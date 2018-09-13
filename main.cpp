#include <iostream>
#include "Bitmap.h"

int main() {
    BYTE pix_data[] = {0, 8, 4};
    UINT pix_data_size = sizeof(pix_data);
    Pixel pixel(sizeof(pix_data));
    pixel.setData(pix_data);
    Bitmap bitmap_image(4, 4, 24);
    bitmap_image.setPixel(2, 1, &pixel);

    Pixel receive(sizeof(pix_data));
    bitmap_image.getPixel(2, 1, &receive);
    BYTE* rec = receive.getData();
    printf("%d %d %d", rec[0], rec[1], rec[2]);

    Bitmap bitmap_smaple("lena_gray.bmp");
    return 0;
}