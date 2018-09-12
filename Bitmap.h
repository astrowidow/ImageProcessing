//
// Created by 俵京佑 on 2018/09/11.
//

#ifndef IMAGEPROCESSING_BITMAP_H
#define IMAGEPROCESSING_BITMAP_H

#include "common.h"

class Bitmap {
private:
    UINT width;
    UINT height;
    UINT depth;
    UINT byte_per_pix;
    BYTE* imageData;
public:
    Bitmap(UINT width, UINT height, UINT depth);
    BYTE* getPixel(UINT row, UINT col);
    char setPixel(UINT row, UINT col);
    virtual ~Bitmap();
};


#endif //IMAGEPROCESSING_BITMAP_H
