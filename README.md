# retroJam

This project is a multi retro console emulator for Adafruit Fruit Jam, capable of emulating a few classic 8-bit systems and even the 16-bit Sega Genesis. Support for additional boards may follow. Some emulators has savestate support.
It also can play .wav music files.

See the [release](https://github.com/fhoedemakers/retroJam/releases/latest) section for precompiled binaries and metadata packs.

## Supported Systems

Use a FAT32 formatted sd-card and put your roms on it. You can use folders to origanize them.
This emulator framework supports the following file extensions:
- `.nes` - Nintendo Entertainment System. With save state support.
- `.md`,`.bin`, `.gen`  - Sega Genesis/MegaDrive
- `.gg` - Sega Game Gear - With save state support.
- `.sms` - Sega Master System - With save state support.
- `.gb` - Nintendo GameBoy
- `.gbc` - Nintendo GameBoy Color

**Note:** Genesis does not run at full speed because of SRAM constraints. As an alternative, you can use the standalone [Pico-GenesisPlus](https://github.com/fhoedemakers/pico-genesisPlus) emulator.

## Building

If you want to build the project yourself, follow these steps:

This project requires the Raspberry Pi Pico SDK and PIO USB. Follow these steps:

1. Set up the Pico SDK environment:
   ```bash
   export PICO_SDK_PATH=/path/to/pico-sdk
   ```
   
2. Download and extract the latest PICO-PIO-USB repo in a folder of your choice: https://github.com/sekigon-gonnoc/Pico-PIO-USB/releases 0.7.2 is the latest as of this writing.
   ```bash
   wget https://github.com/sekigon-gonnoc/Pico-PIO-USB/archive/refs/tags/0.7.2.zip
   unzip 0.7.2.zip
   ```
   
4. Set PICO_PIO_USB_PATH environment variabele:
   ```bash
   export PICO_PIO_USB_PATH=`pwd`/Pico-PIO-USB-0.7.2
   ```
2. Get the repo and initialize submodules in a folder of your choice:
   ```bash
   git clone https://github.com/fhoedemakers/retroJam.git
   cd retroJam
   git submodule update --init --recursive
   ```

3. Create build directory and compile, do this in the directory where you downloaded the retroJam repo:
   ```bash
   chmod +x buildAll.sh
   ./buildAll.sh
   ```

4. Flash the resulting `.uf2` file from the `releases` folder to your RP2350 board.

5. Play!

## Gamepad and keyboard usage

|     | (S)NES | Genesis | XInput | Dual Shock/Sense | 
| --- | ------ | ------- | ------ | ---------------- |
| Button1 | B  |    A    |   A    |    X             |
| Button2 | A  |    B    |   B    |   Circle         |
| Select  | select | Mode or C | Select | Select     |

### Menu 
Gamepad buttons:
- UP/DOWN: Next/previous item in the menu.
- LEFT/RIGHT: next/previous page.
- Button2: Open folder/flash and start game.
- Button1: Back to parent folder.
- START: Show [metadata](#using-metadata) and box art (when available)
- SELECT: Opens a setting menu. Here you can change settings like screen mode, scanlines, framerate display, menu colors and other board specific settings. Settings can also be changed in-game by pressing some button combinations as explained below. The settings menu can also be opened in-game.

When using an USB-Keyboard:
- Cursor keys: Up, Down, left, right
- Z: Back to parent folder
- X: Open Folder/flash and start a game
- S: Show [metadata](#using-metadata) and box art (when available).
- A: acts as the select button.

### Emulator (in game)
Gamepad buttons:
- SELECT + START, Xbox button: opens the settings menu. From there, you can:
  - Quit the game and return to the SD card menu
  - Manage save states **(NES/SMS/Game Gear only)**. Load or save your game state to one of 5 slots. Enable auto save/load state on exit/start.
  - Adjust settings and resume your game.
- SELECT + UP/SELECT + DOWN: switches screen modes.
- SELECT + Button1/Button2: toggle rapid-fire.
- START + Button2: Toggle framerate display
- START + DOWN : (quick) Save state. (slot 5)
- START + UP : (quick) Load state. (slot 5)
- **Pimoroni Pico DV Demo Base only**: SELECT + LEFT: Switch audio output to the connected speakers on the line-out jack of the Pimoroni Pico DV Demo Base. The speaker setting will be remembered when the emulator is restarted.
- **Fruit Jam Only** 
  - SELECT + UP: Toggle scanlines.   
  - pushbutton 1 (on board): Mute audio of built-in speaker. Audio is still outputted to the audio jack.
  - pushbutton 2 (on board) or SELECT + RIGHT: Toggles the VU meter on or off. (NeoPixel LEDs light up in sync with the music rhythm)
  - START + LEFT/RIGHT: Adjust volume of built-in speaker and external audio jack.
- **RP2350 with PSRAM only**: Record about 30 seconds of audio by pressing START to pause the game and then START + BUTTON1. Audio is recorded to **/soundrecorder.wav** on the SD-card.
- **Genesis Mini Controller**: When using a Genesis Mini controller with 3 buttons, press C for SELECT. 8 buttons Genesis controllers press MODE for SELECT
- **USB-keyboard**: When using an USB-Keyboard
  - Cursor keys: up, down, left, right
  - A: SELECT
  - S: START
  - Z: Button1
  - X: Button2

NES Save States should work for  mapper 0,1,2,3 and 4. Other mappers may or may not work. Below the games that use these mappers.

  - https://nesdir.github.io/mapper1.html
  - https://nesdir.github.io/mapper2.html
  - https://nesdir.github.io/mapper3.html
  - https://nesdir.github.io/mapper4.html

  The mapper number is also shown in the Save State screen.


## Using Metadata

When a game is selected in the menu, pressing the START button will show metadata information about the game, such as title, publisher, year of release, genre, and box art (if available).
For this to work, extract the metadata packs from the releases section to your SD card. 

## Music Playback in menu (RP2350 Only)

The menu allows you to play music files. Files must meet the following requirements:

- **Format:** WAV  
- **Bit depth:** 16-bit  
- **Sample rate:** 44.1 kHz  
- **Channels:** Stereo  
- **File extension:** `.wav`  

You can find some free retro tunes here:  https://lonepeakmusic.itch.io/retro-midi-music-pack-1

## How to Play
1. Select a music file from the menu.
2. Press **Button2** or **START** to start playback.
3. Press **Button2** or **START** again to stop playback.

## Converting MP3 to WAV
You can easily convert MP3 files to WAV using [Audacity](https://www.audacityteam.org/):

1. Open the MP3 file in Audacity.
2. Go to **File → Export → Export Audio**.
3. Choose the following settings:
   - **Format:** WAV (Microsoft)
   - **Channels:** Stereo
   - **Sample rate:** 44,100 Hz
   - **Encoding:** Signed 16-bit PCM
4. Copy the exported WAV file to the SD card.

## Hardware

This project is designed for:

- **Board:** Adafruit Fruit Jam
- **Controllers:** USB Dual Shock, Dual Sense, XInput (XBOX), NES USB controller, and Wii Classic Controller support via STEMMA QT.

Other boards may follow. PSRAM must be available for it to work.
 - USB controller support (submodule)

## Credits

Based on [pico-infonesPlus](https://github.com/fhoedemakers/pico-infonesPlus) by @frenskefrens
