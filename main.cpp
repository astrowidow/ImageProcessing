#include <iostream>
#include "Bitmap.h"
#include "./ProcessStrategy/ProcessStrategyContrastConversion.h"

int main() {
    //Bitmap longPhaseImage("./testImage/LongPhaseX.bmp");
    Bitmap longPhaseImage("./testImage/lena_gray.bmp");
    Bitmap shortPhaseImage("./testImage/lena_gray.bmp");
    Bitmap test(512, 512, 8);
    Pixel testPix(1);
    BYTE pix_data = 0;

    testPix.setData(&pix_data);
    for(UINT width = 0; width < 512; width++){
        for(UINT height = 0; height < 512; height++){
            shortPhaseImage.setPixel(width, height, &testPix);
        }
    }
    shortPhaseImage.writeBitmap("./testImage/black.bmp");

    for(UINT width = 0; width < 512; width++){
        for(UINT height = 0; height < 512; height++){
            longPhaseImage.getPixel(width, height, &testPix);
            shortPhaseImage.setPixel(width, height, &testPix);
            test.setPixel(width, height, &testPix);
            //printf("width = %d, height = %d, data is %x  %x  %x  %x\n", width, height, pix_data[0], pix_data[1], pix_data[2], pix_data[3]);
        }
    }
    shortPhaseImage.writeBitmap("./testImage/testGenerateByShortPhaseImage.bmp");
    test.writeBitmap("./testImage/testGenerateByTest.bmp");
    // strategy patternのテスト
    ProcessStrategy* contrast_conversion = (ProcessStrategy*) new ProcessStrategyContrastConversion(&longPhaseImage, &test, 3, -150);
    contrast_conversion->executeProcessing();
    test.writeBitmap("./testImage/contrastTest.bmp");
    return 0;
}