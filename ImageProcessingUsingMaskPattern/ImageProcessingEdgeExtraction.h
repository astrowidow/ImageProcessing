//
// Created by 俵京佑 on 2018/10/25.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTION_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTION_H

#include "ImageProcessingUsingMaskPattern.h"

class ImageProcessingEdgeExtraction : public ImageProcessingUsingMaskPattern
{
public:
    ImageProcessingEdgeExtraction(Image* src_image,
                                  Image* dst_image);
    void initializeGainAndOffset() override;
    void initializeMaskCoeff() override;
    ~ImageProcessingEdgeExtraction() = default;
};


#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGEDGEEXTRACTION_H
