#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <math.h>
#include "img.h"  

/*************************************************************************
* �������ƣ�
*   Dilation()
* ����:
*   unsigned char* lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   int  lWidth       - Դͼ���ȣ���������������4�ı�����
*   int  lHeight      - Դͼ��߶ȣ���������
*   int   nMode		- ���ͷ�ʽ��0��ʾˮƽ����1��ֱ����2�Զ���ṹԪ�ء�
*	 int   structure[3][3]	- �Զ����3��3�ṹԪ�ء�
* ����ֵ:
*   BOOL               - ���ͳɹ�����TRUE�����򷵻�FALSE��
* ˵��:
* �ú������ڶ�ͼ������������㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬
* �м��λ��ԭ�㣻�������û��Լ�����3��3�ĽṹԪ�ء�
* Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
************************************************************************/
void Dilation(Image* srcImage, int nMode)//int structure[3][3])
{
	int lHeight = srcImage->height;
	int lWidth = srcImage->width;
	unsigned char* lpDIBBits = srcImage->imageData;
	unsigned char*	lpSrc;			// ָ��Դͼ���ָ��	
	unsigned char*	lpDst;			// ָ�򻺴�ͼ���ָ��	
	unsigned char*	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	//HLOCAL	hNewDIBBits;
	long i, j, n, m;			//ѭ������
	unsigned char pixel;	//����ֵ

	int structure[15][15] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1,1},
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
		{ 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 },
	};

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	//hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	lpNewDIBBits = (unsigned char *)malloc(sizeof(unsigned char)*lWidth*lHeight);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = lpNewDIBBits;
	memset(lpDst, 255, lWidth * lHeight);

	if (nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ�������
		for (j = 0; j <lHeight; j++)
		{
			for (i = 1; i <lWidth - 1; i++)
			{
				// ����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
				// ����������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = lpDIBBits + lWidth * j + i;
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = lpNewDIBBits + lWidth * j + i;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}
			}
		}
	}
	else if (nMode == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ�������
		for (j = 1; j <lHeight - 1; j++)
		{
			for (i = 0; i <lWidth; i++)
			{
				// ����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±�
				// ����������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = lpDIBBits + lWidth * j + i;
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = lpNewDIBBits + lWidth * j + i;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1)*lWidth);
					if (pixel == 255)
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}
			}
		}
	}
	else
	{
		//ʹ���Զ���ĽṹԪ�ؽ�������
		for (j = 7; j <lHeight - 7; j++)
		{
			for (i = 7; i <lWidth-7; i++)
			{
				// ����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
				// ���������غ����ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = lpDIBBits + lWidth * j + i;
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = lpNewDIBBits + lWidth * j + i;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ������һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				//ע����DIBͼ�������������µ��õ�
				for (m = 0; m < 15; m++)
				{
					for (n = 0; n < 15; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((14 - m) - 7)*lWidth + (n - 7));
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}
				}
			}
		}
	}

	// �������ͺ��ͼ��

	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	bool flag = SaveImage("result_dilate.bmp", srcImage);
	if (!flag)
	{
		printf("Dilation Fail!");
	}
	free(lpNewDIBBits);
}

/*************************************************************************
* �������ƣ�
*   Erosion()
* ����:
*   unsigned char* lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   int  lWidth       - Դͼ���ȣ���������������4�ı�����
*   int  lHeight      - Դͼ��߶ȣ���������
*   int   nMode		- ��ʴ��ʽ��0��ʾˮƽ����1��ֱ����2�Զ���ṹԪ�ء�
*	 int   structure[3][3]	- �Զ����3��3�ṹԪ�ء�
* ����ֵ:
*   BOOL               - ��ʴ�ɹ�����TRUE�����򷵻�FALSE��
* ˵��:
* �ú������ڶ�ͼ����и�ʴ���㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬
* �м��λ��ԭ�㣻�������û��Լ�����3��3�ĽṹԪ�ء�
* Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
************************************************************************/

void Erosion(Image* srcImage, int nMode)
{
	int lHeight = srcImage->height;
	int lWidth = srcImage->width;
	unsigned char* lpDIBBits = srcImage->imageData;
	unsigned char*	lpSrc;			// ָ��Դͼ���ָ��	
	unsigned char*	lpDst;			// ָ�򻺴�ͼ���ָ��	
	unsigned char*	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��

	long i, j, m, n;			//ѭ������	
	unsigned char pixel;	//����ֵ

	int structure[3][5] = {
		{1,1,1,1,1},
		{1,1,1,1,1},
		{1,1,1,1,1}
	};

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	//hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	lpNewDIBBits = (unsigned char *)malloc(sizeof(unsigned char)*lWidth*lHeight);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = lpNewDIBBits;
	memset(lpDst, 255, lWidth * lHeight);

	if (nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
		for (j = 0; j <lHeight; j++)
		{
			for (i = 1; i <lWidth - 1; i++)
			{
				// ����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
				// ����������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = lpDIBBits + lWidth * j + i;
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = lpNewDIBBits + lWidth * j + i;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + n - 1);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}
			}
		}
	}
	else if (nMode == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ��и�ʴ
		for (j = 1; j <lHeight - 1; j++)
		{
			for (i = 0; i <lWidth; i++)
			{
				// ����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±�
				// ����������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = lpDIBBits + lWidth * j + i;
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = lpNewDIBBits + lWidth * j + i;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				for (n = 0; n < 3; n++)
				{
					pixel = *(lpSrc + (n - 1)*lWidth);
					if (pixel == 0)
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}
			}
		}
	}
	else
	{
		//ʹ���Զ���ĽṹԪ�ؽ��и�ʴ
		for (j = 1; j <lHeight - 1; j++)
		{
			for (i = 2; i <lWidth-2; i++)
			{
				// ����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
				// ���������غ����ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = lpDIBBits + lWidth * j + i;
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = lpNewDIBBits + lWidth * j + i;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = *lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = 255;

				//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				//ע����DIBͼ�������������µ��õ�
				for (m = 0; m < 3; m++)
				{
					for (n = 0; n < 5; n++)
					{
						if (structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2 - m) - 1)*lWidth + (n - 2));
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}
				}
			}
		}
	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	bool flag = SaveImage("result_erode.bmp", srcImage);
	if (flag)
	{
		printf("save erode ok... \n");
	}
	free(lpNewDIBBits);
}

//EdgeErasion()ȥ����ʴ���һȦ��ɫ��Ե
void EdgeErasion(Image* srcimage,int threshold)
{
	int h = srcimage->height;
	int w = srcimage->width;
	unsigned char* dstData;
	dstData = (unsigned char*)malloc(sizeof(unsigned char)*w*h);
	memcpy(dstData, srcimage->imageData, w*h);

	int i, j;
	for (j = 0; j < threshold; j++)
		for (i = 0; i < w; i++)
		{
			dstData[j*w + i] = (unsigned char)0;
		}
	for (j = h - threshold; j < h; j++)
		for (i = 0; i < w; i++)
		{
			dstData[j*w + i] = (unsigned char)0;
		}
	for (i = 0; i < threshold; i++)
		for (j = threshold; j < h - threshold; j++)
		{
			dstData[j*w + i] = 0;
		}
	for (i = w - threshold; i < w; i++)
		for (j = threshold; j < h - threshold; j++)
		{
			dstData[j*w + i] = 0;
		}
	memcpy(srcimage->imageData, dstData, w*h);
	bool flag = SaveImage("result_erase.bmp", srcimage);
	if (flag)
	{
		printf("save erase ok... \n");
	}
	free(dstData);
}   

/*
void erode_image(Image * src)
{
	Image * dst;
	dst = (Image*)malloc(sizeof(Image));
	if (src == NULL || dst == NULL)
		return;

	int width = src->width;
	int height = src->height;

	//ˮƽ����ĸ�ʴ  
	for (int i = 0; i < src->height; i++)
	{
		for (int j = 1; j < src->width - 1; j++)
		{
			//  data = ((unsigned char *)(src->imageData + src->width * i))[j];  
			if (((unsigned char *)(src->imageData + src->width * i))[j] == 0)
			{
				((unsigned char *)(dst->imageData + dst->width * i))[j] = 0;
				for (int k = 0; k < 3; k++)
				{
					//  data = ((unsigned char *)(src->imageData + src->width * i))[j + k -1];  
					if (((unsigned char *)(src->imageData + src->width * i))[j + k - 1] == 255)
					{
						((unsigned char *)(dst->imageData + dst->width * i))[j] = 255;
						break;
					}
				}
			}
			else
				((unsigned char *)(dst->imageData + dst->width * i))[j] = 255;
		}
	}
	//��ֱ����ĸ�ʴ  
	for (int i = 0; i < dst->width; i++)
	{
		for (int j = 1; j < dst->height - 1; j++)
		{
			//  data = ((unsigned char *)(src->imageData + src->width * i))[j];  
			if (((unsigned char *)(dst->imageData + dst->width * j))[i] == 0)
			{
				((unsigned char *)(src->imageData + src->width * j))[i] = 0;
				for (int k = 0; k < 3; k++)
				{
					//  data = ((unsigned char *)(src->imageData + src->width * i))[j + k -1];  
					if (((unsigned char *)(dst->imageData + dst->width * (j + k - 1)))[i] == 255)
					{
						((unsigned char *)(src->imageData + src->width * j))[i] = 255;
						break;
					}
				}
			}
			else
				((unsigned char *)(src->imageData + src->width * j))[i] = 255;
		}
	}
	memcpy(src->imageData, dst->imageData, src->height * src->width);
	bool flag = SaveImage("result_erode.bmp", dst);
	if (flag)
	{
		printf("save erode ok... \n");
	}
	free(dst);
}

void dilate_image(Image * src)
{
	Image * dst;
	dst = (Image*)malloc(sizeof(Image));
	if (src == NULL || dst == NULL)
		return;

	int width = src->width;
	int height = src->height;

	//ˮƽ���������  
	for (int i = 0; i < src->height; i++)
	{
		for (int j = 1; j < src->width - 1; j++)
		{
			if (((unsigned char *)(src->imageData + src->width * i))[j] == 255)
			{
				((unsigned char *)(dst->imageData + dst->width * i))[j] = 255;
				for (int k = 0; k < 3; k++)
				{
					if (((unsigned char *)(src->imageData + src->width * i))[j + k - 1] == 0)
					{
						((unsigned char *)(dst->imageData + dst->width * i))[j] = 0;
						break;
					}
				}
			}
			else
				((unsigned char *)(dst->imageData + dst->width * i))[j] = 0;
		}
	}
	//��ֱ���������  
	for (int i = 0; i < dst->width; i++)
	{
		for (int j = 1; j < dst->height - 1; j++)
		{
			//  data = ((unsigned char *)(src->imageData + src->width * i))[j];  
			if (((unsigned char *)(dst->imageData + dst->width * j))[i] == 255)
			{
				((unsigned char *)(src->imageData + src->width * j))[i] = 255;
				for (int k = 0; k < 3; k++)
				{
					//  data = ((unsigned char *)(src->imageData + src->width * i))[j + k -1];  
					if (((unsigned char *)(dst->imageData + dst->width * (j + k - 1)))[i] == 0)
					{
						((unsigned char *)(src->imageData + src->width * j))[i] = 0;
						break;
					}
				}
			}
			else
				((unsigned char *)(src->imageData + src->width * j))[i] = 0;
		}
	}
	memcpy(src->imageData, dst->imageData, src->height * src->width);
	bool flag = SaveImage("result_dilate.bmp", dst);
	if (flag)
	{
		printf("save dilate ok... \n");
	}
	free(dst);
}
*/