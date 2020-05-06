# Audio Project

## Command line

First, setup "PreLoad.cmake" to your liking..

Then for each case, run:

### Release
- `cmake -S . -B Release`
- `cmake --build Release`

### Debug
- `cmake -S . -B Debug -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build Debug`
