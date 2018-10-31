//
// Created by 俵京佑 on 2018/10/30.
//

#include "ImageProcessingSmoothing.h"

ImageProcessingSmoothing::ImageProcessingSmoothing(Image* src_image,
                                                   Image* dst_image,
                                                   UINT mask_square_pix)
        : ImageProcessingUsingMaskPattern(src_image,
                                          dst_image,
                                          mask_square_pix),
          during_sum(0)
{
    // initialize gain and offset
    initializeGainAndOffset();

    // initialize mask coeff
    initializeMaskCoeff();
}

void ImageProcessingSmoothing::initializeMaskCoeff(){
    for(int i = 0; i < mask_square_pixels; i++){
        for(int j = 0; j < mask_square_pixels; j++){
            mask_coeff[0][i][j] = 1;
        }
    }
}

void ImageProcessingSmoothing::initializeGainAndOffset(){
    gain = mask_square_pixels*mask_square_pixels;
}

void ImageProcessingSmoothing::storeMaskedPixels(int mask_pat_no, UINT row, UINT col, BYTE value){
    during_sum += value*mask_coeff[mask_pat_no][row][col];
}

int ImageProcessingSmoothing::getResultPixel() {
    int temp = during_sum/gain;
    during_sum = 0;
    return temp;
}