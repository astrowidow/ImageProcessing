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
    void* getPixel(int row, int col); // inline function
    void setPixel(int row, int col, void* value); // inline function
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


// inline function
inline void* Image::getPixel(int row,
                      int col)
{
    // select the nearest pixel if the row and the col refer out of an image
    if(row < 0){
        row = 0;
    }
    else if(row >= height){
        row = height - 1;
    }
    if(col < 0){
        col = 0;
    }
    else if(col >= width) {
        col = width - 1;
    }
    // get an address of the referred pixel
    UINT pixel_position = col + row * width;

    // In the case the data pointer is malloced,
    // return data pointer
    if(data == NULL) return NULL;
    return &data[pixel_position*byte_per_pix];
}

inline void Image::setPixel(int row,
                      int col,
                      void* value)
{
    bool is_out_of_image
            = row < 0
              || height <= row
              || col < 0
              || width <= col;
    if(is_out_of_image) return;

    UINT pixel_position = col + row * width;
    for(UCHAR i = 0; i < byte_per_pix; i++){
        data[pixel_position*byte_per_pix + i] = *(BYTE*)value;
    }

    return;
}

#endif //IMAGEPROCESSING_IMAGE_H
