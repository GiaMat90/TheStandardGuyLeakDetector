@echo off
echo Building all configurations...
cmake -B build_win
cmake --build build_win --target build_all_configs
cd build_win
cpack -C "Debug;Release"
cd ..
