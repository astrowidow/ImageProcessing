//
// Created by 俵京佑 on 2018/09/11.
//

#ifndef IMAGEPROCESSING_BITMAP_H
#define IMAGEPROCESSING_BITMAP_H

#include "common.h"
#include "Pixel.h"

class Bitmap {
private:
    UINT width;
    UINT height;
    UINT depth;
    UINT byte_per_pix;
    BYTE* data;
public:
    Bitmap(UINT width, UINT height, UINT depth);
    Pixel getPixel(UINT row, UINT col);
    char setPixel(UINT row, UINT col, Pixel pixel_data);
    virtual ~Bitmap();
};


#endif //IMAGEPROCESSING_BITMAP_H
