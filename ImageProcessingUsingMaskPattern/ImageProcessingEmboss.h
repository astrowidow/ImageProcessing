//
// Created by 俵京佑 on 2018/10/30.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEMBOSS_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEMBOSS_H

#include "ImageProcessingUsingMaskPattern.h"

class ImageProcessingEmboss : public ImageProcessingUsingMaskPattern
{
private:
    int during_sum;
    int gain;
    int offset;
public:
    ImageProcessingEmboss(Image* src_image,
                          Image* dst_image);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    void storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE value) override;
    int getResultPixel() override;
    ~ImageProcessingEmboss() override = default;
};


#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEMBOSS_H
