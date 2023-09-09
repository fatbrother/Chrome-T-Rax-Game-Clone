# bin/bash

# Build the project
echo "Building the project..."

mkdir -p build
sudo rm -rf build/*

cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release