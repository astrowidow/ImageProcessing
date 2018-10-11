//
// Created by 俵京佑 on 2018/09/25.
//

#include "ImageProcessing.h"

ImageProcessing::ImageProcessing(UINT image_height, UINT image_width):height(image_height), width(image_width)
{
}
// Debug build
// テンプレートパターンを使った実装だと
// ... 512pix*512pix*8bit の画像に16*10回コントラスト変換実行
// ... ... execution time is 1.4952 [sec]
// ... 512pix*512pix*8bit の画像に16*100回コントラスト変換実行
// ... ... execution time is 14.043077 [sec]
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 134.921463 [sec]
// テンプレートパターンを使わない実装だと
// ... 512pix*512pix*8bit の画像に16*10回コントラスト変換実行
// ... ... execution time is 1.438288 [sec]
// ... 512pix*512pix*8bit の画像に16*100回コントラスト変換実行
// ... ... execution time is 13.527081 [sec]
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 132.275223 [sec]
// Release build
// テンプレートパターンを使った実装だと
// ... 512pix*512pix*8bit の画像に16*10回コントラスト変換実行
// ... ... execution time is 1.4952 [sec]
// ... 512pix*512pix*8bit の画像に16*100回コントラスト変換実行
// ... ... execution time is 14.043077 [sec]
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 134.921463 [sec]
// テンプレートパターンを使わない実装だと
// ... 512pix*512pix*8bit の画像に16*10回コントラスト変換実行
// ... ... execution time is 0.602235 [sec]
// ... 512pix*512pix*8bit の画像に16*100回コントラスト変換実行
// ... ... execution time is 5.148182 [sec]
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 49.928997 [sec]
// 全然差がない....

void ImageProcessing::execute(){
    //executeOpening();
    //for(UINT row = 0; row < height; row++){
        //for(UINT col = 0; col < width; col++){
            executeProcess();
        //}
    //}
    //executeEnding();
}



ImageProcessing::~ImageProcessing() {
}