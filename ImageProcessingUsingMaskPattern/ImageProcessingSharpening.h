//
// Created by 俵京佑 on 2018/10/30.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSHARPENING_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSHARPENING_H

#include "ImageProcessingUsingMaskPattern.h"

class ImageProcessingSharpening : public ImageProcessingUsingMaskPattern
{
private:
    int during_sum;
public:
    ImageProcessingSharpening(Image* src_image,
                              Image* dst_image);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    void storeMaskedPixels(UINT row, UINT col, BYTE value) override;
    int getResultPixel() override;
    ~ImageProcessingSharpening() override = default;
};

#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSHARPENING_H
