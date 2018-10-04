cmake_minimum_required(VERSION 3.10)
project(imageProcessing)

set(CMAKE_CXX_STANDARD 11)

add_executable(imageProcessing main.cpp Bitmap.cpp Bitmap.h common.h Pixel.cpp Pixel.h ImageProcessing.cpp ImageProcessing.h ImageProcessing/ImageProcessingContrastConversion.cpp ImageProcessing/ImageProcessingContrastConversion.h Image.cpp Image.h)