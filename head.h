#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bmp 19778


#ifndef _bmp_str_
#define _bmp_str_

#pragma pack(push,1)
typedef struct {
   unsigned short bfType; 
   unsigned int   bfSize; 
   unsigned short    bfReserved1; 
   unsigned short    bfReserved2; 
   unsigned int   bfOffBits; 
}BMPFILEHEADER;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct BMP {
   unsigned int  bi_Size; 
   unsigned int   bi_Width; 
   unsigned int   bi_Height; 
   unsigned short   bi_Planes; 
   unsigned short   bi_BitCount; 
   unsigned int  bi_Compression; 
   unsigned int  bi_SizeImage; 
   int   bi_X; 
   int   bi_Y; 
   unsigned int  bi_ClrUsed; 
   unsigned int  bi_ClrImportant; 
}BMPINFOHEADER;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct COLOR_pix {
    char R,G,B;
}COLOR;
#pragma pack(pop)
#endif

int testParam(int C, char **V);
void IRead(FILE *input, COLOR **image, int height,int width);
void IWrite(FILE *output, COLOR **image,int height,int width);
void waterMark(COLOR **image1 , COLOR **image2, BMPINFOHEADER ih1, BMPINFOHEADER ih2);
COLOR **createColor(int height,int width);
FILE *IOpen(char *name);
BMPFILEHEADER readFH(FILE *input);
BMPINFOHEADER readIH(FILE *input);
