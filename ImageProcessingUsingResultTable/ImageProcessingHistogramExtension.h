//
// Created by 俵京佑 on 2018/10/18.
//

#ifndef IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H
#define IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H

#include "ImageProcessingUsingResultTable.h"

class ImageProcessingHistogramExtension : public ImageProcessingUsingResultTable
{
private:
    UINT neglect_threshold;
    BYTE* max_pixel;
    BYTE* min_pixel;

    // redefinition of result table
    BYTE** result_table;
public:
    ImageProcessingHistogramExtension(Image* src_image,
                                      Image* dst_image,
                                      UINT neglect_threshold = 1); // threshold for store the limit value
    void execute() override;
    ~ImageProcessingHistogramExtension() override;
private:
    void initialize();
};


#endif //IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H
