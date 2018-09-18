#include <iostream>
#include "Bitmap.h"

int main() {
    Bitmap longPhaseImage("./testImage/LongPhaseX.bmp");
    Bitmap shortPhaseImage("./testImage/ShortPhaseX.bmp");
    Bitmap test(2048, 2048, 32);
    Pixel testPix(4);
    BYTE* pix_data;

    for(UINT width = 0; width < 2048; width++){
        for(UINT height = 0; height < 2048; height++){
            longPhaseImage.getPixel(width, height, &testPix);
            test.setPixel(width, height, &testPix);
            //printf("width = %d, height = %d, data is %x  %x  %x  %x\n", width, height, pix_data[0], pix_data[1], pix_data[2], pix_data[3]);
        }
    }
    test.writeBitmap("./testImage/testGenerate.bmp");
    return 0;
}