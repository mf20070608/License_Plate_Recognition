//main.cpp
#include <stdio.h>
#include <stdlib.h>  
#include <time.h>
#include "img.h"  


int main()
{	
	char mode_name[20];
	do
	{
		printf("please select the mode:Color Threshold Division or Edge Detection(input number 1 or 2):");		//����ʶ��ģʽѡ��1����ɫ�ָֻ�����������ƣ�2�Ǳ�Ե��ȡ��������������ɫ����
		gets(mode_name);
		printf("\nLet's start ! :)\n");
		if (*mode_name == '1')		//��ɫ�ָ��
		{
			clock_t start, start_dilation, start_sobel, end, end_dilation, end_sobel;
			char YN[20];
			char img_name[20];
				printf("\nplease input the path of the image:");
				gets(img_name);
				start = clock();
				Image* img = LoadImage(img_name);
				Image* imgHSV = Rgb2Hsv(img);
				Image* imgPlate = PlateFilter(imgHSV);

				/****************************�˲���**********************/
				Gaussian(imgPlate);

				/*************************�����ͺ�ʴ**********************/

				start_dilation = clock();
				for (int i = 0; i < 5; i++)
				{
					Dilation(imgPlate, 0);
					Dilation(imgPlate, 1);
				}
				printf("save dilate ok... \n");
				end_dilation = clock();
				printf("//dilation time = %f\n", (double)(end_dilation - start_dilation) / CLOCKS_PER_SEC);
				Erosion(imgPlate, 1);

				/*************************Sobel��Ե����**********************/
				start_sobel = clock();
				Sobel(imgPlate);
				EdgeErasion(imgPlate, 10);		//ȥ����ԵһȦ��ɫ
				end_sobel = clock();
				printf("//sobel time = %f\n", (double)(end_sobel - start_sobel) / CLOCKS_PER_SEC);

				/*************************��ͨ��ɸѡ**********************/
				//��һ��������������С���
				//�ڶ���������������С�߶�
				//������������������С��߱�
				//���ĸ���������������߱�
				int width = img->width;
				int height = img->height;
				CRect* plateRectAll = find_connected_region_location(imgPlate, 90, 30, 2.0, 3.8);

				PickRec(img, imgPlate, plateRectAll);
				printf("\nsave Final ok!!!");

				end = clock();
				printf("\n//time_total= %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
				printf("\n");

		}
		else if (*mode_name == '2')		//��Ե��ȡ����
		{
			clock_t start, start_dilation, start_sobel, end, end_dilation, end_sobel;
			char YN[20];
			char img_name[20];
				printf("please input the path of the image:");
				gets(img_name);
				start = clock();
				Image* img = LoadImage(img_name);
				Image* imgGray = Rgb2Gray(img);

				/***************************��Ե����**********************/
				Sobel(imgGray);

				/***************************�˲���************************/
				medianFilter(imgGray);

				/***************************��ֵ��ֵ��**********************/
				thresholdSet(imgGray, 150);		//���õĻ�Ӧ��������Ӧ�趨��ֵ������ֻ�Ǵ���ȡ��150

				/***************************��ʴ������**********************/
				start_dilation = clock();
				for (int i = 0; i < 3; i++)
				{
					Dilation(imgGray, 0);
				}
				printf("save dilate ok... \n");
				end_dilation = clock();
				printf("//dilation time = %f\n", (double)(end_dilation - start_dilation) / CLOCKS_PER_SEC);
				Erosion(imgGray, 1);

				start_sobel = clock();
				Sobel(imgGray);
				EdgeErasion(imgGray, 10);		//ȥ����ԵһȦ��ɫ
				end_sobel = clock();
				printf("//sobel time = %f\n", (double)(end_sobel - start_sobel) / CLOCKS_PER_SEC);

				/*************************��ͨ��ɸѡ***********************/
				//��һ��������������С���
				//�ڶ���������������С�߶�
				//������������������С��߱�
				//���ĸ���������������߱�
				CRect* plateRectAll = find_connected_region_location(imgGray, 90, 30, 2.3, 3.7);
				PickRec(img, imgGray, plateRectAll);
				printf("\nsave Final ok!!!");

				end = clock();
				printf("\n//time_total= %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
				printf("\n");
		}
	}while (1);
	return 0;
}