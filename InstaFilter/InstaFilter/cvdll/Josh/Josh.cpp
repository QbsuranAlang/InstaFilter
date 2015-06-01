#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
using namespace cv;
#define SIZE 256

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

void adjustBrightnessContrast(IplImage *&src, int Brightness, int Contrast);

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
		unsigned char R[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
		unsigned char G[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
		unsigned char B[] = {62,63,64,64,65,66,67,68,68,69,70,71,71,72,73,74,75,75,76,77,78,79,79,80,81,82,82,83,84,85,86,86,87,88,89,89,90,91,92,92,93,94,95,95,96,97,98,98,99,100,101,101,102,103,104,104,105,106,107,107,108,109,110,110,111,112,112,113,114,115,115,116,117,117,118,119,119,120,121,122,122,123,124,124,125,126,126,127,128,128,129,129,130,131,131,132,133,133,134,135,135,136,136,137,138,138,139,139,140,141,141,142,142,143,143,144,145,145,146,146,147,147,148,148,149,149,150,150,151,152,152,153,153,153,154,154,155,155,156,156,157,157,158,158,159,159,159,160,160,161,161,162,162,162,163,163,164,164,164,165,165,166,166,166,167,167,167,168,168,169,169,169,170,170,170,171,171,171,172,172,172,173,173,173,174,174,174,175,175,175,175,176,176,176,177,177,177,178,178,178,178,179,179,179,180,180,180,180,181,181,181,181,182,182,182,182,183,183,183,183,184,184,184,184,185,185,185,185,186,186,186,186,187,187,187,187,188,188,188,188,189,189,189,189,189,190,190,190,190,191,191,191,191,192,192,192};
		
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

		adjustBrightnessContrast(img, 0, 100);
		//release
		cvSaveImage(outputPath, img);

		cvReleaseImage(&img);
		cvReleaseImage(&temp);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Josh");
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