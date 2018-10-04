//
// Created by 俵京佑 on 2018/10/04.
//

#include "Image.h"

Image::Image() {}

UCHAR Image::getPixel(int row,
                       int col,
                       Pixel* dst_pixel) // if this argument is not pointer, Pixel instance (malloc) is executed every time
{
    // select the nearest pixel if the row and the col refer out of an image
    UCHAR get_status = 0;
    if(row < 0){
        row = 0;
        get_status = 1;
    }
    else if(row >= height){
        row = height - 1;
        get_status = 1;
    }
    if(col < 0){
        col = 0;
        get_status = 1;
    }
    else if(col >= width) {
        col = width - 1;
        get_status = 1;
    }
    bool is_match_depth = checkBytePerPixel(dst_pixel);
    if(!is_match_depth) get_status = 2;

    if(get_status == 0){
        // get an address of the referred pixel
        UINT pixel_position = col + row * width;
        dst_pixel->setData(&data[pixel_position*byte_per_pix]);
    }
    else{
        printf("setting error occurred. Error: %d.\n", get_status);
    }

    return get_status;
}

UCHAR Image::setPixel(int row,
                       int col,
                       Pixel* src_pixel) // prevent malloc from execution by using pointer
{
    UCHAR set_status = 0;

    // error check !
    if(row < 0 || height <= row) set_status = 1;
    if(col < 0 || width <= col) set_status = 1;
    bool is_match_depth = checkBytePerPixel(src_pixel);
    if(!is_match_depth) set_status = 2;

    if(set_status == 0){
        // get an address of the referred pixel
        UINT pixel_position = col + row * width;
        memcpy(&data[pixel_position*byte_per_pix], src_pixel->getData(), byte_per_pix);
    } else {
        printf("setting error occured. Error: %d.\n", set_status);
    }

    return set_status;
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
BYTE* Image::getData(){
    return data;
}

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