//
// Created by 俵京佑 on 2018/10/04.
//

#include "Image.h"

Image::Image(UINT width, UINT height, UINT depth)
        : width(width),
          height(height),
          depth(depth),
          byte_per_pix(calcBytePerPixel(depth)),
          data_size(width*height*byte_per_pix)
{
    histogram = new UINT[EIGHT_BITS_GRADATION_NUM*byte_per_pix];
    data = new BYTE[data_size];
}

void Image::initImage(UINT width, UINT height, UINT depth) {
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->byte_per_pix = calcBytePerPixel(depth);
    this->data_size = width*height*this->byte_per_pix;
    this->histogram = new UINT[EIGHT_BITS_GRADATION_NUM*this->byte_per_pix];
    this->data = new BYTE[this->data_size];
}

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
void Image::calcHistogram(){
    // initialize memory
    memset(histogram, 0x00, sizeof(UINT)*EIGHT_BITS_GRADATION_NUM*byte_per_pix);

    BYTE pixel_data;
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            for(UCHAR byte_num = 0; byte_num < byte_per_pix; byte_num++){
                pixel_data = getPixelByte(row, col, byte_num);
                histogram[byte_per_pix*pixel_data + byte_num]++;
                //printf("data = %d\n", pixel_data);
                //printf("hist = %d\n", histogram[byte_per_pix*pixel_data + byte_num]);
            }
        }
    }
//    int sum = 0;
//    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){
//        printf("freq of %d if %d\n", i, histogram[i]);
//        sum += histogram[i];
//    }
//    printf("pixel num is %d", sum);
}

Image::~Image(){
    delete[] histogram;
    delete[] data;
    histogram = nullptr;
    data = nullptr;
}

UINT Image::calcBytePerPixel(UINT depth){
    bool is_divisible = (depth%BYTE_IN_BITS == 0);
    UINT byte_p_pix;
    is_divisible ? byte_p_pix = depth/BYTE_IN_BITS : byte_p_pix = depth/BYTE_IN_BITS + 1;
    return  byte_p_pix;
}