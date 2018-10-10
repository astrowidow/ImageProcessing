//
// Created by 俵京佑 on 2018/10/04.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H


#include "common.h"
#include "Pixel.h"

class Image {
protected:
    UINT width;
    UINT height;
    UINT depth;
    UINT byte_per_pix;
    UINT data_size;
    BYTE* data;
public:
    Image();
    UCHAR getPixel(int row, int col, Pixel* dst_pixel);
    UCHAR setPixel(int row, int col, Pixel* src_pixel);
    UINT getWidth();
    UINT getHeight();
    UINT getDepth();
    UINT getBytePerPix();
    UINT getDataSize();
    BYTE* getData();
    virtual ~Image();

protected:
    bool checkBytePerPixel(Pixel* arg_pixel);
    UINT calcBytePerPixel(UINT depth);
};


#endif //IMAGEPROCESSING_IMAGE_H
