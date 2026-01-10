# CHANGELOG

A multi retro console emulator for Adafruit Fruit Jam, capable of emulating a few classic 8-bit systems and even the 16-bit Sega Genesis. Support for additional boards may follow. Some emulators have savestate support. It also can play .wav music files.
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

## Fixes
- Use SRAM for NES emulator buffers.
- More minor fixes and improvements.

# v0.3 Release notes

## Fixes

- Clock speed on Fruit Jam was set to an incorrect value for Genesis games, causing instability. Fixed.
- Fixed an issue where writing to flash sometimes caused the system to hang without rebooting.
- Other small fixes and improvements.

# v0.2 Release notes

## Fixes

- WAV playback fixed.

# v0.1 Release notes

Initial release. Adafruit Fruit Jam only for now.
There will be bugs! Please report them on GitHub.

## Metadata

Extract the zip files to the root folder of the SD card. Select a game in the menu and press START to show more information and box art. Works for most official released games. Screensaver shows floating random cover art.