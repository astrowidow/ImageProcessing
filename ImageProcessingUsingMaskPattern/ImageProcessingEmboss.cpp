//
// Created by 俵京佑 on 2018/10/30.
//

#include "ImageProcessingEmboss.h"

#define mask_square_pixels (3)

ImageProcessingEmboss::ImageProcessingEmboss(Image* src_image,
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

void ImageProcessingEmboss::initializeMaskCoeff(){
//    mask_coeff[0][0] = -2;mask_coeff[0][1] = -1;mask_coeff[0][2] = 0;
//    mask_coeff[1][0] = -1;mask_coeff[1][1] = 1;mask_coeff[1][2] = 1;
//    mask_coeff[2][0] = 0;mask_coeff[2][1] = 1;mask_coeff[2][2] = 2;
    mask_coeff[0][0][0] = -1;mask_coeff[0][0][1] = 0;mask_coeff[0][0][2] = 0;
    mask_coeff[0][1][0] = 0;mask_coeff[0][1][1] = 1;mask_coeff[0][1][2] = 0;
    mask_coeff[0][2][0] = 0;mask_coeff[0][2][1] = 0;mask_coeff[0][2][2] = 0;
}

void ImageProcessingEmboss::initializeGainAndOffset(){
    gain = 2;
    offset = 128;
}

void ImageProcessingEmboss::storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE value){
    during_sum += value*mask_coeff[mask_pat_no][row][col];
}

int ImageProcessingEmboss::getResultPixel() {
    int temp = during_sum/gain + offset;
    during_sum = 0;
    return temp;
}