//img_sl.cpp
#include "img.h"  
#include <stdio.h>  
#include <stdlib.h>  

Image* LoadImage(char* path)
{
	Image* bmpImg;
	FILE* pFile;
	unsigned short fileType;
	BMP bmp;
	int channels = 1;
	int width = 0;
	int height = 0;
	int step = 0;
	int offset = 0;
	unsigned char pixVal;
	BMPQuad* quad;
	int i, j, k;

	bmpImg = (Image*)malloc(sizeof(Image));
	pFile = fopen(path, "rb");
	if (!pFile)
	{
		free(bmpImg);
		return NULL;
	}

	fread(&fileType, sizeof(unsigned short), 1, pFile);
	if (fileType == 0x4D42)		//�����BMP
	{
		fread(&bmp, sizeof(BMP), 1, pFile);
		printf("\n");
		printf("bmp�ļ�ͷ��Ϣ��\n");
		printf("�ļ���С��%d \n", bmp.bfSize);
		printf("�����֣�%d \n", bmp.bfReserved1);
		printf("�����֣�%d \n", bmp.bfReserved2);
		printf("λͼ����ƫ���ֽ�����%d \n", bmp.bfOffBits);
		printf("\n");
		printf("bmp�ļ���Ϣͷ\n");
		printf("�ṹ�峤�ȣ�%d \n", bmp.biSize);
		printf("λͼ��ȣ�%d \n", bmp.biWidth);
		printf("λͼ�߶ȣ�%d \n", bmp.biHeight);
		printf("λͼƽ������%d \n", bmp.biPlanes);
		printf("��ɫλ����%d \n", bmp.biBitCount);
		printf("ѹ����ʽ��%d \n", bmp.biCompression);
		printf("ʵ��λͼ����ռ�õ��ֽ�����%d \n", bmp.biSizeImage);
		printf("X����ֱ��ʣ�%d \n", bmp.biXPelsPerMeter);
		printf("Y����ֱ��ʣ�%d \n", bmp.biYPelsPerMeter);
		printf("ʹ�õ���ɫ����%d \n", bmp.biClrUsed);
		printf("��Ҫ��ɫ����%d \n", bmp.biClrImportant);
		printf("\n");

		if (bmp.biBitCount == 8)
		{
			//printf("���ļ��е�ɫ�壬����λͼΪ�����ɫ\n\n");  
			channels = 1;
			width = bmp.biWidth;
			height = bmp.biHeight;
			offset = (channels*width) % 4;
			if (offset != 0)
			{
				offset = 4 - offset;
			}
			//bmpImg->mat = kzCreateMat(height, width, 1, 0);  
			bmpImg->width = width;
			bmpImg->height = height;
			bmpImg->channels = 1;
			bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
			step = channels*width;

			quad = (BMPQuad*)malloc(sizeof(BMPQuad) * 256);
			fread(quad, sizeof(BMPQuad), 256, pFile);
			free(quad);

			for (i = 0; i<height; i++)
			{
				for (j = 0; j<width; j++)
				{
					fread(&pixVal, sizeof(unsigned char), 1, pFile);
					bmpImg->imageData[(height - 1 - i)*step + j] = pixVal;
				}
				if (offset != 0)
				{
					for (j = 0; j<offset; j++)
					{
						fread(&pixVal, sizeof(unsigned char), 1, pFile);
					}
				}
			}
		}
		else if (bmp.biBitCount == 24)
		{
			//printf("��λͼΪλ���ɫ\n\n");  
			channels = 3;
			width = bmp.biWidth;
			height = bmp.biHeight;

			bmpImg->width = width;
			bmpImg->height = height;
			bmpImg->channels = 3;
			bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width * 3 * height);
			step = channels*width;

			offset = (channels*width) % 4;
			if (offset != 0)
			{
				offset = 4 - offset;
			}

			for (i = 0; i<height; i++)
			{
				for (j = 0; j<width; j++)
				{
					for (k = 0; k<3; k++)
					{
						fread(&pixVal, sizeof(unsigned char), 1, pFile);
						bmpImg->imageData[(height - 1 - i)*step + j * 3 + k] = pixVal;
					}
					//kzSetMat(bmpImg->mat, height-1-i, j, kzScalar(pixVal[0], pixVal[1], pixVal[2]));  
				}
				if (offset != 0)
				{
					for (j = 0; j<offset; j++)
					{
						fread(&pixVal, sizeof(unsigned char), 1, pFile);
					}
				}
			}
		}
	}

	return bmpImg;
}

bool SaveImage(char* path, Image* bmpImg)
{
	FILE *pFile;
	unsigned short fileType;
	BMP bmp;
	int step;
	int offset;
	unsigned char pixVal = '\0';
	int i, j;
	BMPQuad* quad;

	pFile = fopen(path, "wb");
	if (!pFile)
	{
		return false;
	}

	fileType = 0x4D42;
	fwrite(&fileType, sizeof(unsigned short), 1, pFile);

	if (bmpImg->channels == 3)//24λ��ͨ������ͼ  
	{
		step = bmpImg->channels*bmpImg->width;
		offset = step % 4;
		if (offset != 0)
		{
			step += 4 - offset;
		}

		bmp.bfSize = bmpImg->height*step + 54;
		bmp.bfReserved1 = 0;
		bmp.bfReserved2 = 0;
		bmp.bfOffBits = 54;
		bmp.biSize = 40;
		bmp.biWidth = bmpImg->width;
		bmp.biHeight = bmpImg->height;
		bmp.biPlanes = 1;
		bmp.biBitCount = 24;
		bmp.biCompression = 0;
		bmp.biSizeImage = bmpImg->height*step;
		bmp.biXPelsPerMeter = 0;
		bmp.biYPelsPerMeter = 0;
		bmp.biClrUsed = 0;
		bmp.biClrImportant = 0;
		fwrite(&bmp, sizeof(BMP), 1, pFile);

		for (i = bmpImg->height - 1; i>-1; i--)
		{
			for (j = 0; j<bmpImg->width; j++)
			{
				pixVal = bmpImg->imageData[i*bmpImg->width * 3 + j * 3];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				pixVal = bmpImg->imageData[i*bmpImg->width * 3 + j * 3 + 1];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				pixVal = bmpImg->imageData[i*bmpImg->width * 3 + j * 3 + 2];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
			}
			if (offset != 0)
			{
				for (j = 0; j<4-offset; j++)
				{
					pixVal = 0;
					fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				}
			}
		}
	}
	else if (bmpImg->channels == 1)//8λ����ͨ�����Ҷ�ͼ  
	{
		step = bmpImg->width;
		offset = step % 4;
		if (offset != 0)
		{
			step += 4 - offset;
		}

		bmp.bfSize = 54 + 256 * 4 + bmpImg->height*step;//54 + 256 * 4 + bmpImg->width;
		bmp.bfReserved1 = 0;
		bmp.bfReserved2 = 0;
		bmp.bfOffBits = 54 + 256 * 4;
		bmp.biSize = 40;
		bmp.biWidth = bmpImg->width;
		bmp.biHeight = bmpImg->height;
		bmp.biPlanes = 1;
		bmp.biBitCount = 8;
		bmp.biCompression = 0;
		bmp.biSizeImage = bmpImg->height*step;
		bmp.biXPelsPerMeter = 0;
		bmp.biYPelsPerMeter = 0;
		bmp.biClrUsed = 256;
		bmp.biClrImportant = 256;
		fwrite(&bmp, sizeof(BMP), 1, pFile);

		quad = (BMPQuad*)malloc(sizeof(BMPQuad) * 256);
		for (i = 0; i<256; i++)
		{
			quad[i].rgbBlue = i;
			quad[i].rgbGreen = i;
			quad[i].rgbRed = i;
			quad[i].rgbReserved = 0;
		}
		fwrite(quad, sizeof(BMPQuad), 256, pFile);
		free(quad);

		for (i = bmpImg->height - 1; i>-1; i--)
		{
			for (j = 0; j<bmpImg->width; j++)
			{
				pixVal = bmpImg->imageData[i*bmpImg->width + j];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
			}
			if (offset != 0)
			{
				for (j = 0; j<4-offset; j++)
				{
					pixVal = 0;
					fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				}
			}
		}
	}
	fclose(pFile);

	return true;
}
