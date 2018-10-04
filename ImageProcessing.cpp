//
// Created by 俵京佑 on 2018/09/25.
//

#include "ImageProcessing.h"

ImageProcessing::ImageProcessing(Bitmap* src_image,
                                 Bitmap* dst_image):src(src_image), dst(dst_image)
{
    pixel = new Pixel(src->byte_per_pix);
}

ImageProcessing::~ImageProcessing() {
    delete pixel;
}