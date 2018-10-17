#include <iostream>
#include "Bitmap.h"
#include "ImageProcessing/ImageProcessingContrastConversion.h"
#include "ImageProcessing/ImageProcessingGammaCorrection.h"

int main() {
    //Bitmap srcImage("../testImage/morning_glory.bmp");
    Bitmap srcImage("../testImage/lena_gray.bmp");
    //Bitmap shortPhaseImage("../testImage/lena_gray.bmp");
    Bitmap test(srcImage.getWidth(), srcImage.getHeight(), srcImage.getDepth());

    // strategy patternのテスト
    auto contrast_conversion = (ImageProcessing*) new ImageProcessingContrastConversion(&srcImage, &test, 3, -150);
    //auto contrast_conversion = (ImageProcessing*) new ImageProcessingGammaCorrection(&srcImage, &test, 2.2);

    clock_t start = clock();
    for(int i = 0; i < 16*1000; i++){
        contrast_conversion->execute();
    }
    clock_t end = clock();
    printf("execution time is %f", (float)(end - start)/CLOCKS_PER_SEC);

    contrast_conversion->execute();
    test.writeBitmap("../testImage/dstTest.bmp");
    //srcImage.writeBitmap("../testImage/dstTest.bmp");
    return 0;
}