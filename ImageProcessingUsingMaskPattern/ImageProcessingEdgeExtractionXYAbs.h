//
// Created by 俵京佑 on 2018/11/04.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONXYABS_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONXYABS_H


#include "ImageProcessingUsingMaskPattern.h"


class ImageProcessingEdgeExtractionXYAbs : public ImageProcessingUsingMaskPattern
{
private:
    int* during_sum;
public:
    ImageProcessingEdgeExtractionXYAbs(Image* src_image,
                                  Image* dst_image);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    void storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE pixel_value) override;
    int getResultPixel() override;
    ~ImageProcessingEdgeExtractionXYAbs() override;
};


#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONXYABS_H
