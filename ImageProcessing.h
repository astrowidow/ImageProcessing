//
// Created by 俵京佑 on 2018/09/25.
//

#ifndef IMAGEPROCESSING_PROCESSSTRATEGY_H
#define IMAGEPROCESSING_PROCESSSTRATEGY_H

#include "Bitmap.h"
#include "Pixel.h"

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
// ... ... execution time is 0.715390 [sec]
// ... 512pix*512pix*8bit の画像に16*100回コントラスト変換実行
// ... ... execution time is 6.248881 [sec]
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 56.505589 [sec]
// テンプレートパターンを使わない実装だと
// ... 512pix*512pix*8bit の画像に16*10回コントラスト変換実行
// ... ... execution time is 0.591836 [sec]
// ... 512pix*512pix*8bit の画像に16*100回コントラスト変換実行
// ... ... execution time is 4.647976 [sec]
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 49.928997 [sec]
// 中の通常関数呼び出しを全部手動で展開すると
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 19.977270 [sec]
// 最終的にインライン化して
// ... 512pix*512pix*8bit の画像に16*1000回コントラスト変換実行
// ... ... execution time is 24.176504 [sec] まで高速化！！！

class ImageProcessing {
public:
    ImageProcessing() = default;
    virtual void execute() = 0;
    virtual ~ImageProcessing() = default;
};


#endif //IMAGEPROCESSING_PROCESSSTRATEGY_H
