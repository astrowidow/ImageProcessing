#include <iostream>
#include "Bitmap.h"

int main() {
    Bitmap longPhaseImage("./testImage/LongPhaseX.bmp");
    Bitmap shortPhaseImage("./testImage/ShortPhaseX.bmp");
    Bitmap test(2048, 2048, 32);
    Pixel testPix(4);

    for(UINT width = 0; width < 512; width++){
        for(UINT height = 0; height < 512; height++){
            longPhaseImage.getPixel(height, width, &testPix);
            shortPhaseImage.setPixel(height, width, &testPix);
        }
    }
    shortPhaseImage.writeBitmap("./testImage/testGenerate.bmp");
    return 0;
}