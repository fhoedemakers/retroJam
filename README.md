# retroJam

Multicore emulator for Adafruit Fruit Jam. Other boards may follow. 

## Supported Systems

This emulator framework supports the following file extensions:
- `.nes` - Nintendo Entertainment System
- `.md`,`.bin`, `.gen`  - Sega Genesis/MegaDrive
- `.gg` - Sega Game Gear
- `.sms` - Sega Master System
- `.gb` - Nintendo GameBoy
- `.gbc` - Nintendo GameBoy Color

**Note:** Genesis does not run at full speed because of SRAM constraints. As an alternative, you can use the standalone [Pico-GenesisPlus](https://github.com/fhoedemakers/pico-genesisPlus) emulator.

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
   ./pico_shared/bld.sh -c8
   ```

4. Flash the resulting `.uf2` file to your RP2350 board.

## Hardware

This project is designed for:

- **Board:** Adafruit Fruit Jam
- **Controllers:** USB Dual SHock, Dual Sense, XInput (XBOX), NES controller, and Wii Classic Controller support

Other boards will follow. PSRAM must be available for it to work.

## Structure

- `main.cpp` - Main entry point with menu system
- `CMakeLists.txt` - Build configuration
- `pico_lib/` - DVI and utility libraries (submodule)
- `pico_shared/` - Shared code for menu, settings, and hardware support (submodule)
- `tusb_xinput/` - USB controller support (submodule)

## Credits

Based on [pico-infonesPlus](https://github.com/fhoedemakers/pico-infonesPlus) by @frenskefrens
