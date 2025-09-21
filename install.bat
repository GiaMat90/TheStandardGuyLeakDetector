@echo off
echo Building all configurations...
cmake -B build
cmake --build build --target build_all_configs
cd build
cpack -C "Debug;Release"
cd ..
