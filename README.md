# Audio Project

## Command line

First, setup "PreLoad.cmake" to your liking..

Then for each case, run:

### Debug
- `cmake -S . -B Debug`
- `cmake --build Debug`

### Release
- `cmake -S . -B Release -DCMAKE_BUILD_TYPE=Release`
- `cmake --build Release`
