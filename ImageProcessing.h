//
// Created by 俵京佑 on 2018/09/25.
//

#ifndef IMAGEPROCESSING_PROCESSSTRATEGY_H
#define IMAGEPROCESSING_PROCESSSTRATEGY_H


#include "Bitmap.h"
#include "Pixel.h"

class ImageProcessing {
protected:
    UINT height;
    UINT width;
public:
    ImageProcessing(UINT image_height, UINT image_width);
    void execute();
    virtual ~ImageProcessing();
private:
    virtual void executeOpening() = 0;
    virtual void executeProcess() = 0;
    virtual void executeEnding() = 0;
};


#endif //IMAGEPROCESSING_PROCESSSTRATEGY_H
