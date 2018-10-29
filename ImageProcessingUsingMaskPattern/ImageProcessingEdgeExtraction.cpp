//
// Created by 俵京佑 on 2018/10/25.
//

#include "ImageProcessingEdgeExtraction.h"
#define mask_square_pixels (3)

ImageProcessingEdgeExtraction::ImageProcessingEdgeExtraction(Image* src_image,
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

void ImageProcessingEdgeExtraction::initializeMaskCoeff(){
    mask_coeff[0][0] = 0;
    mask_coeff[0][1] = -1;
    mask_coeff[0][2] = 0;
    mask_coeff[1][0] = -1;
    mask_coeff[1][1] = 0;
    mask_coeff[1][2] = 1;
    mask_coeff[2][0] = 0;
    mask_coeff[2][1] = 1;
    mask_coeff[2][2] = 0;
}

void ImageProcessingEdgeExtraction::initializeGainAndOffset(){
    //gain = 1;
    //offset = 0;
}

void ImageProcessingEdgeExtraction::storeMaskedPixels(UINT row, UINT col, BYTE value){
    during_sum += value*mask_coeff[row][col];
}

int ImageProcessingEdgeExtraction::getResultPixel() {
    int temp = during_sum;
    during_sum = 0;
    return temp;
}