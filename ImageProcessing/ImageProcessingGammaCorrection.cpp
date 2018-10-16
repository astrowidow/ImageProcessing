//
// Created by 俵京佑 on 2018/10/17.
//

#include <cmath>
#include "ImageProcessingGammaCorrection.h"

ImageProcessingGammaCorrection::ImageProcessingGammaCorrection
        (Image* src_image,
         Image* dst_image,
         double gamma) : ImageProcessing(src_image->getHeight(), src_image->getWidth()), gamma(gamma)
{
    src = src_image;
    dst = dst_image;

    double base;
    for(int i = 0; i <= BYTE_MAX; i++){
        base = (double)i/BYTE_MAX;
        result_table[i] = (BYTE) (pow(base, gamma)*BYTE_MAX);
    }
}

void ImageProcessingGammaCorrection::execute()
{
    // declaration
    Image* source = src;
    Image* destination = dst;
    UINT byte_per_pixel = source->getBytePerPix();
    BYTE* p_src_pixel_data;
    BYTE* p_dst_pixel_data;// = new BYTE[byte_per_pixel];
    int pixel_data;

    // processing
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            p_src_pixel_data = (BYTE*)source->getPixel(row, col);
            p_dst_pixel_data = (BYTE*)destination->getPixel(row, col);
            for(UCHAR i = 0; i < byte_per_pixel; i++){
                // gamma correction
                pixel_data = result_table[p_src_pixel_data[i]];
                // set the data to dst
                p_dst_pixel_data[i] = (BYTE)pixel_data;
            }
        }
    }
}

ImageProcessingGammaCorrection::~ImageProcessingGammaCorrection(){
    // do nothing
}