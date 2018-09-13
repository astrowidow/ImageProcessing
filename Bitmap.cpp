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

Bitmap::Bitmap(char* file_name){
    FILE* fp;
    fp = fopen(file_name, "rb");

    int data_num = 1;
    fread(&file_header, sizeof(file_header), data_num, fp);

    fread(&core_header.size, sizeof(core_header.size), data_num, fp);
    info_header.size = core_header.size;

    if(core_header.size == 40){
        fread(&info_header, sizeof(info_header) - sizeof(info_header.size), data_num, fp);
    }
    else if(core_header.size == 12){
        fread(&core_header, sizeof(core_header) - sizeof(core_header.size), data_num, fp);
    }
}

UCHAR Bitmap::getPixel(UINT row,
                       UINT col,
                       Pixel* dst_pixel) // if this argument is not pointer, Pixel instance (malloc) is executed every time
{
    // select the nearest pixel if the row and the col refer out of an image
    char get_status = 0;
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
        dst_pixel->setData(&data[pixel_position]);
    }
    else{
        printf("setting error occured. Error: %d.\n", get_status);
    }

    return get_status;
}

UCHAR Bitmap::setPixel(UINT row,
                       UINT col,
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
        memcpy(&data[pixel_position], src_pixel->getData(), byte_per_pix);
    } else {
        printf("setting error occured. Error: %d.\n", set_status);
    }

    return set_status;
}

// private function ---------------------------------
bool Bitmap::checkBytePerPixel(Pixel* arg_pixel){
    return (arg_pixel->getBytePerPix() == byte_per_pix);
}

Bitmap::~Bitmap() {
    free(data);
}
