//
// Created by 俵京佑 on 2018/10/23.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGUSINGMASKPATTERN_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGUSINGMASKPATTERN_H

#include "../Image.h"
#include "../ImageProcessing.h"

class ImageProcessingUsingMaskPattern : public ImageProcessing
{
protected:
    Image* src_base;
    Image* dst_base;
    UINT height;
    UINT width;
    UINT byte_per_pixel;
public:
    ImageProcessingUsingMaskPattern(Image* src_image, Image* dst_image);
    virtual void execute() override;
    virtual ~ImageProcessingUsingMaskPattern() override = default;
};

#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGUSINGMASKPATTERN_H
