//
// Created by 俵京佑 on 2018/09/25.
//

#include "ProcessStrategyContrastConversion.h"
#include "../Bitmap.h"

ProcessStrategyContrastConversion::ProcessStrategyContrastConversion
        (Bitmap* src_image,
         Bitmap* dst_image,
        double gain,
        double offset)
        :ProcessStrategy(src_image, dst_image), gain(gain), offset(offset)
{
    // do nothing
}

void ProcessStrategyContrastConversion::executeProcessing()
{
    for(UINT row = 0; row < src->height; row++){
        for(UINT col = 0; col < src->width; col++){
            if(src->getPixel(row, col, pixel) != 0){
                printf("error at get pixel: row = %d, col = %d", row+1, col+1);
            }
            BYTE* p_pixel_data = pixel->getData();
            for(UCHAR i = 0; i < src->byte_per_pix; i++){
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
    }
}

ProcessStrategyContrastConversion::~ProcessStrategyContrastConversion(){
    // do nothing
}