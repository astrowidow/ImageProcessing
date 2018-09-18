//
// Created by 俵京佑 on 2018/09/11.
//
#include <cstdlib>
#include <cstring>
#include "Bitmap.h"

Bitmap::Bitmap(UINT w, UINT h, UINT d):width(w), height(h), depth(d) {
    byte_per_pix = calcBytePerPixel(depth);
    data_size = width * height * byte_per_pix;
    // malloc
    pallet_data = (ColorPallet*)malloc(sizeof(ColorPallet));
    offset_data = (BYTE*)malloc(sizeof(BYTE));
    data = (BYTE*)malloc(data_size);
}

Bitmap::Bitmap(char* file_name){
    // open file
    FILE* fp;
    fp = fopen(file_name, "rb");

    // read header information
    UINT data_num = 1;
    fread(&file_header.type, sizeof(file_header.type), data_num, fp);
    fread(&file_header.size, sizeof(file_header.size), data_num, fp);
    fread(&file_header.reserved1, sizeof(file_header.reserved1), data_num, fp);
    fread(&file_header.reserved2, sizeof(file_header.reserved2), data_num, fp);
    fread(&file_header.offset_byte, sizeof(file_header.offset_byte), data_num, fp);

    fread(&core_header.size, sizeof(core_header.size), data_num, fp);
    fread(&core_header.width, sizeof(core_header.width), data_num, fp);
    fread(&core_header.height, sizeof(core_header.height), data_num, fp);
    fread(&core_header.planes, sizeof(core_header.planes), data_num, fp);
    fread(&core_header.bit_count, sizeof(core_header.bit_count), data_num, fp);

    // if header style is "bitmap info header",
    // read additional data
    if(core_header.size == INFO_HEADER_SIZE){
        fread(&info_header.compression, sizeof(info_header.compression), data_num, fp);
        fread(&info_header.data_size, sizeof(info_header.data_size), data_num, fp);
        fread(&info_header.x_pix_per_meter, sizeof(info_header.x_pix_per_meter), data_num, fp);
        fread(&info_header.y_pix_per_meter, sizeof(info_header.y_pix_per_meter), data_num, fp);
        fread(&info_header.num_pallet_color, sizeof(info_header.num_pallet_color), data_num, fp);
        fread(&info_header.idx_important_pallet, sizeof(info_header.idx_important_pallet), data_num, fp);
    }

    // support only uncompressed bitmap
    if((core_header.size == INFO_HEADER_SIZE)
       && (info_header.compression != BI_RGB)){
        printf("Only uncompressed format is supported !!");
    }

    // read pallet data
    int num_pallet_color = 0;
    if(core_header.size == INFO_HEADER_SIZE){
        num_pallet_color = info_header.num_pallet_color;
        readColorPalletData(fp, num_pallet_color);
    }
    else if(core_header.size == CORE_HEADER_SIZE) {
        // TO BE IMPLEMENTED
        num_pallet_color = 0;
        readColorPalletData(fp, num_pallet_color);
    }

    // advance the file pointer to data part
    // ... there is the case that info header doesn't include num_pallet_color
    UINT offset_byte;
    offset_byte = file_header.offset_byte - FILE_HEADER_SIZE - core_header.size - num_pallet_color;
    // ... read offset data
    offset_data = (BYTE*)malloc(offset_byte);
    fread(offset_data, offset_byte, data_num, fp);

    // read image data
    // ... get byte per pixel
    UINT byte_p_pix = calcBytePerPixel(core_header.bit_count);
    // ... get image data size
    UINT image_data_size = core_header.height*core_header.width*byte_p_pix;
    // ... read image data
    data = (BYTE*)malloc(image_data_size);
    fread(data, image_data_size, data_num, fp);

    // set important parameter
    width = core_header.width;
    height = core_header.height;
    depth = core_header.bit_count;
    byte_per_pix = byte_p_pix;
    data_size = image_data_size;

    // close file
    fclose(fp);
}

UCHAR Bitmap::getPixel(UINT row,
                       UINT col,
                       Pixel* dst_pixel) // if this argument is not pointer, Pixel instance (malloc) is executed every time
{
    // select the nearest pixel if the row and the col refer out of an image
    UCHAR get_status = 0;
    if(row < 0){
        row = 0;
        get_status = 1;
    }
    else if(row >= height){
        row = height - 1;
        get_status = 1;
    }
    if(col < 0){
        col = 0;
        get_status = 1;
    }
    else if(col >= width) {
        col = width - 1;
        get_status = 1;
    }
    bool is_match_depth = checkBytePerPixel(dst_pixel);
    if(!is_match_depth) get_status = 2;

    if(get_status == 0){
        // get an address of the referred pixel
        UINT pixel_position = col + row * width;
        dst_pixel->setData(&data[pixel_position*byte_per_pix]);
    }
    else{
        printf("setting error occurred. Error: %d.\n", get_status);
    }

    return get_status;
}

UCHAR Bitmap::setPixel(UINT row,
                       UINT col,
                       Pixel* src_pixel) // prevent malloc from execution by using pointer
{
    UCHAR set_status = 0;

    // error check !
    if(row < 0 || height <= row) set_status = 1;
    if(col < 0 || width <= col) set_status = 1;
    bool is_match_depth = checkBytePerPixel(src_pixel);
    if(!is_match_depth) set_status = 2;

    if(set_status == 0){
        // get an address of the referred pixel
        UINT pixel_position = col + row * width;
        memcpy(&data[pixel_position*byte_per_pix], src_pixel->getData(), byte_per_pix);
    } else {
        printf("setting error occured. Error: %d.\n", set_status);
    }

    return set_status;
}

void Bitmap::writeBitmap(char *file_name){
    // open file
    FILE* fp;
    fp = fopen(file_name, "wb");

    // if header file is prepared,
    // use the header
    UINT data_num = 1;
    if(file_header.type[0] == 'B'
       && file_header.type[1] == 'M'){
        // file header
        fwrite(file_header.type, sizeof(file_header.type), data_num, fp);
        fwrite(&file_header.size, sizeof(file_header.size), data_num, fp);
        fwrite(&file_header.reserved1, sizeof(file_header.reserved1), data_num, fp);
        fwrite(&file_header.reserved2, sizeof(file_header.reserved2), data_num, fp);
        fwrite(&file_header.offset_byte, sizeof(file_header.offset_byte), data_num, fp);
        fwrite(&core_header.size, sizeof(core_header.size), data_num, fp);
        // information header
        if(core_header.size == CORE_HEADER_SIZE){
            USHORT width = (USHORT)core_header.width;
            fwrite(&width, sizeof(width), data_num, fp);
            USHORT height = (USHORT)core_header.height;
            fwrite(&height, sizeof(height), data_num, fp);

            fwrite(&core_header.planes, sizeof(core_header.planes), data_num, fp);
            fwrite(&core_header.bit_count, sizeof(core_header.bit_count), data_num, fp);

            UINT num_pallet_color = 0;
            for(UINT i = 0; i < num_pallet_color/CORE_HEADER_SIZE; i++){
                fwrite(&pallet_data[i].b, sizeof(pallet_data[i].b), data_num, fp);
                fwrite(&pallet_data[i].g, sizeof(pallet_data[i].g), data_num, fp);
                fwrite(&pallet_data[i].r, sizeof(pallet_data[i].r), data_num, fp);
            }
        }
        else if(core_header.size == INFO_HEADER_SIZE){
            fwrite(&core_header.width, sizeof(core_header.width), data_num, fp);
            fwrite(&core_header.height, sizeof(core_header.height), data_num, fp);
            fwrite(&core_header.planes, sizeof(core_header.planes), data_num, fp);
            fwrite(&core_header.bit_count, sizeof(core_header.bit_count), data_num, fp);

            fwrite(&info_header.compression, sizeof(info_header.compression), data_num, fp);
            fwrite(&info_header.data_size, sizeof(info_header.data_size), data_num, fp);
            fwrite(&info_header.x_pix_per_meter, sizeof(info_header.x_pix_per_meter), data_num, fp);
            fwrite(&info_header.y_pix_per_meter, sizeof(info_header.y_pix_per_meter), data_num, fp);
            fwrite(&info_header.num_pallet_color, sizeof(info_header.num_pallet_color), data_num, fp);
            fwrite(&info_header.idx_important_pallet, sizeof(info_header.idx_important_pallet), data_num, fp);

            for(UINT i = 0; i < info_header.num_pallet_color/INFO_HEADER_SIZE; i++){
                fwrite(&pallet_data[i].b, sizeof(pallet_data[i].b), data_num, fp);
                fwrite(&pallet_data[i].g, sizeof(pallet_data[i].g), data_num, fp);
                fwrite(&pallet_data[i].r, sizeof(pallet_data[i].r), data_num, fp);
                fwrite(&pallet_data[i].padding, sizeof(pallet_data[i].padding), data_num, fp);
            }
        }
    }
    else {// if there isn't prepared header...
        // ... write file header
        UCHAR type[] = "BM";
        fwrite(&type[0], sizeof(UCHAR), data_num, fp);
        fwrite(&type[1], sizeof(UCHAR), data_num, fp);

        UINT file_size = data_size + FILE_HEADER_SIZE + INFO_HEADER_SIZE;
        fwrite(&file_size, sizeof(file_size), data_num, fp);

        USHORT reserved_data = 0;
        fwrite(&reserved_data, sizeof(reserved_data), data_num, fp);
        fwrite(&reserved_data, sizeof(reserved_data), data_num, fp);

        UINT offset_byte = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
        fwrite(&offset_byte, sizeof(offset_byte), data_num, fp);

        // ... write info headeer
        UINT info_header_size = INFO_HEADER_SIZE;
        fwrite(&info_header_size, sizeof(info_header_size), data_num, fp);

        fwrite(&width, sizeof(width), data_num, fp);
        fwrite(&height, sizeof(height), data_num, fp);

        USHORT plane_num = 1; // always 1
        fwrite(&plane_num, sizeof(plane_num), data_num, fp);

        USHORT bit_count = (USHORT)depth;
        fwrite(&bit_count, sizeof(bit_count), data_num, fp);

        UINT compression_type = 0; // always 0
        fwrite(&compression_type, sizeof(compression_type), data_num, fp);

        UINT image_data_size = data_size;
        fwrite(&image_data_size, sizeof(image_data_size), data_num, fp);

        UINT pix_per_meter = 0;
        // x pix per meter
        fwrite(&pix_per_meter, sizeof(pix_per_meter), data_num, fp);
        // y pix per meter
        fwrite(&pix_per_meter, sizeof(pix_per_meter), data_num, fp);

        UINT pallet_num = 0;
        fwrite(&pallet_num, sizeof(pallet_num), data_num, fp);

        UINT important_pallet_idx = 0;
        fwrite(&important_pallet_idx, sizeof(important_pallet_idx), data_num, fp);
    }

    // write data part
    fwrite(data, data_size, data_num, fp);

    // close file
    fclose(fp);
}

// private function ---------------------------------
bool Bitmap::checkBytePerPixel(Pixel* arg_pixel){
    return (arg_pixel->getBytePerPix() == byte_per_pix);
}

UINT Bitmap::calcBytePerPixel(UINT depth){
    bool is_divisible = (depth%BYTE_IN_BITS == 0);
    UINT byte_p_pix;
    is_divisible ? byte_p_pix = depth/BYTE_IN_BITS : byte_p_pix = depth/BYTE_IN_BITS + 1;
    return  byte_p_pix;
}

void Bitmap::readColorPalletData(FILE* fp,
                                 int num_pallet_color){
    pallet_data = (ColorPallet*)malloc(sizeof(ColorPallet)*num_pallet_color);
    // read pallet loop
    for(int i = 0; i < num_pallet_color; i++){
        fread(&pallet_data[i].b, sizeof(UCHAR), 1, fp);
        fread(&pallet_data[i].g, sizeof(UCHAR), 1, fp);
        fread(&pallet_data[i].r, sizeof(UCHAR), 1, fp);
        fread(&pallet_data[i].padding, sizeof(UCHAR), 1, fp);
    }
}

Bitmap::~Bitmap() {
    free(pallet_data);
    free(offset_data);
    free(data);
}
