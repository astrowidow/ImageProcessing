//
// Created by 俵京佑 on 2018/10/30.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGAVERAGESMOOTHING_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGAVERAGESMOOTHING_H


#include "ImageProcessingUsingMaskPattern.h"

class ImageProcessingAverageSmoothing : public ImageProcessingUsingMaskPattern
{
private:
    int during_sum;
    int gain;
public:
    ImageProcessingAverageSmoothing(Image* src_image,
                             Image* dst_image);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    void storeMaskedPixels(UINT row, UINT col, BYTE value) override;
    int getResultPixel() override;
    ~ImageProcessingAverageSmoothing() override = default;
};

#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGAVERAGESMOOTHING_H
