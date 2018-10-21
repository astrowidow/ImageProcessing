//
// Created by 俵京佑 on 2018/10/22.
//

#include "ImageProcessingUsingResultTable.h"

ImageProcessingUsingResultTable::ImageProcessingUsingResultTable(Image* src_image, Image* dst_image)
        :src_base(src_image),
         dst_base(dst_image),
         height(src_image->getHeight()),
         width(src_image->getWidth()),
         byte_per_pixel(src_image->getBytePerPix())
{
}

void ImageProcessingUsingResultTable::execute(){
    // declaration
    Image* source = src_base;
    Image* destination = dst_base;
    BYTE pixel_data;

    // processing
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            for(UCHAR byte_num = 0; byte_num < byte_per_pixel; byte_num++){
                // gamma correction
                pixel_data = source->getPixelByte(row, col, byte_num);
                pixel_data = result_table[pixel_data];
                // set the data to dst_base
                destination->setPixelByte(row, col, pixel_data, byte_num);
            }
        }
    }
}