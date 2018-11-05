//
// Created by 俵京佑 on 2018/11/04.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONROBERTS_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONROBERTS_H


#include "ImageProcessingUsingMaskPattern.h"


class ImageProcessingEdgeExtractionRoberts : public ImageProcessingUsingMaskPattern
{
private:
    int* during_sum;
    //double gain;
public:
    ImageProcessingEdgeExtractionRoberts(Image* src_image,
                                       Image* dst_image);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    void storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE pixel_value) override;
    int getResultPixel() override;
    ~ImageProcessingEdgeExtractionRoberts() override;
};


#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTIONROBERTS_H
