//
// Created by 俵京佑 on 2018/09/11.
//
#include <cstdlib>
#include <cstring>
#include "Bitmap.h"

Bitmap::Bitmap(UINT w, UINT h, UINT d):width(w), height(h), depth(d) {
    bool is_divisible = (depth%BYTE_IN_BITS == 0);
    is_divisible ? byte_per_pix = depth/BYTE_IN_BITS : byte_per_pix = depth/BYTE_IN_BITS + 1;

    data = (BYTE*)malloc(width * height * byte_per_pix);
}

Pixel Bitmap::getPixel(UINT row, UINT col) {
    // select the nearest pixel if the row and the col refer out of an image
    if(row < 0) row = 0;
    else if(row >= height) row = height - 1;
    if(col < 0) col = 0;
    else if(col >= width) col = width - 1;

    // get an address of the referred pixel
    UINT pixel_position = col + row * width;
    Pixel pixel_tmp(byte_per_pix);
    pixel_tmp.setData(&data[pixel_position]);

    return pixel_tmp;
}

char Bitmap::setPixel(UINT row, UINT col, Pixel pixel_data) {
    int set_status = 1;

    // error check !
    if(row < 0 || height <= row) set_status = -1;
    if(col < 0 || width <= col) set_status = -2;
    bool is_match_depth = (pixel_data.getByte_per_pix() == byte_per_pix);
    if(!is_match_depth) set_status = -3;

    if(set_status == 1){
        memcpy(data, pixel_data.getData(), byte_per_pix);
    } else {
        printf("setting error occured. Error: %d.\n", set_status);
    }

    return set_status;
}

Bitmap::~Bitmap() {
    free(data);
}
