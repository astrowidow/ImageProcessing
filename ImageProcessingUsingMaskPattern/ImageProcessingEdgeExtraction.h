//
// Created by 俵京佑 on 2018/10/25.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTION_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTION_H

#include "ImageProcessingUsingMaskPattern.h"

class ImageProcessingEdgeExtraction : public ImageProcessingUsingMaskPattern
{
private:
    int during_sum;
public:
    ImageProcessingEdgeExtraction(Image* src_image,
                                  Image* dst_image);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    void storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE value) override;
    int getResultPixel() override;
    ~ImageProcessingEdgeExtraction() override = default;
};


#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTION_H
