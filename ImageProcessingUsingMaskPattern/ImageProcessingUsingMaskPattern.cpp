//
// Created by 俵京佑 on 2018/10/23.
//

#include "ImageProcessingUsingMaskPattern.h"

ImageProcessingUsingMaskPattern::ImageProcessingUsingMaskPattern(Image* src_image, Image* dst_image, UINT mask_square_pixels)
        :src_base(src_image),
         dst_base(dst_image),
         height(src_image->getHeight()),
         width(src_image->getWidth()),
         byte_per_pixel(src_image->getBytePerPix()),
         mask_square_pixels(mask_square_pixels)
{
    auto is_odd = (bool)(mask_square_pixels%2);
    if(!is_odd){
        mask_square_pixels = mask_square_pixels + 1;
        printf("mask square pixels num should be odd number!\n The number is modified to %d.\n", mask_square_pixels);
    }
    mask_max_idx = mask_square_pixels/2;
    mask_min_idx = -mask_max_idx;

    // initial malloc mask pattern
    mask_coeff = new int*[mask_square_pixels];
    mask_result = new int*[mask_square_pixels];
    for(int i = 0; i < mask_square_pixels; i++){
        mask_coeff[i] = new int[mask_square_pixels];
        mask_result[i] =  new int[mask_square_pixels];
    }

    // initial malloc mask result


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
                for(int row_diff = mask_min_idx; row_diff <= mask_max_idx; row_diff++){
                    for(int col_diff = mask_min_idx; col_diff <= mask_max_idx; col_diff++){
                        //during_sum[byte_num] += source->getPixelByteWithLimit(row + row_diff, col + col_diff, byte_num)
                        //                            *mask_coeff[row_diff + mask_max_idx][col_diff + mask_max_idx];
//                        mask_result[row_diff + mask_max_idx][col_diff + mask_max_idx]
//                                = source->getPixelByteWithLimit(row + row_diff, col + col_diff, byte_num)
//                                  *mask_coeff[row_diff + mask_max_idx][col_diff + mask_max_idx];
                        storeMaskedPixels((UINT)(row_diff + mask_max_idx), (UINT)(col_diff + mask_max_idx), source->getPixelByteWithLimit(row + row_diff, col + col_diff, byte_num));
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
    for(int i = 0; i < mask_square_pixels; i++){
        delete[] mask_coeff[i];
        delete[] mask_result[i];
    }
    delete[] mask_result;
    delete[] mask_coeff;
}