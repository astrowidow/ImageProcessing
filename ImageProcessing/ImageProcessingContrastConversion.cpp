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
    pixel = new Pixel(src->getBytePerPix());
}

void ImageProcessingContrastConversion::execute()
{
    // declaration
    BYTE* p_pixel_data;
    Image* source = src;
    Image* destination = dst;
    UINT byte_per_pixel = source->getBytePerPix();
    int pixel_data;

    // processing
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            p_pixel_data = (BYTE*)source->getPixel(row, col);
            for(UCHAR i = 0; i < byte_per_pixel; i++){
                pixel_data = (int) (gain*p_pixel_data[i] + offset);
                if(pixel_data > SATURATED_PIXEL) pixel_data = SATURATED_PIXEL;
                if(pixel_data < 0) pixel_data = 0;
                p_pixel_data[i] = (BYTE)pixel_data;
            }
            destination->setPixel(row, col, p_pixel_data);
        }
    }
}

ImageProcessingContrastConversion::~ImageProcessingContrastConversion(){
    // do nothing
}