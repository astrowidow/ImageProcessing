#include <iostream>
#include "Bitmap.h"
#include "ImageProcessingUsingResultTable/ImageProcessingContrastConversion.h"
#include "ImageProcessingUsingResultTable/ImageProcessingGammaCorrection.h"
#include "ImageProcessingUsingResultTable/ImageProcessingHistogramExtension.h"
#include "ImageProcessingUsingResultTable/ImageProcessingSigmoidConversion.h"
#include "ImageProcessingUsingResultTable/ImageProcessingNegative.h"
#include "ImageProcessingUsingResultTable/ImageProcessingSolarization.h"
#include "ImageProcessingUsingMaskPattern/ImageProcessingEdgeExtractionX.h"
#include "ImageProcessingUsingMaskPattern/ImageProcessingSmoothing.h"
#include "ImageProcessingUsingMaskPattern/ImageProcessingAverageSmoothing.h"
#include "ImageProcessingUsingMaskPattern/ImageProcessingSharpening.h"
#include "ImageProcessingUsingMaskPattern/ImageProcessingEmboss.h"
#include "ImageProcessingUsingMaskPattern/ImageProcessingEdgeExtractionXYAbs.h"
#include "ImageProcessingUsingMaskPattern/ImageProcessingEdgeExtractionSobel.h"

int main() {
    Bitmap srcImage("../testImage/morning_glory.bmp");
    //Bitmap srcImage("../testImage/lena_gray.bmp");

    Bitmap test(srcImage.getWidth(), srcImage.getHeight(), srcImage.getDepth());
    Bitmap test_(srcImage.getWidth(), srcImage.getHeight(), srcImage.getDepth());


    // strategy patternのテスト
    //auto algorithm = (ImageProcessing*) new ImageProcessingContrastConversion(&srcImage, &test, 3, -150);
    //auto algorithm = (ImageProcessing*) new ImageProcessingGammaCorrection(&srcImage, &test, 0.2);
    //auto algorithm = (ImageProcessing*) new ImageProcessingHistogramExtension(&srcImage, &test, 7000);
    //auto algorithm = (ImageProcessing*) new ImageProcessingSigmoidConversion(&srcImage, &test, 0.01);
    //auto algorithm = (ImageProcessing*) new ImageProcessingNegative(&srcImage, &test);
    //auto algorithm = (ImageProcessing*) new ImageProcessingSolarization(&srcImage, &test, 3);
    //auto algorithm = (ImageProcessing*) new ImageProcessingEdgeExtractionX(&srcImage, &test);
    auto algorithm = (ImageProcessing*) new ImageProcessingEdgeExtractionXYAbs(&srcImage, &test);
    //auto algorithm = (ImageProcessing*) new ImageProcessingEdgeExtractionSobel(&srcImage, &test);
    //auto algorithm = (ImageProcessing*) new ImageProcessingSmoothing(&srcImage, &test, 10);
    //auto algorithm = (ImageProcessing*) new ImageProcessingAverageSmoothing(&srcImage, &test);
    //auto algorithm = (ImageProcessing*) new ImageProcessingSharpening(&srcImage, &test);
    //auto algorithm = (ImageProcessing*) new ImageProcessingEmboss(&srcImage, &test);
    auto algorithm1 = (ImageProcessing*) new ImageProcessingHistogramExtension(&test, &test_, 1);

//    clock_t start = clock();
//    for(int i = 0; i < 16*100; i++){
//        algorithm->execute();
//    }
//    clock_t end = clock();
//    printf("execution time is %f", (float)(end - start)/CLOCKS_PER_SEC);

    algorithm->execute();
    algorithm1->execute();
    test_.writeBitmap("../testImage/dstTest_.bmp");
    test.writeBitmap("../testImage/dstTest.bmp");

    delete algorithm;
    //delete algorithm1;

    return 0;
}