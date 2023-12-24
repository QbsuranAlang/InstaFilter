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
		unsigned char R[] = {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,13,13,14,15,15,16,17,17,18,19,20,20,21,22,23,24,25,26,27,28,28,30,31,32,33,34,35,36,37,39,40,41,42,44,45,47,48,49,51,53,54,56,57,59,61,63,64,66,68,70,72,74,76,78,80,82,84,87,89,91,93,96,98,100,103,105,107,109,111,114,116,118,120,122,124,126,128,130,132,134,136,138,140,141,143,145,147,149,150,152,154,155,157,159,160,162,163,165,166,168,169,171,172,174,175,177,178,179,181,182,183,185,186,187,188,190,191,192,193,194,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,213,214,215,216,217,218,218,219,220,221,221,222,223,224,224,225,226,226,227,228,228,229,229,230,231,231,232,232,233,233,234,235,235,236,236,237,237,237,238,238,239,239,240,240,241,241,241,242,242,243,243,243,244,244,244,245,245,245,246,246,246,247,247,247,248,248,248,249,249,249,249,250,250,250,250,251,251,251,252,252,252,252,253,253,253,253,254,254,254,254,255,255,255};
		unsigned char G[] = {0,1,1,2,2,3,4,4,5,6,6,7,7,8,9,9,10,11,11,12,13,13,14,15,15,16,17,17,18,19,19,20,21,22,22,23,24,25,25,26,27,28,28,29,30,31,32,32,33,34,35,36,37,38,39,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,55,56,57,58,59,60,61,63,64,65,66,68,69,70,71,73,74,75,77,78,80,81,82,84,85,87,88,90,92,93,95,96,98,100,101,103,105,106,108,110,112,114,115,117,119,121,123,124,126,128,130,132,133,135,137,138,140,142,143,145,147,148,150,151,153,154,156,157,159,160,162,163,165,166,167,169,170,171,173,174,175,177,178,179,180,182,183,184,185,186,187,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,209,210,211,212,213,214,214,215,216,217,218,218,219,220,221,221,222,223,224,224,225,226,226,227,228,228,229,230,230,231,232,232,233,234,234,235,235,236,237,237,238,238,239,239,240,241,241,242,242,243,243,244,244,245,245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,254,254,255,255};
		unsigned char B[] = {0,1,2,3,4,5,6,7,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,67,68,69,70,71,72,73,74,75,76,77,77,78,79,80,81,82,83,84,84,85,86,87,88,89,89,90,91,92,93,93,94,95,96,96,97,98,99,100,100,101,102,103,103,104,105,106,106,107,108,109,109,110,111,112,113,113,114,115,116,117,117,118,119,120,121,122,122,123,124,125,126,127,128,129,130,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,173,174,175,176,177,178,179,180,181,182,184,185,186,187,188,189,190,191,193,194,195,196,197,198,199,201,202,203,204,205,206,208,209,210,211,212,213,215,216,217,218,219,220,222,223,224,225,226,228,229,230,231,232,233,235,236,237,238,239,241,242,243,244,245,247,248,249,250,251,253,254,255};
		
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
		adjustBrightnessContrast(img, -15, 71);
		
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
	return _T("Anne");
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