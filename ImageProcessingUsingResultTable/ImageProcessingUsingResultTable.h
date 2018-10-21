//
// Created by 俵京佑 on 2018/10/22.
//

#ifndef IMAGEPROCESSING_IMAGEPROCESSINGUSINGRESULTTABLE_H
#define IMAGEPROCESSING_IMAGEPROCESSINGUSINGRESULTTABLE_H

#include "../Image.h"
#include "../ImageProcessing.h"

class ImageProcessingUsingResultTable : public ImageProcessing
{
protected:
    Image* src_base;
    Image* dst_base;
    UINT height;
    UINT width;
    UINT byte_per_pixel;
    BYTE result_table[EIGHT_BITS_GRADATION_NUM];
public:
    ImageProcessingUsingResultTable(Image* src_image, Image* dst_image);
    virtual void execute() override;
    virtual ~ImageProcessingUsingResultTable() override = default;
};


#endif //IMAGEPROCESSING_IMAGEPROCESSINGUSINGRESULTTABLE_H
