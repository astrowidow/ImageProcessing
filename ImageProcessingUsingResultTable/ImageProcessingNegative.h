//
// Created by 俵京佑 on 2018/10/22.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGNEGATIVE_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGNEGATIVE_H

#include "ImageProcessingUsingResultTable.h"

class ImageProcessingNegative : public ImageProcessingUsingResultTable
{
private:
public:
    ImageProcessingNegative(Image* src_image, Image* dst_image);
    ~ImageProcessingNegative() override = default;
};


#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGNEGATIVE_H
