cmake_minimum_required(VERSION 3.10)
project(imageProcessing)

set(CMAKE_CXX_STANDARD 11)

add_executable(imageProcessing main.cpp Bitmap.cpp Bitmap.h common.h Pixel.cpp Pixel.h ProcessStrategy.cpp ProcessStrategy.h ProcessStrategy/ProcessStrategyContrastConversion.cpp ProcessStrategy/ProcessStrategyContrastConversion.h)