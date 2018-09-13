//
// Created by 俵京佑 on 2018/09/11.
//

#ifndef IMAGEPROCESSING_BITMAP_H
#define IMAGEPROCESSING_BITMAP_H

#include <string>
#include "common.h"
#include "Pixel.h"

struct BitmapFileHeader{
    char type[2];
    UINT size;
    USHORT reserved1;
    USHORT reserved2;
    int offset_byte;
};

struct BitmapCoreHeader{
    UINT size;
    USHORT width;
    USHORT height;
    USHORT planes;
    USHORT bit_count;
};

struct BitmapInfoHeader{
    UINT size;
    UINT width;
    UINT height;
    USHORT planes;
    USHORT bit_count;
    UINT compression;
    UINT data_size;
    UINT x_pix_per_meter;
    UINT y_pix_per_meter;
    UINT num_pallet_color;
    UINT idx_important_pallet;
};

class Bitmap {
private:
    UINT width;
    UINT height;
    UINT depth;
    UINT byte_per_pix;
    BYTE* data;

    // header
    BitmapFileHeader file_header;
    BitmapCoreHeader core_header;
    BitmapInfoHeader info_header;

public:
    Bitmap(UINT width, UINT height, UINT depth);
    Bitmap(char* file_name);
    UCHAR getPixel(UINT row, UINT col, Pixel* dst_pixel);
    UCHAR setPixel(UINT row, UINT col, Pixel* src_pixel);
    virtual ~Bitmap();

private:
    bool checkBytePerPixel(Pixel* arg_pixel);
};

#endif //IMAGEPROCESSING_BITMAP_H
