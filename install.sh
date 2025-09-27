cmake -B ./build_unix
cmake --build ./build_unix --target build_all_configs
cd ./build_unix
cpack -C "Debug;Release"
cd ..
