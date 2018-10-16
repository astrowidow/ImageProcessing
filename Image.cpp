//
// Created by 俵京佑 on 2018/10/04.
//

#include "Image.h"

Image::Image() {}

UINT Image::getWidth(){
    return width;
}
UINT Image::getHeight(){
    return height;
}
UINT Image::getDepth(){
    return depth;
}
UINT Image::getBytePerPix(){
    return  byte_per_pix;
}
UINT Image::getDataSize(){
    return data_size;
}
void* Image::getData(){
    return data;
}

Image::~Image(){}

// protected function ---------------------------------
bool Image::checkBytePerPixel(Pixel* arg_pixel){
    return (arg_pixel->getBytePerPix() == byte_per_pix);
}

UINT Image::calcBytePerPixel(UINT depth){
    bool is_divisible = (depth%BYTE_IN_BITS == 0);
    UINT byte_p_pix;
    is_divisible ? byte_p_pix = depth/BYTE_IN_BITS : byte_p_pix = depth/BYTE_IN_BITS + 1;
    return  byte_p_pix;
}