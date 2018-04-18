#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <math.h>
#include "img.h"  

void grayStretch(Image* src, int nMin, int nMax)
{
	int height = src->height;
	int width = src->width;
	unsigned char* dstData;
	dstData = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
	int low_value = nMin;    //��������ص���Сֵ   
	int high_value = nMax;   //��������ص����ֵ  

	float rate = 0;          //ͼ���������  

	float stretch_p[256], stretch_p1[256], stretch_num[256];
	//�����������,��ʼ���������Ԫ��Ϊ0  
	memset(stretch_p, 0, sizeof(stretch_p));
	memset(stretch_p1, 0, sizeof(stretch_p1));
	memset(stretch_num, 0, sizeof(stretch_num));
	//ͳ��ͼ������Ҷȼ����ֵĴ���  
	unsigned char* srcData = (unsigned char*)src->imageData;
	int nHeight = src->height;
	int nWidth = src->width;
	int i, j;
	unsigned char nVal = 0;
	for (i = 0; i<nHeight; i++)
	{
		for (j = 0; j<nWidth; j++)
		{
			nVal = srcData[i*nWidth + j];
			stretch_num[nVal]++;
		}
	}
	//ͳ�Ƹ����Ҷȼ����ֵĸ���  
	for (i = 0; i<256; i++)
	{
		stretch_p[i] = stretch_num[i] / (nHeight*nWidth);
	}
	//ͳ�Ƹ����Ҷȼ��ĸ��ʺ�  
	for (i = 0; i<256; i++)
	{
		for (j = 0; j <= i; j++)
		{
			stretch_p1[i] += stretch_p[j];
		}
	}
	//����������ֵ���ֵ  
	for (i = 0; i<256; i++)
	{
		if (stretch_p1[i]<0.1)     //low_valueȡֵ�ӽ���10%�������صĻҶ�ֵ  
		{
			low_value = i;
		}
		if (stretch_p1[i]>0.9)     //high_valueȡֵ�ӽ���90%�������صĻҶ�ֵ  
		{
			high_value = i;
			break;
		}
	}
	rate = (float)255 / (high_value - low_value + 1);
	//���лҶ�����  
	for (i = 0; i<nHeight; i++)
	{
		for (j = 0; j<nWidth; j++)
		{
			nVal = srcData[i*nWidth + j];
			if (nVal<low_value)
			{
				dstData[i*nWidth + j] = 0;
			}
			else if (nVal>high_value)
			{
				dstData[i*nWidth + j] = 255;
			}
			else
			{
				dstData[i*nWidth + j] = (unsigned char)((nVal - low_value)*rate + 0.5);
				if (dstData[i*nWidth + j]>255)
				{
					dstData[i*nWidth + j] = 255;
				}
			}
		}
	}
	memcpy(src->imageData, dstData, width * height);
	bool flag = SaveImage("result_grayStretch.bmp", src);
	if (flag)
	{
		printf("save grayStretch ok... \n");
	}
	// �ͷ��ڴ�
	free(dstData);
}