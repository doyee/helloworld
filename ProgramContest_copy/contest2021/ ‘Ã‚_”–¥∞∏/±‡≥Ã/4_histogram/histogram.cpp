#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*8 bit Y plane followed by 8 bit 2x2 subsampled UV planes*/
#define     ASVL_PAF_NV12               0x801
/*8 bit Y plane followed by 8 bit 2x2 subsampled VU planes*/
#define     ASVL_PAF_NV21               0x802
/*Define the image format space*/
typedef struct __tag_ASVL_OFFSCREEN
{
    unsigned int u32PixelArrayFormat;
    int i32Width;
    int i32Height;
    unsigned char* ppu8Plane[4];
    int pi32Pitch[4];
}ASVLOFFSCREEN, *LPASVLOFFSCREEN;


bool readImageData(char *pFileName, ASVLOFFSCREEN *pImage)
{
    if(pFileName == NULL || pImage == NULL) {
        return false;
    }
    int  iFrameLength = 0;
    if(pImage->u32PixelArrayFormat == ASVL_PAF_NV12 || pImage->u32PixelArrayFormat == ASVL_PAF_NV21) {
        iFrameLength = pImage->i32Height * pImage->pi32Pitch[0]*3/2;
    } else {
        iFrameLength = pImage->i32Height * pImage->pi32Pitch[0]*3;
    }
    if(iFrameLength == 0) {
        return false;
    }
    if(pImage->ppu8Plane[0] != NULL) {
        free(pImage->ppu8Plane[0]);
    }
    pImage->ppu8Plane[0]  = (unsigned char*) malloc(iFrameLength);
    pImage->ppu8Plane[1]  = pImage->ppu8Plane[0] + pImage->i32Height * pImage->pi32Pitch[0];

    FILE *pFile = fopen(pFileName, "rb");
    if(pFile){
        fread(pImage->ppu8Plane[0], 1, iFrameLength, pFile);
        fclose(pFile);
    } else {
        free(pImage->ppu8Plane[0]);
        pImage->ppu8Plane[0] = pImage->ppu8Plane[1] = NULL;
        return false;
    }
    return true;
}

bool releaseImageData(ASVLOFFSCREEN *pImage)
{
    if(pImage == NULL || pImage->ppu8Plane[0] == NULL) {
        return false;
    }
    free(pImage->ppu8Plane[0]);
    pImage->ppu8Plane[0] = NULL;

    return true;
}

bool writeHistogram(char *pFileName, float* pData, int length)
{
    if(pFileName == NULL || pData == NULL || length <= 0) {
        return false;
    }
    char buff[256] = {0};
    FILE *pFile = fopen(pFileName, "wb+");
    if(pFile) {
        for(int i=0; i<length;i++){
            memset(buff, 0, sizeof(buff));
            sprintf(buff, "index:%03d, Histogram: %f%%\n", i, *(pData + i)*100);
            fwrite(buff, strlen(buff) * sizeof(char), sizeof(char), pFile);
        }
        fclose(pFile);
    }
    return true;
}

bool printHistogram(float* pData, int length)
{
    if(pData == NULL || length <= 0) {
        return false;
    }
    for(int i=0; i<length;i++){
        printf("Value: %03d, Histogram: %f%%\n", i, *(pData+i)*100);
    }

    return true;
}

bool calculateHistogram1(ASVLOFFSCREEN *pImage, float* pfHistogram, int* pHistogramLength)
{
    if(pImage == NULL || pfHistogram == NULL || pHistogramLength == NULL || *pHistogramLength <= 0) {
        return false;
    }
    int i32Histogram[1024] = { 0 };
    int i32HistogramLength = *pHistogramLength;
    int iGrayFrameLength = 0;
    iGrayFrameLength = pImage->i32Width * pImage->i32Height;
    unsigned char* pGrayData = NULL;
    pGrayData = pImage->ppu8Plane[0];
    unsigned char pPixelData = 0;

    for(int i = 0; i < pImage->i32Height; i++)
    {
        for(int j = 0; j < pImage->i32Width; j++)
        {
            pPixelData = *(pGrayData + i * pImage->pi32Pitch[0] + j);
            i32Histogram[pPixelData] = i32Histogram[pPixelData] + 1;
        }
    }

    *pHistogramLength = 256;
    for(int i = 0; i < 256; i++)
    {
        *(pfHistogram + i) = (float)((float)i32Histogram[i]/(float)iGrayFrameLength);
    }

    return true;
}

bool calculateHistogram2(ASVLOFFSCREEN *pImage, float* pfHistogram, int* pHistogramLength)
{
    if(pImage == NULL || pfHistogram == NULL || pHistogramLength == NULL || *pHistogramLength <= 0) {
        return false;
    }

    int i32Histogram[1024] = { 0 };
    int i32HistogramLength = *pHistogramLength;
    int iGrayFrameLength = 0;
    iGrayFrameLength = pImage->i32Width * pImage->i32Height;
    unsigned char* pGrayData = NULL;
    pGrayData = pImage->ppu8Plane[0];
    unsigned char pPixelData = 0;

    unsigned int u32Bins[16] = { 0 };
    for(int i = 1; i <= 16; i++)
    {
        u32Bins[i-1] = 16*i;
    }


    for(int i = 0; i < pImage->i32Height; i++)
    {
        for(int j = 0; j < pImage->i32Width; j++)
        {
            pPixelData = *(pGrayData + i * pImage->pi32Pitch[0] + j);
            for(int k = 0; k < 16; k++) {
                if(pPixelData < u32Bins[k]) {
                    i32Histogram[k] = i32Histogram[k] + 1;
                    break;
                }
            }
        }
    }

    *pHistogramLength = 16;
    for(int i = 0; i < 16; i++)
    {
        *(pfHistogram + i) = (float)((float)i32Histogram[i]/(float)iGrayFrameLength);
    }

    return true;
}


#define _IMAGE_WIDTH  1440
#define _IMAGE_HEIGHT 1080
#define _IMAGE_PITCH  1480
#define _IMAGE_FORMAT ASVL_PAF_NV12

#define _IMAGE_FILENAME "HistogramInputImage_1440x1080_pitch1480.nv12"
#define _HIST_FILENAME1 "HistogramResult1.txt"
#define _HIST_FILENAME2 "HistogramResult2.txt"

int main(int argc, char **argv) {

    bool bResult = false;
    ASVLOFFSCREEN nImage = { 0 };

    nImage.u32PixelArrayFormat = _IMAGE_FORMAT;
    nImage.i32Width  = _IMAGE_WIDTH;
    nImage.i32Height = _IMAGE_HEIGHT;
    nImage.pi32Pitch[0] = _IMAGE_PITCH;
    nImage.pi32Pitch[1] = _IMAGE_PITCH;
    nImage.pi32Pitch[2] = _IMAGE_PITCH;
    bResult = readImageData(_IMAGE_FILENAME, &nImage);
    if(!bResult) {
        printf("read image failed.\n");
        return -1;
    }

    float fHistogram[1024] = { 0.0f };
    int i32HistogramLength = 1024;

    calculateHistogram1(&nImage, fHistogram, &i32HistogramLength);
    writeHistogram(_HIST_FILENAME1, fHistogram, i32HistogramLength);
    printHistogram(fHistogram, i32HistogramLength);

    calculateHistogram2(&nImage, fHistogram, &i32HistogramLength);
    writeHistogram(_HIST_FILENAME2, fHistogram, i32HistogramLength);
    printHistogram(fHistogram, i32HistogramLength);

    releaseImageData(&nImage);

    return 0;
}
