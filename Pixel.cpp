//
// Created by 俵京佑 on 2018/09/13.
//

#include "Pixel.h"

Pixel::Pixel(UINT size):byte_per_pix(size){
    data = (BYTE*)malloc(byte_per_pix);
}

void Pixel::setData(BYTE *src_data) {
    memcpy(data, src_data, byte_per_pix);
    return;
}

BYTE* Pixel::getData() const {
    return data;
}

UINT Pixel::getByte_per_pix() const {
    return byte_per_pix;
}

Pixel::~Pixel() {
    free(data);
}
