//
// Created by 俵京佑 on 2018/09/11.
//
#include <cstdlib>
#include "Bitmap.h"

Bitmap::Bitmap(UINT w, UINT h, UINT d):width(w), height(h), depth(d) {
    bool isDivisible = (depth%BYTE_IN_BITS == 0);
    isDivisible ? byte_per_pix = depth/BYTE_IN_BITS : byte_per_pix = depth/BYTE_IN_BITS + 1;

    imageData = (BYTE*)malloc(width * height * byte_per_pix);
}

BYTE* Bitmap::getPixel(UINT row, UINT col) {
    // select the nearest pixel if the row and the col refer out of an image
    if(row < 0) row = 0;
    else if(row >= height) row = height - 1;
    if(col < 0) col = 0;
    else if(col >= width) col = width - 1;

    // get an address of the referred pixel
    UINT pixelPosition = col + row * width;
    return &imageData[pixelPosition * byte_per_pix];
}

char Bitmap::setPixel(UINT row, UINT col) {
}

Bitmap::~Bitmap() {
    free(imageData);
}
