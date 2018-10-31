//
// Created by 俵京佑 on 2018/10/30.
//

#include "ImageProcessingAverageSmoothing.h"

#define mask_square_pixels (3)

ImageProcessingAverageSmoothing::ImageProcessingAverageSmoothing(Image* src_image,
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

void ImageProcessingAverageSmoothing::initializeMaskCoeff(){
    mask_coeff[0][0][0] = 1;
    mask_coeff[0][0][1] = 1;
    mask_coeff[0][0][2] = 1;
    mask_coeff[0][1][0] = 1;
    mask_coeff[0][1][1] = 4;
    mask_coeff[0][1][2] = 1;
    mask_coeff[0][2][0] = 1;
    mask_coeff[0][2][1] = 1;
    mask_coeff[0][2][2] = 1;
}

void ImageProcessingAverageSmoothing::initializeGainAndOffset(){
    gain = 12;
}

void ImageProcessingAverageSmoothing::storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE value){
    during_sum += value*mask_coeff[mask_pat_no][row][col];
//    for(int i = 0; i < 2; i++){
//        during_sum += value*mask_coeff[row][col];
//    }
}

int ImageProcessingAverageSmoothing::getResultPixel() {
    int temp = during_sum/gain;
    during_sum = 0;
    return temp;
}