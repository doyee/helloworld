
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

typedef unsigned char byte;

void drawRect(byte* pBufferY, int width, int height, int rectWidth, int rectHeight)
{
	byte* pY = pBufferY;
	long offset = (height-rectHeight)*width/2+(width-rectWidth)/2;
	pY+=offset;
	memset(pY, 1, rectWidth);
	pY+=rectWidth;
	for(int i=0; i<rectHeight-1; i++) {
		pY+=(width-rectWidth);
		memset(pY, 1, sizeof(byte));
		pY+=rectWidth;
		memset(pY, 1, sizeof(byte));
	}
	pY+=(width-rectWidth);
	memset(pY, 1, rectWidth);
}

void fillBlack(byte* pBufferY, byte* pBufferUV, int width, int height, int blackWidth, int blackHeight) {
	byte* pY = pBufferY;
	byte* pUV = pBufferUV;
	for(int i=0; i<blackHeight; i++) {
		memset(pY, 10, blackWidth);
		pY += width;
	}
	// for(int i=0; i<blackHeight/2; i++) {
	// 	memset(pUV, 3, blackWidth);
	// 	pUV += width;
	// }
}


int main()
{
	FILE* fp = NULL;
	FILE* fp_save = NULL;
	byte* pBufferY = NULL;
	byte* pBufferUV = NULL;
	int width = 4160;
	int height = 3120;
	fp = fopen("/Users/wujian/Desktop/content2019/7_multi-thread/4160x3120.nv21", "rb");
	if(NULL == fp)
	{
		printf("open origin file failed!\n");
		return 1;
	}
	pBufferY = (byte*)malloc(sizeof(byte) * width * height);
	pBufferUV = (byte*)malloc(sizeof(byte) * width * height / 2);

	if(NULL == pBufferY || NULL == pBufferUV) 
	{
		printf("buffer alloc failed!\n");
		return 2;
	}
	memset(pBufferY, 0, sizeof(byte) * width * height);
	memset(pBufferY, 0, sizeof(byte) * width * height / 2);
	fread(pBufferY, width*height, 1, fp);
	fread(pBufferUV, width*height/2, 1, fp);
	fclose(fp);

	drawRect(pBufferY, 4160, 3120, 1280, 960);
	fillBlack(pBufferY, pBufferUV, 4160, 3120, 1440, 1080);

	fp_save = fopen("/Users/wujian/Desktop/content2019/7_multi-thread/new_4160x3120.nv21", "wb");
	if(NULL == fp_save) {
		printf("save file open failed!\n");
		return 1;
	}

	fwrite(pBufferY, width*height, 1, fp_save);
	fwrite(pBufferUV, width*height/2, 1, fp_save);
	fclose(fp_save);

    return 0;
}










