//
// Created by 俵京佑 on 2018/09/25.
//

#include "ImageProcessingContrastConversion.h"
#include "../Image.h"

ImageProcessingContrastConversion::ImageProcessingContrastConversion
        (Image* src_image,
         Image* dst_image,
        double gain,
        double offset) : ImageProcessing(src_image->getHeight(), src_image->getWidth()), gain(gain), offset(offset)
{
    src = src_image;
    dst = dst_image;
}

void ImageProcessingContrastConversion::executeOpening() {}

void ImageProcessingContrastConversion::executeProcess(UINT row, UINT col)
{
    if(src->getPixel(row, col, pixel) != 0){
        printf("error at get pixel: row = %d, col = %d", row+1, col+1);
    }
    BYTE* p_pixel_data = pixel->getData();
    for(UCHAR i = 0; i < src->getBytePerPix(); i++){
        int data_temp = (int) (gain*p_pixel_data[i] + offset);
        if(data_temp > 255) data_temp = 255;
        if(data_temp < 0) data_temp = 0;
        p_pixel_data[i] = (BYTE)data_temp;
    }
    pixel->setData(p_pixel_data);
    if(dst->setPixel(row, col, pixel) != 0){
        printf("error at set pixel: row = %d, col = %d", row+1, col+1);
    }
}

void ImageProcessingContrastConversion::executeEnding() {}

ImageProcessingContrastConversion::~ImageProcessingContrastConversion(){
    // do nothing
}