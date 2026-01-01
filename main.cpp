#include <stdio.h>
#include <cstring>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/divider.h"
#include "hardware/clocks.h"
#include "hardware/vreg.h"
#include "hardware/watchdog.h"
#include "ff.h"
#include "tusb.h"
#include "gamepad.h"
#include "menu.h"
#include "nespad.h"
#include "wiipad.h"
#include "FrensHelpers.h"
#include "settings.h"
#include "FrensFonts.h"
#include "vumeter.h"
#include "menu_settings.h"

int nes_main(); // Forward declaration of nes_main  function
int gb_main();  // Forward declaration of gb_main  function
int sms_main(); // Forward declaration of sms_main function
int md_main();  // Forward declaration of md_main  function
#define EMULATOR_CLOCKFREQ_KHZ 252000
#define AUDIOBUFFERSIZE (1024 * 4)   // * 4 for Genesis

bool isFatalError = false;
char *romName;
static uint32_t CPUFreqKHz = EMULATOR_CLOCKFREQ_KHZ;
#if 1
// Visibility configuration for options menu
// 1 = show option line, 0 = hide.
// Order must match enum in menu_settings.h
const int8_t g_settings_visibility_main[MOPT_COUNT] = {
    0,                               // Exit Game, or back to menu. Always visible when in-game.
    0,                               // Save / Restore State
    !HSTX,                           // Screen Mode (only when not HSTX)
    HSTX,                            // Scanlines toggle (only when HSTX)
    1,                               // FPS Overlay
    0,                               // Audio Enable
    0,                               // Frame Skip
    (EXT_AUDIO_IS_ENABLED && !HSTX), // External Audio
    1,                               // Font Color
    1,                               // Font Back Color
    ENABLE_VU_METER,                 // VU Meter
    (HW_CONFIG == 8),                // Fruit Jam Internal Speaker
    (HW_CONFIG == 8),                // Fruit Jam Volume Control
    0,                               // DMG Palette (for GameBoy emulators)
    0,                               // Border Mode (for Super GameBoy)
    0,                               // Rapid Fire on A
    0                                // Rapid Fire on B
};
#endif
#if 0
const uint8_t g_available_screen_modes[] = {
    1, // SCANLINE_8_7,
    1, // NOSCANLINE_8_7,
    1, // SCANLINE_1_1,
    1  // NOSCANLINE_1_1
};
#endif
// Placeholder splash screen for the menu system
void splash()
{
    char s[SCREEN_COLS + 1];
    int fgcolor = DEFAULT_FGCOLOR;
    int bgcolor = DEFAULT_BGCOLOR;
    ClearScreen(bgcolor);

    strcpy(s, "retroJam");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 2, s, fgcolor, bgcolor);

    strcpy(s, "Multi retro game Emulator");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 3, s, fgcolor, bgcolor);
    
    strcpy(s, "Adafruit Fruit Jam");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 4, s, fgcolor, bgcolor);

    strcpy(s, "A project created by");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 8, s, fgcolor, bgcolor);
    strcpy(s, "@frenskefrens");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 9, s, CLIGHTBLUE, bgcolor);

    strcpy(s, "Supported systems:");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 13, s, fgcolor, bgcolor);
    
    strcpy(s, "NES, Genesis/MD, SMS/Game Gear");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 14, s, CGREEN, bgcolor);
    
    strcpy(s, "GameBoy, GameBoy Color");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 15, s, CGREEN, bgcolor);

    // strcpy(s, "(Emulators not yet implemented)");
    // putText(SCREEN_COLS / 2 - strlen(s) / 2, 17, s, CRED, bgcolor);

    strcpy(s, "https://github.com/");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 25, s, CLIGHTBLUE, bgcolor);
    strcpy(s, "fhoedemakers/retroJam");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 26, s, CLIGHTBLUE, bgcolor);
}

int main()
{
    vreg_voltage voltage = VREG_VOLTAGE_1_20;
    bool freqOverruled = false;
    char selectedRom[FF_MAX_LFN];
    romName = selectedRom;
    ErrorMessage[0] = selectedRom[0] = 0;
    Frens::FlashParams *flashParams;
    // assign flashParams to point to flash location
    flashParams = (Frens::FlashParams *)FLASHPARAM_ADDRESS;
    if ( Frens::validateFlashParams(*flashParams) ) {
        CPUFreqKHz = flashParams->cpuFreqKHz;
        voltage = flashParams->voltage;
        freqOverruled = true;
    }
    Frens::setClocksAndStartStdio(CPUFreqKHz, voltage);
    printf("Checking flash params at 0x%08X\n", (uintptr_t)flashParams);
    printf("==========================================================================================\n");
    printf("Picomulator %s\n", SWVERSION);
    printf("Build date: %s\n", __DATE__);
    printf("Build time: %s\n", __TIME__);
    printf("CPU freq: %d kHz\n", clock_get_hz(clk_sys) / 1000);
#if HSTX
    printf("HSTX freq: %d\n", clock_get_hz(clk_hstx) / 1000);
#endif
    printf("Stack size: %d bytes\n", PICO_STACK_SIZE);
    printf("==========================================================================================\n");
    printf("Starting up...\n");
    if (freqOverruled)
    {
        printf("CPU Frequency overruled by flash param to %d kHz\n", CPUFreqKHz);
    }

    // Initialize settings with a generic emulator type
    // When specific emulators are added, this should be changed appropriately
    FrensSettings::initSettings(FrensSettings::emulators::MULTI);
    
    // Initialize display and SD card
    // Note: Audio buffer size can be adjusted based on emulator requirements
    isFatalError = !Frens::initAll(selectedRom, CPUFreqKHz, 4, 4, AUDIOBUFFERSIZE, false, true);
  
    bool showSplash = true;
    if (!isFatalError)
    {
        if (!Frens::isPsramEnabled())
        {
            snprintf(ErrorMessage, 256, "PSRAM is not detected!");
            isFatalError = true;
        }
        else
        {
            ErrorMessage[0] = 0;
            isFatalError = false;
        }
    }
    while (true)
    {

        g_settings_visibility = g_settings_visibility_main;
        // Show menu with supported file extensions
        // .nes = NES ROMs
        // .md = Sega Genesis/MegaDrive ROMs
        // .gg = Game Gear ROMs
        // .gb = GameBoy ROMs
        // .gbc = GameBoy Color ROMs
        menu("retroJam", ErrorMessage, isFatalError, showSplash, ".nes .md .gen .bin .sms .gg .gb .gbc", selectedRom);
        printf("Selected ROM from menu: %s\n", selectedRom);

        // TODO: Detect ROM type and launch appropriate emulator
        // For now, just display a message and return to menu
        printf("ROM selected: %s\n", selectedRom);
        printf("Launching  %s emulator\n", FrensSettings::getEmulatorTypeString());
        if ( FrensSettings::getEmulatorType() == FrensSettings::emulators::NES ) {
            printf("Launching NES emulator...\n");
            // Launch NES emulator
            nes_main(); 
        } else if ( FrensSettings::getEmulatorType() == FrensSettings::emulators::GENESIS ) {
            printf("Launching Genesis/MegaDrive emulator...\n");
            // Launch Genesis/MegaDrive emulator
            md_main();
        } else if ( FrensSettings::getEmulatorType() == FrensSettings::emulators::GAMEBOY ) {
            printf("Launching GameBoy/GameBoy Color emulator...\n");
            // Launch GameBoy/GameBoy Color emulator
            gb_main(); 
        } else if ( FrensSettings::getEmulatorType() == FrensSettings::emulators::SMS ) {
            printf("Launching Sega Master System/Game Gear emulator...\n");
            // Launch Sega Master System/Game Gear emulator
            sms_main();
        }
        
        else {
            printf("Unsupported ROM format selected.\n");
        }
        
        // Clear the selection to return to menu
        selectedRom[0] = 0;
        showSplash = false;
    }

    return 0;
}
