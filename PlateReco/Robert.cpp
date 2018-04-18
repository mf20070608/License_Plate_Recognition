#include <stdio.h>
#include <stdlib.h>  
#include <math.h>
#include <string.h>
#include "img.h"  

void Robert(Image* bmpImg)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;

	// ָ�򻺴�ͼ���ָ��
	unsigned char*	lpDst;

	// ָ�򻺴�DIBͼ���ָ��
	unsigned char*	lpNewDIBBits;
	//void*	hNewDIBBits;

	//ѭ������
	long i, j;

	//����ֵ
	double result;
	unsigned char pixel[4];

	int height = bmpImg->height;
	int width = bmpImg->width;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	//hNewDIBBits = (void*)malloc(sizeof(unsigned char)*width*height);  // LocalAlloc(LHND, lWidth * lHeight);

	/*if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		printf("�����ڴ�ʧ��");
	}
	*/

	// �����ڴ�
	//lpNewDIBBits = (char *)LocalLock(hNewDIBBits);
	lpNewDIBBits = (unsigned char*)malloc(sizeof(unsigned char)*width*height);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = lpNewDIBBits;
	memset(lpDst, (unsigned char)255, width * height);


	//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
	for (j = height - 1; j > 0; j--)
	{
		for (i = 0; i <width - 1; i++)
		{
			//����ʹ��2��2��ģ�壬Ϊ��ֹԽ�磬���Բ��������±ߺ����ұߵ���������

			// ָ��Դͼ���j�У���i�����ص�ָ��			
			lpSrc = bmpImg->imageData + width * j + i;

			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = lpNewDIBBits + width * j + i;

			//ȡ�õ�ǰָ�봦2*2���������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel[0] = (unsigned char)*lpSrc;
			pixel[1] = (unsigned char)*(lpSrc + 1);
			pixel[2] = (unsigned char)*(lpSrc - width);
			pixel[3] = (unsigned char)*(lpSrc - width + 1);

			//����Ŀ��ͼ���еĵ�ǰ��
			result = sqrt((float)(pixel[0] - pixel[3])*(pixel[0] - pixel[3]) + \
				(pixel[1] - pixel[2])*(pixel[1] - pixel[2]));
			*lpDst = (unsigned char)result;

		}
	}

	// ���Ƹ�ʴ���ͼ��
	memcpy(bmpImg->imageData, lpNewDIBBits, width * height);
	bool flag = SaveImage("result_Robert.bmp", bmpImg);
	if (flag)
	{
		printf("save Robert ok... \n");
	}
	// �ͷ��ڴ�
	//LocalUnlock(hNewDIBBits);
	free(lpNewDIBBits);
}
