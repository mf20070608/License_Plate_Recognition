#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <math.h>
#include "img.h"  

void Hough(Image* srcImg,int yuzhi)
{
	int height = srcImg->height;
	int width = srcImg->width;

	unsigned char* dstData;
	dstData = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
	//memcpy(dstData, srcImg->imageData, sizeof(unsigned char)*width*height);

#define pi 3.1416
#define mp sqrt((float)height*height+width*width)
#define ma 180
	int i, j, k, p;
	int npp[ma][1000];
	for (i = 1; i < height; i++) //heightԭͼ�߶�

		for (j = 1; j < width; j++) //width ԭͼ���

		{

			if (srcImg->imageData[i*width + j] == 255) //�Ա�Ե��������ݣ�����lpDIBBits�У�����hough�仯

			{

				for (k = 1; k < ma; k++) //ma=180

				{

					p = (int)(i*cos(pi*k / 180) + j*sin(pi*k / 180));//p hough�任�о������

					p = (int)(p / 2 + mp / 2); //��pֵ�Ż���ֹΪ��

					npp[k][p] = npp[k][p]++; //npp�Ա任���ж�Ӧ�ظ����ֵĵ��ۼ�

				}

			}

		}

	int kmax = 0; //�ֱ�ߵĽǶ�

	int pmax = 0; //�ֱ�ߵľ���

	int n = 0; //��һ����ΪѰ���ֱ��

	for (i = 1; i < ma; i++) //ma=180

		for (j = 1; j<mp; j++) //mpΪԭͼ�Խ��߾���

		{

			if (npp[i][j]>yuzhi) //�ҳ��ֱ�� yuzhiΪ�м�������ڱȽ�

			{

				yuzhi = npp[i][j];

				kmax = i; //��¼�ֱ�ߵĽǶ�

				pmax = j; //��¼�ֱ�ߵľ���

			}

		}

	memset(dstData, (unsigned char)0, sizeof(unsigned char)*width*height);//ԭͼ���������kmax��pmax��ֵ�ļ��ϼ������ֱ��

	for (i = 1; i < height; i++) 

		for (j = 1; j < width; j++)

		{

			if (srcImg->imageData[i*width + j] == 255)

			{

				p = (int)(i*cos(pi*kmax / 180) + j*sin(pi*kmax / 180));//pi=3.1415926

				p = (int)(p / 2 + mp / 2); //mpΪԭͼ�Խ��߾���

				if (p == pmax)

					dstData[ i*width + j] = 255; //�洢ͼ������ ����temp������

			}

		}
	memcpy(srcImg->imageData, dstData, width * height);
	bool flag = SaveImage("result_hough.bmp", srcImg);
	if (flag)
	{
		printf("save jumpPoint ok... \n");
	}
	// �ͷ��ڴ�
	free(dstData);
}