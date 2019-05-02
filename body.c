#include "head.h"

void IRead(FILE *input, COLOR **image, int height,int width){
    int i,j;
    for (i=0;i<height;i++)
        for (j=0;j<width;j++)
            fread(&image[i][j],sizeof(COLOR),1,input);
}


void IWrite(FILE *output, COLOR **image,int height,int width){
    int i,j;
    for (i=0;i<height;i++)
        for (j=0;j<width;j++)
            fwrite(&image[i][j],sizeof(COLOR),1,output);
}


void waterMark(COLOR **image1 , COLOR **image2, BMPINFOHEADER ih1, BMPINFOHEADER ih2){
    unsigned int Height, Width; 
    int i,j;
    if(ih1.bi_SizeImage == ih2.bi_SizeImage){
        if(ih1.bi_Height==ih2.bi_Height){
            Height = ih1.bi_Height;
            Width = ih1.bi_Width; 
        }
        else{
            printf("problem! rotate image on 90 grad!\n");
            exit(6);
        }
    }
    else{
        if(ih1.bi_Height>ih2.bi_Height)
                Height = ih2.bi_Height;
            else
                Height = ih1.bi_Height;
            if (ih1.bi_Width > ih2.bi_Width)
                Width = ih2.bi_Width;
            else 
                Width = ih1.bi_Width;
    }
    for (i=0;i<Height;i++)
        for (j=0;j<Width;j++){
            image1[i][j].B=((image1[i][j].B ^ image2[i][j].B));
            image1[i][j].R=((image1[i][j].R ^ image2[i][j].R));
            image1[i][j].G=((image1[i][j].G ^ image2[i][j].G));
        }
}


COLOR **createColor(int height,int width){
    COLOR **image;
    int i;
    image = (COLOR**)malloc(sizeof(COLOR*)*height);
    for (i=0;i<height;i++)
        image[i]=(COLOR*)malloc(sizeof(COLOR)*width);
    return image;
}

int testParam(int C, char **V){
    if (C==5){
        if (!strcmp(V[1],"i1") && !strcmp(V[3],"i2")){
            return 0;            
        }
    }
    if (C == 1){
        printf("WaterMark by Ghost\nto more info use -h\nEnjoy!\n");
        exit(0);
    }
    if(C==2){
        if(!strcmp(V[1], "-h")){
            printf("Use command waterMark.exe i1 iamge1.bmp i2 image2.bmp\n");
            printf("Result write in image1.bmp\n");
            printf("Enjoy!\n");
            exit(0);
        }
    }
    printf("incorrect command! example: prog.exe i1 image1.bmp i2 image2.bmp\n");
    exit(1);
}

FILE *IOpen(char *name){
    FILE *f;
    f = fopen(name, "rb+");
    if(!f){
        printf("file '%s' not found!\n",name);
        return NULL;
    }  
    return f;
}

BMPFILEHEADER readFH(FILE *input){
    BMPFILEHEADER fh;
    fread(&fh, sizeof(BMPFILEHEADER),1,input);
    if (fh.bfType != bmp){
        printf("file is not BMP\n");
        exit(3);
    }
    return fh;
}
BMPINFOHEADER readIH(FILE *input){
    BMPINFOHEADER ih;
    fread(&ih, sizeof(BMPINFOHEADER),1,input);
    return ih;
}