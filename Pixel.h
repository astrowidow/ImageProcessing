//
// Created by 俵京佑 on 2018/09/13.
//

#ifndef IMAGEPROCESSING_PIXEL_H
#define IMAGEPROCESSING_PIXEL_H
#include "common.h"
#include <cstdlib>
#include <cstring>

class Pixel {
private:
    UINT byte_per_pix;
    BYTE* data;
public:
    Pixel(UINT size);

    void setData(BYTE *data);

    UINT getByte_per_pix() const;
    BYTE *getData() const;

    virtual ~Pixel();
};


#endif //IMAGEPROCESSING_PIXEL_H
