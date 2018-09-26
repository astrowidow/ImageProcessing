//
// Created by 俵京佑 on 2018/09/25.
//

#ifndef IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H
#define IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H

#include "../ProcessStrategy.h"
#include "../Bitmap.h"

class ProcessStrategyContrastConversion : public ProcessStrategy
{
private:
    double gain;
    double offset;
public:
    ProcessStrategyContrastConversion(Bitmap* src_image, Bitmap* dst_image, double gain, double offset);
    void executeProcessing() override;
    ~ProcessStrategyContrastConversion() override;
};


#endif //IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H
