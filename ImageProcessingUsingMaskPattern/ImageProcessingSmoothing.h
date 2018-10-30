//
// Created by 俵京佑 on 2018/10/30.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSMOOTHING_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSMOOTHING_H


#include "ImageProcessingUsingMaskPattern.h"

class ImageProcessingSmoothing : public ImageProcessingUsingMaskPattern
{
private:
    int during_sum;
    int gain;
public:
    ImageProcessingSmoothing(Image* src_image,
                             Image* dst_image,
                             UINT mask_square_pix);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    void storeMaskedPixels(UINT row, UINT col, BYTE value) override;
    int getResultPixel() override;
    ~ImageProcessingSmoothing() override = default;
};

#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSMOOTHING_H
