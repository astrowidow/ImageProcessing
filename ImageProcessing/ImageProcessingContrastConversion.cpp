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

void ImageProcessingContrastConversion::executeOpening() {}

//void ImageProcessingContrastConversion::executeProcess(UINT row, UINT col)
//{
//    BYTE* p_pixel_data = (BYTE*)src->getPixel(row, col);
//    for(UCHAR i = 0; i < src->getBytePerPix(); i++){
//        int data_temp = (int) (gain*p_pixel_data[i] + offset);
//        if(data_temp > SATURATED_PIXEL) data_temp = SATURATED_PIXEL;
//        if(data_temp < 0) data_temp = 0;
//        p_pixel_data[i] = (BYTE)data_temp;
//    }
//    dst->setPixel(row, col, p_pixel_data);
//}

void ImageProcessingContrastConversion::executeProcess()
{
    BYTE* p_pixel_data = (BYTE*)src->getPixel(0, 0);
    BYTE* p_dst_image_data = (BYTE*)dst->getPixel(0,0);
    UINT pixel_position;
    UINT bpp = src->getBytePerPix();
    int data_temp;
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            //BYTE* p_pixel_data = (BYTE*)src->getPixel(row, col);
            pixel_position = col + row * width;
            for(UCHAR i = 0; i < bpp; i++){
                //int data_temp = (int) (gain*p_pixel_data[i] + offset);
                data_temp = p_pixel_data[pixel_position];
                data_temp = (int) (gain*p_pixel_data[pixel_position] + offset);
                if(data_temp > SATURATED_PIXEL) data_temp = SATURATED_PIXEL;
                if(data_temp < 0) data_temp = 0;
                p_dst_image_data[pixel_position] = (BYTE)data_temp;
                //data_temp = p_pixel_data[pixel_position];
                //p_pixel_data[i] = (BYTE)data_temp;
            }
            //dst->setPixel(row, col, p_pixel_data);
        }
    }
}

void ImageProcessingContrastConversion::executeEnding() {}

ImageProcessingContrastConversion::~ImageProcessingContrastConversion(){
    // do nothing
}