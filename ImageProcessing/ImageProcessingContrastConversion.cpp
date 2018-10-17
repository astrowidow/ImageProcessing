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

void ImageProcessingContrastConversion::execute()
{
    // declaration
    Image* source = src;
    Image* destination = dst;
    UINT byte_per_pixel = source->getBytePerPix();
    //BYTE src_pixel_data;
    //BYTE dst_pixel_data;// = new BYTE[byte_per_pixel];
    int pixel_data;

    // processing
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            for(UCHAR i = 0; i < byte_per_pixel; i++){
                // linear contrast conversion
                pixel_data = source->getPixelByte(row, col, i);
                pixel_data = (int) (gain*pixel_data + offset);
                // trim result data
                if(pixel_data > SATURATED_PIXEL) pixel_data = SATURATED_PIXEL;
                if(pixel_data < 0) pixel_data = 0;
                // set the data to dst
                //dst_pixel_data = (BYTE)pixel_data;
                destination->setPixelByte(row, col, (BYTE)pixel_data, i);
            }
            //destination->setPixel(row, col, p_dst_pixel_data);
        }
    }
    //delete[] p_dst_pixel_data;
}

ImageProcessingContrastConversion::~ImageProcessingContrastConversion(){
    // do nothing
}