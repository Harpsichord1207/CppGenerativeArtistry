cmake_minimum_required(VERSION 3.16)
project(CppGenerativeArtistry)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "D:/Projects/Cpp/ExLibs/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML REQUIRED COMPONENTS audio network graphics window system)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML NOT FOUND!")
else()
    message("SFML FOUND!")
endif()

include_directories(${SFML_INCLUDE_DIR})
add_executable(
        CppGenerativeArtistry
        main.cpp
        utils.cpp
        CirclePacking/draw.cpp
        PietMondrian/draw.cpp
        HypnoticSquares/draw.cpp
)
target_link_libraries(CppGenerativeArtistry sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
