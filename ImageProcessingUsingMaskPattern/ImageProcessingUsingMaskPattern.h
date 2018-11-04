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
    UINT mask_square_pixels;
    // initialize in constructor
    int*** mask_coeff;
    int mask_pat_num;
    int mask_min_idx;
    int mask_max_idx;
public:
    ImageProcessingUsingMaskPattern(Image* src_image,
                                    Image* dst_image,
                                    UINT mask_square_pixels,
                                    int mask_pat_num = 1);
    virtual void execute() override;
    virtual void initializeGainAndOffset() = 0;
    virtual void initializeMaskCoeff() = 0;
    virtual void storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE pixel_value) = 0;
    virtual int getResultPixel() = 0;
    virtual ~ImageProcessingUsingMaskPattern() override;
};

#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGUSINGMASKPATTERN_H
