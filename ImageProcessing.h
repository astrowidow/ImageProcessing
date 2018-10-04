//
// Created by 俵京佑 on 2018/09/25.
//

#ifndef IMAGEPROCESSING_PROCESSSTRATEGY_H
#define IMAGEPROCESSING_PROCESSSTRATEGY_H


#include "Bitmap.h"
#include "Pixel.h"

class ImageProcessing {
protected:
    Bitmap* dst;
    Bitmap* src;
    Pixel* pixel;
public:
    ImageProcessing(Bitmap* src_image,
                    Bitmap* dst_image);
    virtual void executeProcessing() = 0;
    virtual ~ImageProcessing();
};


#endif //IMAGEPROCESSING_PROCESSSTRATEGY_H
