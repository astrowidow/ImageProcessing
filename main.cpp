#include <iostream>
#include "Bitmap.h"

int main() {
    Bitmap test(4, 4, 3);
    int* a = (int*)test.getPixel(0, 2);
    BYTE b[3];
    char i = sizeof(b[2]);
    return 0;
}