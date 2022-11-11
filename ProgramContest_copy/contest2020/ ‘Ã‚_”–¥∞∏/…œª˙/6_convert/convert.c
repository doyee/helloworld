#include<stdio.h>
#include<stdlib.h>
# include <string.h>

#define FULL_WIDTH 4160
#define FULL_HEIGHT 3120
#define CORP_WIDTH 2560
#define CORP_HEIGHT 1920

#define SCAL_WIDTH 640
#define SCAL_HEIGHT 480

char OrigImg[FULL_WIDTH * FULL_HEIGHT * 3/2] = {0};
char CropImg[CORP_WIDTH * CORP_HEIGHT *3/2] = {0};
char ScalImg[SCAL_WIDTH * SCAL_HEIGHT *3 /2] = {0};


char getY(char *img,int x,int y)
{
	return img[x+CORP_WIDTH*y];
}
char getU(char *img,int x,int y)
{
	return img[CORP_WIDTH * CORP_HEIGHT + 2*x + CORP_WIDTH *y];
}
char getV(char *img,int x,int y)
{
	return img[CORP_WIDTH * CORP_HEIGHT + 2*x + CORP_WIDTH *y + 1];
}

int main() {
	
	FILE *fd = fopen("4160x3120.nv21","rb");
	if(fd == NULL)
	{
		printf("can not read image\n");
		return -1;
	}
	//read image
	int readlen = fread(OrigImg,1,FULL_WIDTH * FULL_HEIGHT * 3/2,fd);
	if(readlen != FULL_WIDTH * FULL_HEIGHT * 3/2)
	{
		printf("read image error\n");
		fclose(fd);
		return -1;
	}
	fclose(fd);
	//corp image
	//Y
	for(int n = 0; n< CORP_HEIGHT; ++n) //y
	{
		//copy Y
		char *cropstart = CropImg + CORP_WIDTH*n;
		char *fullstart = OrigImg + FULL_WIDTH*((FULL_HEIGHT-CORP_HEIGHT)/2+n)+(FULL_WIDTH-CORP_WIDTH)/2;
		memcpy(cropstart,fullstart,CORP_WIDTH);
		
	}
	
	//copy UV
	for(int i = 0;i<CORP_HEIGHT/2;++i)
	{
		//copy UV
		char *cropstart = CropImg + CORP_WIDTH * CORP_HEIGHT + CORP_WIDTH * i;
		char *fullstart = OrigImg + FULL_WIDTH * FULL_HEIGHT + FULL_WIDTH*((FULL_HEIGHT-CORP_HEIGHT)/4+i)+(FULL_WIDTH-CORP_WIDTH)/2;
		memcpy(cropstart,fullstart,CORP_WIDTH);
	}
	FILE *fd1 = fopen("2560x1920.nv21","wb");
	fwrite(CropImg,CORP_WIDTH * CORP_HEIGHT *3/2,1,fd1);
	fclose(fd);
	//change size
	for(int j = 0;j< SCAL_HEIGHT ;++j) //y
	{
		
		for(int i = 0;i<SCAL_WIDTH;++i) //x
		{
			//copy char
			//Y
			ScalImg[i+ SCAL_WIDTH*j] = getY(CropImg,4*i,4*j);
		}
	}
	for(int i = 0;i<SCAL_HEIGHT/2;++i) //y
	{
		for(int j = 0;j<SCAL_WIDTH/2;++j) //x
		{
			//U
			ScalImg[SCAL_WIDTH*SCAL_HEIGHT + 2*j + SCAL_WIDTH*i] = getU(CropImg,4*j,4*i);
			//V
			ScalImg[SCAL_WIDTH*SCAL_HEIGHT + 2*j + 1 + SCAL_WIDTH*i] = getV(CropImg,4*j,4*i);
		}
	}
	
	FILE *fdc = fopen("640x480.nv21","wb");
	if(fdc == NULL)
	{
		printf("can not write image\n");
		return -1;
	}
	fwrite(ScalImg,SCAL_WIDTH*SCAL_HEIGHT*3/2,1,fdc);
	fclose(fd);
	
	
	

    return 0;
}
