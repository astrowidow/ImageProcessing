#include <iostream>
#include "Bitmap.h"

int main() {
    BYTE pix_data[] = {0, 8, 4};
    UINT pix_data_size = sizeof(pix_data);
    Pixel pixel(sizeof(pix_data));
    pixel.setData(pix_data);
    Bitmap test(4, 4, 24);
    test.setPixel(0, 0, pixel);
    Pixel receive = test.getPixel(0, 0);
    BYTE* rec = receive.getData();
    printf("%d %d %d", rec[0], rec[1], rec[2]);
    return 0;
}