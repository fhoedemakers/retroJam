# picomulator

Multicore emulator for RP2350 with PSRAM support.

## Supported Systems

This emulator framework supports the following file extensions:
- `.nes` - Nintendo Entertainment System
- `.md` - Sega Genesis/MegaDrive
- `.gg` - Sega Game Gear
- `.gb` - Nintendo GameBoy
- `.gbc` - Nintendo GameBoy Color

**Note:** Individual emulator cores are not yet implemented. This is the framework structure based on pico-infonesPlus.

## Building

This project requires the Raspberry Pi Pico SDK. Follow these steps:

1. Set up the Pico SDK environment:
   ```bash
   export PICO_SDK_PATH=/path/to/pico-sdk
   ```

2. Initialize submodules:
   ```bash
   git submodule update --init --recursive
   ```

3. Create build directory and compile:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. Flash the resulting `.uf2` file to your RP2350 board.

## Hardware

This project is designed for:
- **Board:** Raspberry Pi Pico 2 (RP2350)
- **Memory:** PSRAM support enabled
- **Display:** DVI output (configurable via BoardConfigs.cmake)
- **Storage:** SD card for ROM files
- **Controllers:** USB, NES controller, and Wii Classic Controller support

## Structure

- `main.cpp` - Main entry point with menu system
- `CMakeLists.txt` - Build configuration
- `pico_lib/` - DVI and utility libraries (submodule)
- `pico_shared/` - Shared code for menu, settings, and hardware support (submodule)
- `tusb_xinput/` - USB controller support (submodule)

## Credits

Based on [pico-infonesPlus](https://github.com/fhoedemakers/pico-infonesPlus) by @frenskefrens