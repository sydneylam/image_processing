cmake_minimum_required(VERSION 3.17)
project(Image_Processing)

set(CMAKE_CXX_STANDARD 14)

add_executable(Image_Processing src/image-processor.cpp src/Header.h src/Header.cpp src/pixel.cpp src/pixel.h src/Image.cpp src/Image.h)