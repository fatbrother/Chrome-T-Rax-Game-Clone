cmake_minimum_required(VERSION 3.10)

project(LittleDinosaur)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# compile all files in src
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(main ${SOURCES})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(main PRIVATE sfml-system sfml-network sfml-graphics sfml-window)