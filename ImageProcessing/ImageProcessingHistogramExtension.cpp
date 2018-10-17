//
// Created by 俵京佑 on 2018/10/18.
//

#include "ImageProcessingHistogramExtension.h"

ImageProcessingHistogramExtension::ImageProcessingHistogramExtension
        (Image* src_image,
         Image* dst_image)
        : ImageProcessing(src_image->getHeight(),
                          src_image->getWidth(),
                          src_image->getBytePerPix())
{
    src = src_image;
    dst = dst_image;
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            for(UCHAR byte_num = 0; byte_num < byte_per_pixel; byte_num++){

            }
        }
    }

    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){

    }
}

void ImageProcessingHistogramExtension::execute()
{
    // declaration
    Image* source = src;
    Image* destination = dst;
    BYTE pixel_data;

    // processing
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            for(UCHAR byte_num = 0; byte_num < byte_per_pixel; byte_num++){
                // gamma correction
                pixel_data = source->getPixelByte(row, col, byte_num);
                pixel_data = result_table[pixel_data];
                // set the data to dst
                destination->setPixelByte(row, col, (BYTE)pixel_data, byte_num);
            }
        }
    }
}

ImageProcessingHistogramExtension::~ImageProcessingHistogramExtension(){
    // do nothing
}