#include <iostream>
#include "Bitmap.h"
#include "ImageProcessing/ImageProcessingContrastConversion.h"

int main() {
    Bitmap longPhaseImage("../testImage/lena_gray.bmp");
    Bitmap shortPhaseImage("../testImage/black.bmp");
    //Bitmap shortPhaseImage("../testImage/lena_gray.bmp");
    Bitmap test(512, 512, 8);
    Pixel testPix(1);
    BYTE pix_data = 0;

    auto contrast_conversion = (ImageProcessing*) new ImageProcessingContrastConversion(&longPhaseImage, &test, 3, -150);
    // strategy patternのテスト

    clock_t start = clock();
    for(int i = 0; i < 16*1000; i++){
        contrast_conversion->execute();
    }
    clock_t end = clock();
    printf("execution time is %f", (float)(end - start)/CLOCKS_PER_SEC);

    test.writeBitmap("../testImage/contrastTestAuto.bmp");
    return 0;
}