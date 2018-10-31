//
// Created by 俵京佑 on 2018/10/30.
//

#include "ImageProcessingSharpening.h"

#define mask_square_pixels (3)

ImageProcessingSharpening::ImageProcessingSharpening(Image* src_image,
                                                     Image* dst_image)
        : ImageProcessingUsingMaskPattern(src_image,
                                          dst_image,
                                          mask_square_pixels),
          during_sum(0)
{
    // initialize gain and offset
    initializeGainAndOffset();

    // initialize mask coeff
    initializeMaskCoeff();
}

void ImageProcessingSharpening::initializeMaskCoeff(){
    mask_coeff[0][0][0] = 0;mask_coeff[0][0][1] = -1;mask_coeff[0][0][2] = 0;
    mask_coeff[0][1][0] = -1;mask_coeff[0][1][1] = 5;mask_coeff[0][1][2] = -1;
    mask_coeff[0][2][0] = 0;mask_coeff[0][2][1] = -1;mask_coeff[0][2][2] = 0;
}

void ImageProcessingSharpening::initializeGainAndOffset(){
    //gain = 1;
    //offset = 0;
}

void ImageProcessingSharpening::storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE value){
    during_sum += value*mask_coeff[mask_pat_no][row][col];
}

int ImageProcessingSharpening::getResultPixel() {
    int temp = during_sum;
    during_sum = 0;
    return temp;
}