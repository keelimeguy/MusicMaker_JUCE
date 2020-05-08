# MusicMaker_JUCE

A program to make, generate, and play: chord progressions, phrases, and other such musical things.

This program is an inspired rewrite of my [java implementation](https://github.com/keelimeguy/MusicMaker) and [python implementation](https://github.com/keelimeguy/MusicMakerPy).


## Usage
- `cmake -S . -B build [-D<ARGS>=0|1]`
- `cmake --build build --config <Debug|Release> --target install`

Installed files will appear in the "install/" subdirectory.

### ARGS
- `AUTO_BUILD_FRUT` : Build the FRUT sub-repository automatically, defaults to 1
- `VENDOR_BUILD_DEMORUNNER` : Build the DemoRunner example JUCE project, defaults to 0
- `USE_DEMORUNNER_BIGOBJ_FIX` : Add big-obj flags to fix large file errors in DemoRunner, defaults to 1


## System
MusicMaker Tested on:
- Windows 10.0.18362 --- with MSVC 19.13.26128.0

DemoRunner Tested on:
- Windows 10.0.18362 --- with MSVC 19.13.26128.0
- WSL 4.4.0-18362-Microsoft #476-Microsoft (Debian GNU/Linux 9) --- with GNU 6.3.0


## Dependencies

### DemoRunner
The following might help to fix missing dependencies while building the DemoRunner example JUCE project

#### GNU/Linux
- `sudo apt install libasound2-dev libwebkit2gtk-4.0-dev libgtk-3-dev libcurl4-openssl-dev`
