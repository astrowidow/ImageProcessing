//
// Created by 俵京佑 on 2018/09/25.
//

#ifndef IMAGEPROCESSING_PROCESSSTRATEGY_H
#define IMAGEPROCESSING_PROCESSSTRATEGY_H


#include "Bitmap.h"

class ProcessStrategy {
protected:
    Bitmap* dst;
    Bitmap* src;
    Pixel* pixel;
public:
    ProcessStrategy(Bitmap* src_image,
                    Bitmap* dst_image);
    virtual void executeProcessing() = 0;
    virtual ~ProcessStrategy();
};


#endif //IMAGEPROCESSING_PROCESSSTRATEGY_H
