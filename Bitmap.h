//
// Created by 俵京佑 on 2018/09/11.
//

#ifndef IMAGEPROCESSING_BITMAP_H
#define IMAGEPROCESSING_BITMAP_H

#include <string>
#include "common.h"
#include "Pixel.h"
#include "Image.h"

// define macro
#define FILE_HEADER_SIZE (14)
#define CORE_HEADER_SIZE (12)
#define INFO_HEADER_SIZE (40)
#define CORE_PALLET_SET_SIZE (3)
#define INFO_PALLET_SET_SIZE (4)

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

class Bitmap : public Image
{
private:
    // important data
    UINT pallet_byte;
    UINT pallet_num;

    // data pointer
    ColorPallet* pallet_data;

    // header
    BitmapFileHeader file_header;
    BitmapCoreHeader core_header;
    BitmapInfoHeader info_header;

public:
    Bitmap(UINT width, UINT height, UINT depth);
    Bitmap(char* file_name);
    void writeBitmap(char *file_name);
    ~Bitmap() override;
};

#endif //IMAGEPROCESSING_BITMAP_H
