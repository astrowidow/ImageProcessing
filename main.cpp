#include <iostream>
#include "Bitmap.h"
#include "ImageProcessingUsingResultTable/ImageProcessingContrastConversion.h"
#include "ImageProcessingUsingResultTable/ImageProcessingGammaCorrection.h"
#include "ImageProcessingUsingResultTable/ImageProcessingHistogramExtension.h"
#include "ImageProcessingUsingResultTable/ImageProcessingSigmoidConversion.h"
#include "ImageProcessingUsingResultTable/ImageProcessingNegative.h"

int main() {
    Bitmap srcImage("../testImage/morning_glory.bmp");
    //Bitmap srcImage("../testImage/lena_gray.bmp");

    Bitmap test(srcImage.getWidth(), srcImage.getHeight(), srcImage.getDepth());
    //UINT* hist = test.calcHistogram();

    // strategy patternのテスト
    //auto algorithm = (ImageProcessing*) new ImageProcessingContrastConversion(&srcImage, &test, 3, -150);
    //auto algorithm = (ImageProcessing*) new ImageProcessingGammaCorrection(&srcImage, &test, 0.2);
    //auto algorithm = (ImageProcessing*) new ImageProcessingHistogramExtension(&srcImage, &test, 7000);
    //auto algorithm = (ImageProcessing*) new ImageProcessingSigmoidConversion(&srcImage, &test, 0.01);
    auto algorithm = (ImageProcessing*) new ImageProcessingNegative(&srcImage, &test);

//    clock_t start = clock();
//    for(int i = 0; i < 16*10; i++){
//        algorithm->execute();
//    }
//    clock_t end = clock();
//    printf("execution time is %f", (float)(end - start)/CLOCKS_PER_SEC);

    algorithm->execute();
    test.writeBitmap("../testImage/dstTest.bmp");
    //srcImage.writeBitmap("../testImage/dstTest.bmp");

    return 0;
}