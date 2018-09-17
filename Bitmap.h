//
// Created by 俵京佑 on 2018/09/11.
//

#ifndef IMAGEPROCESSING_BITMAP_H
#define IMAGEPROCESSING_BITMAP_H

#include <string>
#include "common.h"
#include "Pixel.h"

// define macro
#define FILE_HEADER_SIZE (14)
#define CORE_HEADER_SIZE (12)
#define INFO_HEADER_SIZE (40)

// define enum
enum Compression_format{
    BI_RGB,
    BI_RLE8,
    BI_RLE4,
    Bitfileids,
};

// define struct used in Bitmap class
struct BitmapFileHeader{
    char type[2];
    UINT size;
    USHORT reserved1;
    USHORT reserved2;
    int offset_byte;
};

struct BitmapCoreHeader{
    UINT size;
    UINT width;
    UINT height;
    USHORT planes;
    USHORT bit_count;
};

struct BitmapInfoHeader{
    UINT compression;
    UINT data_size;
    UINT x_pix_per_meter;
    UINT y_pix_per_meter;
    UINT num_pallet_color;
    UINT idx_important_pallet;
};

struct ColorPallet{
    UCHAR r;
    UCHAR g;
    UCHAR b;
    UCHAR padding;
};

class Bitmap {
private:
    // important data
    UINT width;
    UINT height;
    UINT depth;
    UINT byte_per_pix;
    UINT data_size;

    // data pointer
    ColorPallet* pallet_data;
    BYTE* offset_data;
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
    UINT calcBytePerPixel(UINT depth);
    void readColorPalletData(FILE* fp, int num_pallet_color);
};

#endif //IMAGEPROCESSING_BITMAP_H
