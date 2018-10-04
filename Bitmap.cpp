//
// Created by 俵京佑 on 2018/09/11.
//
#include <cstdlib>
#include <cstring>
#include "Bitmap.h"

Bitmap::Bitmap(UINT w, UINT h, UINT d){
    width = w;
    height = h;
    depth = d;
    byte_per_pix = calcBytePerPixel(depth);
    data_size = width * height * byte_per_pix;
    // malloc
    data = new BYTE[data_size];
    pallet_data = new ColorPallet;
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
    pallet_byte = file_header.offset_byte - FILE_HEADER_SIZE - core_header.size;
    UINT pallet_color_num;
    if(core_header.size == INFO_HEADER_SIZE){
        if(pallet_byte%INFO_PALLET_SET_SIZE) printf("pallet num is unexpected !!");
        pallet_color_num = pallet_byte/INFO_PALLET_SET_SIZE;
        pallet_data = new ColorPallet[pallet_color_num];
        for(int i = 0; i < pallet_color_num; i++){
            fread(&pallet_data[i].b, sizeof(UCHAR), 1, fp);
            fread(&pallet_data[i].g, sizeof(UCHAR), 1, fp);
            fread(&pallet_data[i].r, sizeof(UCHAR), 1, fp);
            fread(&pallet_data[i].padding, sizeof(UCHAR), 1, fp);
        }
    }
    else if(core_header.size == CORE_HEADER_SIZE) {
        if(pallet_byte%CORE_PALLET_SET_SIZE) printf("pallet num is unexpected !!");
        pallet_color_num = pallet_byte/CORE_PALLET_SET_SIZE;
        pallet_data = new ColorPallet[pallet_color_num];
        for(int i = 0; i < pallet_color_num; i++){
            fread(&pallet_data[i].b, sizeof(UCHAR), 1, fp);
            fread(&pallet_data[i].g, sizeof(UCHAR), 1, fp);
            fread(&pallet_data[i].r, sizeof(UCHAR), 1, fp);
        }
    }

    // read image data
    // ... get byte per pixel
    UINT byte_p_pix = calcBytePerPixel(core_header.bit_count);
    // ... get image data size
    UINT image_data_size = core_header.height*core_header.width*byte_p_pix;
    // ... read image data
    data = new BYTE[image_data_size];
    fread(data, image_data_size, data_num, fp);

    // set important parameter
    width = core_header.width;
    height = core_header.height;
    depth = core_header.bit_count;
    byte_per_pix = byte_p_pix;
    data_size = image_data_size;
    pallet_num = pallet_color_num;

    // close file
    fclose(fp);
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
            auto width = (USHORT)core_header.width;
            fwrite(&width, sizeof(width), data_num, fp);
            auto height = (USHORT)core_header.height;
            fwrite(&height, sizeof(height), data_num, fp);

            fwrite(&core_header.planes, sizeof(core_header.planes), data_num, fp);
            fwrite(&core_header.bit_count, sizeof(core_header.bit_count), data_num, fp);

            for(UINT i = 0; i < pallet_num; i++){
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

            for(UINT i = 0; i < pallet_num; i++){
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

        auto bit_count = (USHORT)depth;
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

        // ... write color pallet if needed
        if(depth == 8){
            UCHAR padding_data = 0;
            UCHAR pallet_element = 0;
            //for(UCHAR i = 0; i < 256; i++){
            for(UINT i = 0; i < 256; i++){
                fwrite(&pallet_element, sizeof(BYTE), data_num, fp);
                fwrite(&pallet_element, sizeof(BYTE), data_num, fp);
                fwrite(&pallet_element, sizeof(BYTE), data_num, fp);
                fwrite(&padding_data, sizeof(BYTE), data_num, fp);
                pallet_element++;
            }
        }
    }

    // write data part
    fwrite(data, data_size, data_num, fp);

    // close file
    fclose(fp);
}

Bitmap::~Bitmap() {
    //free(pallet_data);
    delete[] pallet_data;
    //free(data);
    delete[] data;
}
