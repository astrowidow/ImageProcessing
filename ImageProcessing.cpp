//
// Created by 俵京佑 on 2018/09/25.
//

#include "ImageProcessing.h"

ImageProcessing::ImageProcessing(UINT image_height, UINT image_width):height(image_height), width(image_width)
{
}

void ImageProcessing::execute(){
    executeOpening();
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            executeProcess(row, col);
        }
    }
    executeEnding();
}

ImageProcessing::~ImageProcessing() {
}