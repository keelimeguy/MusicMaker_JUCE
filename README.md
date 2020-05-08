# Audio Project

## System
Tested on:
- Windows 10.0.18362 with MSVC 19.13.26128.0

## Usage
First, setup "PreLoad.cmake" to your liking..

Then run, for either Debug or Release, using:
- `cmake -S . -B build [-DVENDOR_BUILD_DEMORUNNER=1]`
- `cmake --build build --config <Debug|Release> --target install`

Add the `VENDOR_BUILD_DEMORUNNER` flag only if you wish for the DemoRunner example JUCE project to be compiled.

Installed files will appear in the "install/" subdirectory.
