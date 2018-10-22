//
// Created by 俵京佑 on 2018/10/22.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSOLARIZATION_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSOLARIZATION_H

#include "ImageProcessingUsingResultTable.h"


class ImageProcessingSolarization : public ImageProcessingUsingResultTable
{
private:
    double wave_num;
public:
    ImageProcessingSolarization(Image* src_image, Image* dst_image, double wave_num);
    ~ImageProcessingSolarization() override = default;
};

#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSOLARIZATION_H
