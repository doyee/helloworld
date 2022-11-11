#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char byte;

//crop image
int cropImage(char* filePath, int originWidth, int originHeight, int cropedWidth, int cropedHeight) {
    byte* pTemp_buffer = NULL;
    FILE* fp = NULL;
    FILE* fp_crop = NULL;
    //alloc memory
    pTemp_buffer = (byte*)malloc(cropedWidth);
    fp = fopen(filePath, "rb");
    if (NULL == fp) {
        printf("origin file open failed!\n");
        return 1;
    }
    //save image according to crop info
    fp_crop = fopen("2560x1920.nv21", "wb");
    if (NULL == fp_crop) {
        printf("crop file open failed!\n");
        return 1;
    }

    //save Y plane
    fseek(fp, 0, SEEK_SET);
    fseek(fp, originWidth * (originHeight - cropedHeight) / 2 , SEEK_SET);
    for (int i = 0; i < cropedHeight; i++) {
        fseek(fp, (originWidth - cropedWidth) / 2, SEEK_CUR);
        if (pTemp_buffer != NULL) {
            //printf("write Y row %d\n", i);
            memset(pTemp_buffer, 0, cropedWidth);
            fread(pTemp_buffer, cropedWidth, 1, fp);
            fwrite(pTemp_buffer, cropedWidth, 1, fp_crop);
        }
        else{
            printf("temp buffer alloc fail!");
            return 2;
        }
        fseek(fp, (originWidth - cropedWidth) / 2, SEEK_CUR);
    }
    
    //save UV plane
    fseek(fp, originWidth * (originHeight - cropedHeight) / 2, SEEK_CUR);//jump the Y buffer
    fseek(fp, originWidth * (originHeight - cropedHeight) / 4, SEEK_CUR);//jump the UV buffer
    for (int i = 0; i < cropedHeight / 2; i++) {
        fseek(fp, (originWidth - cropedWidth) / 2, SEEK_CUR);
        if (pTemp_buffer != NULL) {
            //printf("write UV row %d\n", i);
            memset(pTemp_buffer, 0, cropedWidth);
            fread(pTemp_buffer, cropedWidth, 1, fp);
            fwrite(pTemp_buffer, cropedWidth, 1, fp_crop);
        }
        else {
            printf("temp buffer alloc fail!");
            return 2;
        }
        fseek(fp, (originWidth - cropedWidth) / 2, SEEK_CUR);
    }
    
    //free memory
    fclose(fp);
    fclose(fp_crop);
    free(pTemp_buffer);
    return 0;
}

//scale image
int scaleImage(char* filePath, int originWidth, int originHeight, int scaledWidth, int scaledHeight) {
    FILE* fp = NULL;
    FILE* fp_scale = NULL;
    byte* pImage = NULL;
    int ratio = originWidth / scaledWidth;
    pImage = (byte*)malloc(originWidth * originHeight * 3 / 2);
    fp = fopen(filePath, "rb");
    if (NULL == fp) {
        printf("origin file open failed!\n");
        return 1;
    }
    fp_scale = fopen("640x480.nv21", "wb");
    if (NULL == fp_scale) {
        printf("scaled file open failed!\n");
        return 1;
    }
    if (pImage != NULL) {
        memset(pImage, 0, originWidth * originHeight * 3 / 2);
        fread(pImage, originWidth * originHeight * 3 / 2, 1, fp);
        fseek(fp_scale, 0, SEEK_SET);
        byte* pBufferY = pImage;
        byte* pBufferUV = pBufferY + (originWidth * originHeight);
        //deal with Y buffer
        for (int i=0; i < scaledHeight; i++) {
            printf("write Y row %d\n", i);
            for (int j = 0; j < scaledWidth; j++) {
                fwrite(pBufferY, sizeof(byte), 1, fp_scale);
                pBufferY +=ratio;
            }
            pBufferY = pBufferY + (3 * originWidth);
        }
        //deal with UV buffer
        for (int i = 0; i < scaledHeight / 2; i++) {
            printf("write UV row %d\n", i);
            for (int j = 0; j < scaledWidth / 2; j++) {
                fwrite(pBufferUV, sizeof(byte), 2, fp_scale);
                pBufferUV +=(ratio*2);
            }
            pBufferUV = pBufferUV + (3 * originWidth);
        }
    }
    else {
        printf("alloc buffer failed!\n");
        return 2;
    }

    //free memory
    free(pImage);
    fclose(fp);
    fclose(fp_scale);
    return 0;
}
int main() {
    int ret = 0;
    int originWidth = 4160;
    int originHeight = 3120;
    int cropedWidth = 2560;
    int cropedHeight = 1920;
    int scaledWidth = 640;
    int scaledHeight = 480;
    char originFilePath[] = "4160x3120.nv21";
    char cropedFilePath[] = "2560x1920.nv21";
    //crop image
    ret = cropImage(originFilePath, originWidth, originHeight, cropedWidth, cropedHeight);
    if (ret != 0) {
        printf("crop yuv failed!ret = %d\n", ret);
        return 1;
    }
    //down scale image
    ret = scaleImage(cropedFilePath, cropedWidth, cropedHeight, scaledWidth, scaledHeight);
    if (ret != 0) {
        printf("scale yuv failed! ret = %d\n", ret);
        return 1;
    }
    return ret;
}
