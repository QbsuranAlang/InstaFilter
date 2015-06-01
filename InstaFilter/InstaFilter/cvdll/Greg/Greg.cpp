#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#define SIZE 256

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

void adjustBrightnessContrast(IplImage *&src, int Brightness, int Contrast);
void adjustRGB(IplImage *&src, int R, int G, int B, int subR, int subG, int subB);

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img = cvLoadImage(inputPath, 1);
	if(!img)
		return false;
	else  
	{
		unsigned char R[] = {0,1,1,2,2,3,3,4,5,5,6,6,7,8,8,9,9,10,11,11,12,12,13,14,14,15,16,16,17,17,18,19,19,20,21,21,22,23,24,24,25,26,26,27,28,29,29,30,31,32,33,33,34,35,36,37,38,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,63,64,65,66,67,68,70,71,72,73,74,76,77,78,79,81,82,83,84,86,87,88,90,91,92,94,95,96,98,99,100,102,103,105,106,107,109,110,112,113,115,116,118,119,121,122,124,125,126,128,130,131,133,134,136,137,139,140,142,143,145,146,148,149,151,152,154,155,157,158,160,161,163,164,166,167,169,170,172,173,175,176,177,179,180,182,183,184,186,187,188,189,191,192,193,194,196,197,198,199,200,201,202,204,205,206,207,208,209,210,211,212,213,214,215,216,216,217,218,219,220,221,222,222,223,224,225,226,226,227,228,229,229,230,231,232,232,233,234,234,235,236,236,237,238,238,239,240,240,241,241,242,243,243,244,244,245,246,246,247,247,248,248,249,249,250,251,251,252,252,253,253,254,254,255};
		unsigned char G[] = {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,6,6,7,7,8,9,9,10,11,12,13,14,14,15,17,18,19,20,21,23,24,25,27,28,30,32,33,35,37,39,41,43,45,47,49,52,54,56,59,61,64,66,69,72,74,77,80,83,85,88,91,94,97,99,102,105,108,110,113,116,118,121,123,126,128,131,133,136,138,140,142,144,146,149,151,152,154,156,158,160,162,163,165,167,168,170,171,173,174,176,177,178,180,181,182,183,184,185,187,188,189,190,191,191,192,193,194,195,196,196,197,198,199,199,200,200,201,202,202,203,203,204,204,204,205,205,206,206,206,207,207,207,207,208,208,208,208,208,209,209,209,209,209,209,209,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209,209};
		unsigned char B[] = {0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,6,6,6,7,7,7,8,8,9,9,10,10,11,11,12,13,13,14,15,15,16,17,18,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,34,35,36,37,39,40,41,43,44,45,47,48,50,51,53,54,56,57,59,60,62,63,65,67,68,70,71,73,75,77,78,80,82,83,85,87,89,90,92,94,96,98,99,101,103,105,107,108,110,112,114,116,118,119,121,123,125,127,129,131,132,134,136,138,140,142,143,145,147,149,151,152,154,156,158,160,161,163,165,167,168,170,172,173,175,177,178,180,182,183,185,187,188,190,191,193,194,196,197,199,200,202,203,205,206,207,209,210,211,213,214,215,216,217,219,220,221,222,223,224,225,226,227,228,229,230,231,232,232,233,234,235,235,236,237,238,238,239,239,240,241,241,242,242,243,243,244,244,245,245,246,246,246,247,247,248,248,248,249,249,249,250,250,250,250,251,251,251,251,252,252,252,252,252,253,253,253,253,253,253,254,254,254,254,254,254,254,255,255,255,255};
		
		IplImage *filterR = cvCreateImage(cvSize((int)sqrt((double)(sizeof(R)/sizeof(*R))), (int)sqrt((double)(sizeof(R)/sizeof(*R)))), img->depth, 1);
		IplImage *filterG = cvCreateImage(cvSize((int)sqrt((double)(sizeof(R)/sizeof(*R))), (int)sqrt((double)(sizeof(R)/sizeof(*R)))), img->depth, 1);
		IplImage *filterB = cvCreateImage(cvSize((int)sqrt((double)(sizeof(R)/sizeof(*R))), (int)sqrt((double)(sizeof(R)/sizeof(*R)))), img->depth, 1);

		for(int i = 0 ; i < sizeof(R)/sizeof(*R) ; i++)
		{
			filterR->imageData[i] = R[i];
			filterG->imageData[i] = G[i];
			filterB->imageData[i] = B[i];
		}//end for
	
		IplImage *temp = cvCreateImage(cvGetSize(img), img->depth, 1);
		cvResize(filterB, temp, CV_INTER_LINEAR);
		cvReleaseImage(&filterB);
		filterB = cvCloneImage(temp);
		cvReleaseImage(&temp);

		temp = cvCreateImage(cvGetSize(img), img->depth, 1);
		cvResize(filterG, temp, CV_INTER_LINEAR);
		cvReleaseImage(&filterG);
		filterG = cvCloneImage(temp);
		cvReleaseImage(&temp);

		temp = cvCreateImage(cvGetSize(img), img->depth, 1);
		cvResize(filterR, temp, CV_INTER_LINEAR);
		cvReleaseImage(&filterR);
		filterR = cvCloneImage(temp);
		cvReleaseImage(&temp);

		//merge
		temp = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		cvMerge(filterB, filterG, filterR, 0, temp);
		CvScalar mean = cvAvg(temp);
		cvSet(temp, mean);
		cvAddWeighted(img, 0.5, temp, 0.5, 0, img);
	
		//increase
		adjustRGB(img, 68, 36, 85, 31, 44, 11);
		adjustBrightnessContrast(img, 0, 30);

		cvSaveImage(outputPath, img);

		cvReleaseImage(&filterR);
		cvReleaseImage(&filterG);
		cvReleaseImage(&filterB);
		cvReleaseImage(&img);
		cvReleaseImage(&temp);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Greg");
}//end getFIlterName

void adjustBrightnessContrast(IplImage *&src, int Brightness, int Contrast)
{
	unsigned char LookupTableData[256];
	CvMat *LookupTableMatrix;
	double Delta;
	double a, b;
	int y;

	IplImage *filterB = cvCreateImage(cvGetSize(src), (src)->depth, 1);
	IplImage *filterG = cvCreateImage(cvGetSize(src), (src)->depth, 1);
	IplImage *filterR = cvCreateImage(cvGetSize(src), (src)->depth, 1);
	cvSplit(src, filterB, filterG, filterR, 0);

	//Brightness/Contrast Formula
	if(Contrast > 0)
	{
		Delta = 127 * Contrast / 100;
		a=255 / (255 - Delta * 2);
		b = a * (Brightness - Delta);
	}
	else
	{
		Delta = -128 * Contrast / 100;
		a = (256 - Delta*2) / 255;
		b = a * Brightness + Delta;
	}

	for(int x = 0 ; x < 256 ; x++)
	{
		y=(int)(a * x + b);
		if(y < 0) y = 0; else if(y > 255) y = 255;

		LookupTableData[x]=(uchar)y;
	}

	LookupTableMatrix = cvCreateMatHeader(1, 256, CV_8UC1);
	cvSetData(LookupTableMatrix, LookupTableData, 0);

	cvLUT(filterB, filterB, LookupTableMatrix);
	cvLUT(filterG, filterG, LookupTableMatrix);
	cvLUT(filterR, filterR, LookupTableMatrix);

	IplImage *dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvMerge(filterB, filterG, filterR, 0, dst);

	cvReleaseImage(&src);
	src = cvCloneImage(dst);
	cvReleaseImage(&dst);
	cvReleaseImage(&filterB);
	cvReleaseImage(&filterG);
	cvReleaseImage(&filterR);
	cvReleaseMat(&LookupTableMatrix);
}//end Brightness/Contrast

void adjustRGB(IplImage *&src, int R, int G, int B, int subR, int subG, int subB)
{
	cvAddS(src, CV_RGB(R, G, B), src, 0);
	cvSubS(src, CV_RGB(subR, subG, subB), src, 0);
}