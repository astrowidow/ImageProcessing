//
// Created by 俵京佑 on 2018/10/04.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H


#include "common.h"
#include "Pixel.h"

class Image {
protected:
    // must be set
    UINT width;
    UINT height;
    UINT depth;
    UINT byte_per_pix;
    UINT data_size;
    BYTE* data;

    // optional
    UINT* histogram;

public:
    Image() = default;
    Image(UINT width, UINT height, UINT depth);
    UINT getWidth();
    UINT getHeight();
    UINT getDepth();
    UINT getBytePerPix();
    void calcHistogram();
    UINT getDataSize();
    void* getData();
    virtual ~Image();

protected:
    bool checkBytePerPixel(Pixel* arg_pixel);
    UINT calcBytePerPixel(UINT depth);
    void initImage(UINT width, UINT height, UINT depth);
public:
    inline void setPixel(int row,
                         int col,
                         void* value)
    {
//        bool is_out_of_image = row < 0
//                               || height <= row
//                               || col < 0
//                               || width <= col;
//        if(is_out_of_image) return;

        UINT pixel_position = col + row * width;
        for(UCHAR i = 0; i < byte_per_pix; i++){
            data[pixel_position*byte_per_pix + i] = ((BYTE*)value)[i];
        }
    }

    inline BYTE getPixelByte(int row, int col, int byte_number = 0){
//        row = 0 < row ? row : 0;
//        row = row < height ? row : height - 1;
//        col = 0 < col ? col : 0;
//        col = col < width ? col : width - 1;
        UINT pixel_position = col + row * width;
        return data[pixel_position*byte_per_pix + byte_number];
    }

    inline BYTE getPixelByteWithLimit(int row, int col, int byte_number = 0){
        row = 0 < row ? row : 0;
        row = row < height ? row : height - 1;
        col = 0 < col ? col : 0;
        col = col < width ? col : width - 1;
        UINT pixel_position = col + row * width;
        return data[pixel_position*byte_per_pix + byte_number];
    }

    inline void setPixelByte(int row, int col, BYTE pixel_data, int byte_number = 0){
        UINT pixel_position = col + row * width;
        data[pixel_position*byte_per_pix + byte_number] = pixel_data;
    }

    inline void* getPixel(int row, int col)
    {
        // get an address of the referred pixel
        UINT pixel_position = col + row * width;
        return &data[pixel_position*byte_per_pix];
    }

    inline UINT getFrequencyOfPixelValue(BYTE pixel_value, int byte_number = 0){
        return histogram[pixel_value*byte_per_pix + byte_number];
    }
//
//    inline void* getPixelWithLimit(int row, int col)
//    {
//        // select the nearest pixel if the row and the col refer out of an image
//        row = 0 < row ? row : 0;
//        row = row < height ? row : height - 1;
//        col = 0 < col ? col : 0;
//        col = col < width ? col : width - 1;
//
//        // get an address of the referred pixel
//        UINT pixel_position = col + row * width;
//        return &data[pixel_position*byte_per_pix];
//    }

    inline UINT* getHistogram(){
        return histogram;
    }
};


#endif //IMAGEPROCESSING_IMAGE_H
