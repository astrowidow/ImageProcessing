//
// Created by 俵京佑 on 2018/10/04.
//

#include "Image.h"

Image::Image() {
    histogram = new UINT[EIGHT_BITS_GRADATION_NUM*byte_per_pix];
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
UINT* Image::calcHistogram(){
    if(data == nullptr){
        return nullptr;
    }
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

    return histogram;
}
Image::~Image(){
    delete[] histogram;
    histogram = nullptr;
}

UINT Image::calcBytePerPixel(UINT depth){
    bool is_divisible = (depth%BYTE_IN_BITS == 0);
    UINT byte_p_pix;
    is_divisible ? byte_p_pix = depth/BYTE_IN_BITS : byte_p_pix = depth/BYTE_IN_BITS + 1;
    return  byte_p_pix;
}