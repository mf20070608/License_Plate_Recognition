#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <math.h>
#include "img.h"  

int otsu(Image *src)			//otsu�㷨�����ֵ��ֵ
{
	int height = src->height;
	int width = src->width;
	int histCount[256] = { 0 };
	float histogram[256] = { 0 };

	for (int h = 0; h<height; h++)
	{
		for (int w = 0; w<width; w++)
		{
			histCount[src->imageData[w+h*width]]++;//����ֱ��ͼ  
		}
	}

	int totalpixel = width *height;

	for (int i = 0; i<256; i++)
		histogram[i] = (float)histCount[i] / (float)totalpixel;//��һ��ֱ��ͼ  

	float maxavgvalue = 0;

	for (int i = 0; i<256; i++)
		maxavgvalue = i*histogram[i];//�ܵĻҶȾ�ֵ����ʵ������ɽ�����Ϊ0  

	float PA = 0;//A����ָ���  
	float PB = 0;//B����ָ���  
	float Agrayvalue = 0;//A��ҶȾ�ֵ  
	float Bgrayvalue = 0;//B��ҶȾ�ֵ  
	float maxvariance = 0;
	float variance;
	int threshold;

	for (int i = 0; i<256; i++)
	{
		PA += histogram[i];
		PB = 1 - PA;
		Agrayvalue += i*histogram[i];//A��ҶȾ�ֵ  
		Bgrayvalue += maxavgvalue - Agrayvalue;//B��ҶȾ�ֵ  
		//Agrayvalue = Agrayvalue/PA;  
		//Bgrayvalue = Bgrayvalue/PB;  
		variance = PA*(Agrayvalue - maxavgvalue)*(Agrayvalue - maxavgvalue) + PB*(Bgrayvalue - maxavgvalue)*(Bgrayvalue - maxavgvalue);//������䷽��  


		if (variance>maxvariance)
		{
			maxvariance = variance;
			threshold = i;//��������䷽��ʱ������ֵ����Ϊ�����ֵ  
		}
	}
	
	return threshold;//���������ֵ
}

void quickAdaptiveThreshold(Image* bmpImg)//unsigned char* grayImage, unsigned char* binImage, int width, int height)
{
	int height = bmpImg->height;
	int width = bmpImg->width;
	unsigned char* binImage;
	binImage = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
	int t = 15;
	int s = width >> 3;
	const int T = 9; //T�Ǳ��⸡��������  
	const int power2S = 1 << T; //ͬʱ�˳�2��T�η�,���⸡������  

	int factor = power2S * (100 - t) / (100 * s);
	int gn = 127 * s;
	int q = power2S - power2S / s; //�ȱ����б���  
	int pn, hn;
	unsigned char *scanline = NULL;
	int *prev_gn = NULL;

	prev_gn = new int[width];
	for (int i = 0; i < width; i++)
	{
		prev_gn[i] = gn;
	}

	//���ҽ���ɨ��������  
	for (int y = 0; y < height; y++)
	{
		int yh = y * width;
		scanline = bmpImg->imageData + y * width;
		for (int x = 0; x <width; x++)    //���д�������ɨ��  
		{
			pn = scanline[x];
			gn = ((gn * q) >> T) + pn;
			hn = (gn + prev_gn[x]) >> 1;     //����������ƽ��  
			prev_gn[x] = gn;
			pn < (hn*factor) >> T ? binImage[yh + x] = 0 : binImage[yh + x] = 0xff;
		}
		y++;
		if (y == height)
		{
			break;
		}
		yh = y * width;
		scanline = bmpImg->imageData + y * width;
		for (int x = width - 1; x >= 0; x--)  //���д�������ɨ��  
		{
			pn = scanline[x];
			gn = ((gn * q) >> T) + pn;
			hn = (gn + prev_gn[x]) >> 1;
			prev_gn[x] = gn;
			pn < (hn*factor) >> T ? binImage[yh + x] = 0 : binImage[yh + x] = 0xff;
		}
	}
	memcpy(bmpImg->imageData, binImage, width * height);
	bool flag = SaveImage("result_quickAdaptiveThreshold.bmp", bmpImg);
	if (flag)
	{
		printf("save quickAdaptiveThreshold ok... \n");
	}
	// �ͷ��ڴ�
	//LocalUnlock(hNewDIBBits);
	free(binImage);
	delete prev_gn;
}


void threshold(Image* bmpImg)//unsigned char* corrupted, unsigned char* trans, int width, int height)
{
	int height = bmpImg->height;
	int width = bmpImg->width;
	unsigned char* trans;
	trans = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
	//memcpy(trans, bmpImg->imageData, width*height*sizeof(unsigned char));
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int k = 0;
			unsigned char window[9];
			for (int jj = j - 1; jj < j + 2; ++jj)
				for (int ii = i - 1; ii < i + 2; ++ii)
					window[k++] = bmpImg->imageData[jj * width + ii];
			//   ��С��������
			for (int m = 0; m < 8; ++m)
			{
				int min = m;
				for (int n = m + 1; n < 9; ++n)
					if (window[n] < window[min])
						min = n;
				//   Put found minimum element in its place  
				unsigned char temp = window[m];
				window[m] = window[min];
				window[min] = temp;
			}
			unsigned char threshold = 0.5*(window[0] + window[8]);
			if (bmpImg->imageData[j*width + i]>threshold)
				trans[j*width + i] = 255;
			else
				trans[j*width + i] = 0;
		}
	}
	memcpy(bmpImg->imageData, trans, width * height);
	bool flag = SaveImage("result_threshold.bmp", bmpImg);
	if (flag)
	{
		printf("save threshold ok... \n");
	}
	// �ͷ��ڴ�
	//LocalUnlock(hNewDIBBits);
	free(trans);
}

void thresholdSet(Image* bmpImg,int threshold)//unsigned char* corrupted, unsigned char* trans, int width, int height)
{
	int height = bmpImg->height;
	int width = bmpImg->width;
	unsigned char* trans;
	trans = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
	memcpy(trans, bmpImg->imageData, width*height*sizeof(unsigned char));
#define trans(i,j) trans[(int)((i)*width)+(int)(j)]
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width ; j++)
		{
			if (trans(i, j) > threshold)
				trans(i, j) = 255;
			else
				trans(i, j) = 0;
		}
	}
	memcpy(bmpImg->imageData, trans, width * height);
	bool flag = SaveImage("result_thresholdSet.bmp", bmpImg);
	if (flag)
	{
		printf("save thresholdSet ok... \n");
	}
	// �ͷ��ڴ�
	//LocalUnlock(hNewDIBBits);
	free(trans);
}
