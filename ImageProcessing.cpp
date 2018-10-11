//
// Created by 俵京佑 on 2018/09/25.
//

#include "ImageProcessing.h"

ImageProcessing::ImageProcessing(UINT image_height, UINT image_width):height(image_height), width(image_width)
{
}

// テンプレートパターンを使った実装だと
// ... 512pix*512pix*8bit の画像に16*10回コントラスト変換実行
// ... ... execution time is 1.4952 [sec]
// ... 512pix*512pix*8bit の画像に16*100回コントラスト変換実行
// ... ... execution time is 14.043077 [sec]
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 134.921463 [sec]

void ImageProcessing::execute(){
    executeOpening();
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            executeProcess(row, col);
        }
    }
    executeEnding();
}

ImageProcessing::~ImageProcessing() {
}