//
// Created by 俵京佑 on 2018/10/23.
//

#include "ImageProcessingUsingMaskPattern.h"

#define MASK_NUM (30)

ImageProcessingUsingMaskPattern::ImageProcessingUsingMaskPattern(Image* src_image,
                                                                 Image* dst_image,
                                                                 UINT mask_square_pixels,
                                                                 int mask_pat_num)
        :src_base(src_image),
         dst_base(dst_image),
         height(src_image->getHeight()),
         width(src_image->getWidth()),
         byte_per_pixel(src_image->getBytePerPix()),
         mask_square_pixels(mask_square_pixels),
         mask_pat_num(mask_pat_num)
{
    auto is_odd = (bool)(mask_square_pixels%2);
    if(!is_odd){
        mask_square_pixels = mask_square_pixels + 1;
        printf("mask square pixels num should be odd number!\n The number is modified to %d.\n", mask_square_pixels);
    }
    mask_max_idx = mask_square_pixels/2;
    mask_min_idx = -mask_max_idx;

    // initial malloc mask pattern

    mask_coeff = new int**[MASK_NUM];
    for(int j = 0; j < MASK_NUM; j++){
        mask_coeff[j] = new int*[mask_square_pixels];
        for(int i = 0; i < mask_square_pixels; i++){
            mask_coeff[j][i] = new int[mask_square_pixels];
        }
    }

//    // initialize gain and offset
//    initializeGainAndOffset();
//
//    // initialize mask coeff
//    initializeMaskCoeff();
}

// 速度測定結果
// 512*512*1サイズに対して，16*100回処理を実施
// 処理ベタ書きのとき           -> 16.65 sec
// 仮想関数呼び出しにした時      -> 23.62 sec
void ImageProcessingUsingMaskPattern::execute(){
    // declaration
    Image* source = src_base;
    Image* destination = dst_base;
    int pixel_data;

    // processing
    auto* during_sum = new int[byte_per_pixel];
    // for pixel sweep
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            // for byte sweep
            for(UINT byte_num = 0; byte_num < byte_per_pixel; byte_num++){
                //during_sum[byte_num] = 0; // initialize temp buffer

                // for mask pattern sweep
                for(int mask_pat_no = 0; mask_pat_no < mask_pat_num; mask_pat_no++){
                    for(int row_diff = mask_min_idx; row_diff <= mask_max_idx; row_diff++){
                        for(int col_diff = mask_min_idx; col_diff <= mask_max_idx; col_diff++){
                            //during_sum[byte_num] += source->getPixelByteWithLimit(row + row_diff, col + col_diff, byte_num)
                            //                            *mask_coeff[row_diff + mask_max_idx][col_diff + mask_max_idx];
//                        mask_result[row_diff + mask_max_idx][col_diff + mask_max_idx]
//                                = source->getPixelByteWithLimit(row + row_diff, col + col_diff, byte_num)
//                                  *mask_coeff[row_diff + mask_max_idx][col_diff + mask_max_idx];
                            storeMaskedPixels(mask_pat_no,
                                              (UINT)(row_diff + mask_max_idx),
                                              (UINT)(col_diff + mask_max_idx),
                                              source->getPixelByteWithLimit(row + row_diff, col + col_diff, byte_num));
                        }
                    }
                }

                //pixel_data = during_sum[byte_num]/gain + offset;
                pixel_data = getResultPixel();
                if(pixel_data > BYTE_MAX) pixel_data = BYTE_MAX;
                if(pixel_data < 0) pixel_data = 0;
                // set the data to dst_base
                destination->setPixelByte(row, col, (BYTE)pixel_data, byte_num);
            }
        }
    }
    delete[] during_sum;
}

ImageProcessingUsingMaskPattern::~ImageProcessingUsingMaskPattern(){
    for(int j = 0; j < MASK_NUM; j++){
        for(int i = 0; i < mask_square_pixels; i++){
            delete[] mask_coeff[j][i];
        }
        delete[] mask_coeff[j];
    }
    delete[] mask_coeff;
}