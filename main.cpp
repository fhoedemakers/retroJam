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

#define SWVERSION "V0.1"
#define EMULATOR_CLOCKFREQ_KHZ 252000
#define AUDIOBUFFERSIZE 1024

bool isFatalError = false;
char *romName;
static uint32_t CPUFreqKHz = EMULATOR_CLOCKFREQ_KHZ;

// Visibility configuration for options menu
// 1 = show option line, 0 = hide.
// Order must match enum in menu_settings.h
const int8_t g_settings_visibility[MOPT_COUNT] = {
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

const uint8_t g_available_screen_modes[] = {
    1, // SCANLINE_8_7,
    1, // NOSCANLINE_8_7,
    1, // SCANLINE_1_1,
    1  // NOSCANLINE_1_1
};

// Placeholder splash screen for the menu system
void splash()
{
    char s[SCREEN_COLS + 1];
    int fgcolor = DEFAULT_FGCOLOR;
    int bgcolor = DEFAULT_BGCOLOR;
    ClearScreen(bgcolor);

    strcpy(s, "Picomulator");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 2, s, fgcolor, bgcolor);

    strcpy(s, "Multicore Emulator");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 3, s, fgcolor, bgcolor);
    
    strcpy(s, "for RP2350 with PSRAM");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 4, s, fgcolor, bgcolor);

    strcpy(s, "Menu System & SD Card Support");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 8, s, fgcolor, bgcolor);
    strcpy(s, "@frenskefrens");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 9, s, CLIGHTBLUE, bgcolor);

    strcpy(s, "Supported systems:");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 13, s, fgcolor, bgcolor);
    
    strcpy(s, "NES, Genesis/MD, Game Gear");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 14, s, CGREEN, bgcolor);
    
    strcpy(s, "GameBoy, GameBoy Color");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 15, s, CGREEN, bgcolor);

    strcpy(s, "(Emulators not yet implemented)");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 17, s, CYELLOW, bgcolor);

    strcpy(s, "https://github.com/");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 25, s, CLIGHTBLUE, bgcolor);
    strcpy(s, "fhoedemakers/picomulator");
    putText(SCREEN_COLS / 2 - strlen(s) / 2, 26, s, CLIGHTBLUE, bgcolor);
}

int main()
{
    char selectedRom[FF_MAX_LFN];
    romName = selectedRom;
    ErrorMessage[0] = selectedRom[0] = 0;

    Frens::setClocksAndStartStdio(CPUFreqKHz, VREG_VOLTAGE_1_20);

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
    
    // Initialize settings with a generic emulator type
    // When specific emulators are added, this should be changed appropriately
    FrensSettings::initSettings(FrensSettings::emulators::NES);
    
    // Initialize display and SD card
    // Note: Audio buffer size can be adjusted based on emulator requirements
    isFatalError = !Frens::initAll(selectedRom, CPUFreqKHz, 4, 4, AUDIOBUFFERSIZE, false, true);
    
    bool showSplash = true;
    while (true)
    {
        if (strlen(selectedRom) == 0)
        {
            // Show menu with supported file extensions
            // .nes = NES ROMs
            // .md = Sega Genesis/MegaDrive ROMs
            // .gg = Game Gear ROMs
            // .gb = GameBoy ROMs
            // .gbc = GameBoy Color ROMs
            menu("Picomulator", ErrorMessage, isFatalError, showSplash, ".nes .md .gg .gb .gbc", selectedRom);
            printf("Selected ROM from menu: %s\n", selectedRom);
        }
        
        // TODO: Detect ROM type and launch appropriate emulator
        // For now, just display a message and return to menu
        printf("ROM selected: %s\n", selectedRom);
        printf("Emulator not yet implemented.\n");
        
        // Clear the selection to return to menu
        selectedRom[0] = 0;
        showSplash = false;
        
        // Brief delay before showing menu again
        sleep_ms(2000);
    }

    return 0;
}
