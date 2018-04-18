//img.h
#ifndef IMG_H  
#define IMG_H  

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)                                                                                            
#define MIN(X,Y) ((X)>(Y)?(Y):(X))
#define MAX(X,Y) ((X)<(Y)?(Y):(X))
#define CAN_REGION_NUM 8
#define PRE_LOCATION_BIAS 5

typedef struct
{
	//BitMapFileHeader
	//unsigned short    bfType;  
	unsigned long    bfSize;
	unsigned short    bfReserved1;
	unsigned short    bfReserved2;
	unsigned long    bfOffBits;
	//BitMapInfoHeader
	unsigned long  biSize;
	long   biWidth;
	long   biHeight;
	unsigned short   biPlanes;
	unsigned short   biBitCount;
	unsigned long  biCompression;
	unsigned long  biSizeImage;
	long   biXPelsPerMeter;
	long   biYPelsPerMeter;
	unsigned long   biClrUsed;
	unsigned long   biClrImportant;
}BMP;

typedef struct
{
	//RgbQuad 
	unsigned char rgbBlue; //����ɫ����ɫ����  
	unsigned char rgbGreen; //����ɫ����ɫ����  
	unsigned char rgbRed; //����ɫ�ĺ�ɫ����  
	unsigned char rgbReserved; //����ֵ 
}BMPQuad;

typedef struct
{
	int x1, x2;
	int y1, y2;
	int width;
	int height;
	float rate;		//��߱�
}PreRegion;			//��ͨ��

typedef struct
{
	int width;
	int height;
	int channels;
	unsigned char* imageData;
	int region_num;				//������
	PreRegion* pre_region;		//��ͨ��ָ��
}Image;

typedef struct
{
	int x;
	int y;
}XY_Queue;

typedef struct
{
	int top;
	int bottom;
	int left;
	int right;
}CRect;


Image* LoadImage(char* path);
bool SaveImage(char* path, Image* bmpImg);

Image* Rgb2Gray(Image* bmpImg);
Image* Rgb2Hsv(const Image* imgRGB);
Image* PlateFilter(Image* imgHSV);

/***************************************�˲���****************************************/
//void _medianfilter(Image* bmpImg);
void InteEqualize(Image* bmpImg);							//ֱ��ͼ���⻯
void grayStretch(Image* src, int nMin, int nMax);			//�Ҷ�����
void Gaussian(Image* bmpImg);								//��˹ģ��
void medianFilter(Image* bmpImg);							//��ֵ�˲�

/***************************************��Ե���**************************************/
void horizonGrad(Image* bmpImg, int threshold);				//ˮƽ�ݶ�
void JumpPoint(Image* bmpImg);								//ˮƽ�����
void Robert(Image* bmpImg);									//Robert��Ե�������
void Sobel(Image* bmpImg);									//Sobel��Ե�������
void SobelVertical(Image* bmpImg);							//��ֱSobel��Ե�������
void edgesob8(unsigned char *image, int width, int height); //Sobel(8����)
void Canny(Image* bmpImg);									//Canny��Ե�������

/***************************************���͸�ʴ**************************************/
void Erosion(Image* srcImage, int nMode);     				//��ʴ
void Dilation(Image* srcImage, int nMode);					//����
void EdgeErasion(Image* srcimage, int threshold);			//ȥ�����ͺ���ı�

/***************************************��ֵ��****************************************/
int otsu(Image *image);										//otsuǰ��������ֵ�㷨
void threshold(Image* bmpImg);								//��ֵΪW(x,y)=0.5*(max f(x+m,y+n)+min f(x+m,y+n))
void thresholdSet(Image* bmpImg, int threshold);				//�ֶ����ö�ֵ����ֵ
void quickAdaptiveThreshold(Image* bmpImg);					//A fast adaptive image binarization method (Wellner 1993)
//void ThresholdTrans(Image* bmpImg);
/************************************Ѱ�ҳ��Ʊ�Ե**************************************/
int TraceEdge(int w, int h, int widthStep, int nThrLow, unsigned char* pResult, int *pMag);
//void location(Image* ImgPlate, int yuzhi, int *HL, int *HH, int *VL, int *VH);
CRect* location(Image* ImgPlate, int yuzhi);					//��λ���ƾ��Σ�һ�������ڲ��õ�sob8����Ե
void TopBottom(Image* bmpImg, int* iTop, int* iBottom);		//Ѱ�����±߽�
void LeftRight(Image* bmpImg, int* iLeft, int* iRight);		//Ѱ�����ұ߽�
void Hough(Image* srcImg, int yuzhi);						//Hough�任
CRect* find_connected_region_location(Image* img, int xthreashold, int ythreashold, float rateLow, float rateHigh);		//Ѱ����ͨ����

/***********************************�ڳ����Ʋ�����**************************************/
void PickRec(Image* Img, Image* ImgPlate, CRect* rect);						//���ն�λ���Ʋ�����

#endif  
