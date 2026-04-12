# CHANGELOG

A multi retro console emulator for Adafruit Fruit Jam, capable of emulating a few classic 8-bit systems and even the 16-bit Sega Genesis. Support for additional boards may follow. Some emulators have savestate support. It also can play .wav music files.

# v0.6 Release notes

## New and improved Mapper support for NES emulator.

- **RP2350 only:** Added support for Mapper 5 (MMC5 – *Castlevania III* US). Graphical glitches may still occur. These MMC 5 games are tested:
  - Castlevania III US
  - Gemfire (USA version)
  - Romance of the Three Kingdoms II (Japanese version)
  - Nobunaga’s Ambition II (Japanese/USA version)
- **All platforms (RP2040/RP2350):** Added support for Mapper 24 (VRC6A – *Castlevania III/Akumajou Densetsu* JP).
- Mapper 30 (NesMaker) now working.
- Fix HUD not displaying in Parodius DA! (Jap) - mapper 23
- Fix HUD not displaying in Fudou Myouou Den (Japan) - mapper 80
- Fix corrupt graphics in Punch Out! and Fire Emblem Gaiden (JP)
- Fix for roms with incorrect header info, like Galaxian (JP)
- Fix for Robocop 3 (USA) not starting and only showing a black screen instead. (Mapper 1 fix, see [#185](https://github.com/fhoedemakers/pico-infonesPlus/issues/185)) 


Many thanks to [@szuping](https://github.com/szuping) for testing the mapper changes.

Mapper fixes were developed with the help of [Anthropic Claude](https://www.anthropic.com/claude/opus).

## Display & audio

- **Adafruit Fruit Jam:**
  - Headphone detection now works correctly. Plugging in headphones automatically mutes the speaker (Internal or monitor); unplugging them re-enables it.
  - The external audio setting, when enabled, enables the Fruit Jam built-in speaker. Audio is muted from the monitor.
  - Removed the setting and pushbutton1 functionality for muting the internal speaker. Headphone detection now automatically mutes the internal speaker.

## Fixes

- Updated the metadata and cover art pack with missing entries, including artwork for several Japanese titles. See the [Downloads section](#downloads___) below for the download link and instructions. Thanks again to [@DynaMight1124](https://github.com/DynaMight1124)

# v0.5 Release notes

## New Features

- HDMI audio is now supported via the new HSTX video driver. Huge thanks to [@fliperama86](https://github.com/fliperama86) for the awesome [pico_hdmi](https://github.com/fliperama86/pico_hdmi) driver that made this possible.
 Make sure to disable External Audio in the settings. 
- Added option in settings menu to enter bootsel mode for flashing firmware. 

# v0.4 Release notes

## New Features

- Support for Murmulator M2
- Support for Adafruit Feather RP2350 HSTX. This config can be used for breadboard projects and requires the following hardware:
  - Breadboard.
  - [Adafruit Feather RP2350 with HSTX and PSRAM](https://www.adafruit.com/product/6130)
  - [TLV320DAC3100 - I2S DAC with Headphone and Speaker Out](https://www.adafruit.com/product/6309)
  - [Adafruit Micro SD SPI or SDIO Card Breakout Board - 3V ONLY!](https://www.adafruit.com/product/4682)
  - [Adafruit RP2350 22-pin FPC HSTX to DVI Adapter for HDMI Displays](https://www.adafruit.com/product/6055)
  - [22-pin 0.5mm pitch FPC Flex Cable for DSI CSI or HSTX - 5cm](https://www.adafruit.com/product/6034)
  - For USB gamecontrollers:
    - [Adafruit USB Type C Breakout Board - Downstream Connection](https://www.adafruit.com/product/4090)
  - When using a WII-Classic controller for input:
    - [Adafruit Wii Nunchuck Breakout Adapter - Qwiic / STEMMA QT](https://www.adafruit.com/product/4836)
- Added -D option to bld.sh to force DVI output on HSTX boards.
- Added support for PCM5000A I2S DAC on HW_CONFIG 2 (Breadboard/PCB with Pico/Pico2). This is optional and disabled by default. 

## Fixes
- Use SRAM for NES emulator buffers.
- SMS audio fixes.
- GB Audio fixes.
- Set volume to correct level when starting emulator.
- More minor fixes and improvements.
- Improved nespad driver. [@javavi](https://github.com/javavi)

## Metadata

Extract the zip files to the root folder of the SD card. Select a game in the menu and press START to show more information and box art. Works for most official released games. Screensaver shows floating random cover art.

# previous changes

See [HISTORY.md](https://github.com/fhoedemakers/pico-peanutGB/blob/main/HISTORY.md)