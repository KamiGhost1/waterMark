#include "head.h"


int main(int C, char **V){
    FILE *image1, *image2;
    COLOR **I1, **I2;
    BMPFILEHEADER fh1, fh2;
    BMPINFOHEADER ih1, ih2;
    testParam(C, V);
    image1 = IOpen(V[2]);
    image2 = IOpen(V[4]);
    #ifdef debug
    printf("all okey!\n");
    #endif
    fh1 = readFH(image1);
    fh2 = readFH(image2);
    #ifdef debug
    printf("all okey!\n");
    #endif
    ih1 = readIH(image1);
    ih2 = readIH(image2);
    #ifdef debug
    printf("all okey!\n");
    #endif
    fseek(image1,fh1.bfOffBits,SEEK_SET);
    fseek(image2, fh2.bfOffBits,SEEK_SET);
    I1 = createColor(ih1.bi_Height,ih1.bi_Width);
    I2 = createColor(ih2.bi_Height,ih2.bi_Width);
    #ifdef debug
    printf("all okey!\n");
    #endif
    IRead(image1, I1,ih1.bi_Height,ih1.bi_Width);
    IRead(image2, I2,ih2.bi_Height,ih2.bi_Width);
    fseek(image1,fh1.bfOffBits,SEEK_SET);
    fseek(image2, fh2.bfOffBits,SEEK_SET);
    waterMark(I1, I2, ih1, ih2);
    #ifdef debug
    printf("all okey!\n");
    #endif
    IWrite(image1, I1, ih1.bi_Height, ih1.bi_Width);
    #ifdef debug
    printf("Over!\n");
    #endif
    printf("image changed!\n");
    free(I1);
    free(I2);
    fclose(image1);
    fclose(image2);
    return 0;
}