#include <stdio.h>
#include <stdlib.h>  
#include "img.h"  

void InteEqualize(Image* bmpImg)//LPSTR lpDIBBits, int width, int height)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	//Image* InteEquaImg;
	// ��ʱ����
	int	i,j,temp;
	int height = bmpImg->height;
	int width = bmpImg->width;
	// �Ҷ�ӳ���
	unsigned char bMap[256];
	// �Ҷȼ�����
	int	Count[256];
	// ͼ��ÿ�е��ֽ���
	int	LineBytes;
	// ����ͼ��ÿ�е��ֽ���
	LineBytes = width;// WIDTHBYTES(width * 8);

	// ���ü���Ϊ0
	for (i = 0; i < 256; i++)
	{
		// ����
		Count[i] = 0;
	}

	// ��������Ҷ�ֵ�ļ���
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			lpSrc = bmpImg->imageData + LineBytes * i + j;
			// ������1
			Count[*(lpSrc)]++;
		}
	}

	// ����Ҷ�ӳ���
	for (i = 0; i < 256; i++)
	{
		// ��ʼΪ0
		temp = 0;

		for (j = 0; j <= i; j++)
		{
			temp += Count[j];
		}

		// �����Ӧ���»Ҷ�ֵ
		bMap[i] = (unsigned char)(temp * 255 / (height * width));
	}

	// ÿ��
	for (i = 0; i < height; i++)
	{
		// ÿ��
		for (j = 0; j < width; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = bmpImg->imageData + LineBytes * (height - 1 - i) + j;

			// �����µĻҶ�ֵ
			*lpSrc = bMap[*lpSrc];
		}
	}
	bool flag = SaveImage("result_equalized.bmp", bmpImg);
	if (flag)
	{
		printf("save equalized ok... \n");
	}
	// ����
	//return InteEquaImg;
}