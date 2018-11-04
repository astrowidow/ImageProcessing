//
// Created by 俵京佑 on 2018/11/04.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONSOBEL_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONSOBEL_H

#include "ImageProcessingUsingMaskPattern.h"


class ImageProcessingEdgeExtractionSobel : public ImageProcessingUsingMaskPattern
{
private:
    int* during_sum;
    double gain;
public:
    ImageProcessingEdgeExtractionSobel(Image* src_image,
                                       Image* dst_image);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    void storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE pixel_value) override;
    int getResultPixel() override;
    ~ImageProcessingEdgeExtractionSobel() override;
};


#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONSOBEL_H
