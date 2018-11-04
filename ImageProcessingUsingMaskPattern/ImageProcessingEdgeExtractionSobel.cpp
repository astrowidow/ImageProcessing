//
// Created by 俵京佑 on 2018/11/04.
//

#include <cmath>
#include "ImageProcessingEdgeExtractionSobel.h"

#define mask_square_pixels (3)
#define mask_pattern_num (2)

ImageProcessingEdgeExtractionSobel::ImageProcessingEdgeExtractionSobel(Image* src_image,
                                                                       Image* dst_image)
        : ImageProcessingUsingMaskPattern(src_image,
                                          dst_image,
                                          mask_square_pixels,
                                          mask_pattern_num)
{
    during_sum = new int[mask_pattern_num];
    for(int i = 0; i < mask_pattern_num; i++){
        during_sum[i] = 0;
    }

    // initialize gain and offset
    initializeGainAndOffset();

    // initialize mask coeff
    initializeMaskCoeff();
}

void ImageProcessingEdgeExtractionSobel::initializeMaskCoeff(){
    mask_coeff[0][0][0] =-1; mask_coeff[0][0][1] = 0; mask_coeff[0][0][2] = 1;
    mask_coeff[0][1][0] =-2; mask_coeff[0][1][1] = 0; mask_coeff[0][1][2] = 2;
    mask_coeff[0][2][0] =-1; mask_coeff[0][2][1] = 0; mask_coeff[0][2][2] = 1;

    mask_coeff[1][0][0] =-1; mask_coeff[1][0][1] =-2; mask_coeff[1][0][2] =-1;
    mask_coeff[1][1][0] = 0; mask_coeff[1][1][1] = 0; mask_coeff[1][1][2] = 0;
    mask_coeff[1][2][0] = 1; mask_coeff[1][2][1] = 2; mask_coeff[1][2][2] = 1;
}

void ImageProcessingEdgeExtractionSobel::initializeGainAndOffset(){
    //gain = 1;
    //offset = 0;
    gain = 8.0;
}

void ImageProcessingEdgeExtractionSobel::storeMaskedPixels(int mask_pat_no,
                                                           UINT row,
                                                           UINT col,
                                                           BYTE pixel_value){
    during_sum[mask_pat_no] += pixel_value*mask_coeff[mask_pat_no][row][col];
}

int ImageProcessingEdgeExtractionSobel::getResultPixel() {
    int sum_of_x_edge = during_sum[0];
    int sum_of_y_edge = during_sum[1];

    auto temp = (int)(sqrt((double)(sum_of_x_edge*sum_of_x_edge + sum_of_y_edge*sum_of_y_edge))/gain);

    for(int i = 0; i < mask_pattern_num; i++){
        during_sum[i] = 0;
    }
    return temp;
}

ImageProcessingEdgeExtractionSobel::~ImageProcessingEdgeExtractionSobel(){
    delete[] during_sum;
}