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
		cv::RNG rng(cvGetTickCount());
		unsigned char LookupTableData[256];
		CvMat *LookupTableMatrix;
		
		int Brightness = rng.uniform(100, 180) - 100;
		int Contrast = rng.uniform(100, 180) - 100;
		double Delta;
		double a, b;
		int y;

		IplImage *filterB = cvCreateImage(cvGetSize(img), img->depth, 1);
		IplImage *filterG = cvCreateImage(cvGetSize(img), img->depth, 1);
		IplImage *filterR = cvCreateImage(cvGetSize(img), img->depth, 1);
		cvSplit(img, filterB, filterG, filterR, 0);

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

		LookupTableMatrix = cvCreateMatHeader(1,256,CV_8UC1);
		cvSetData(LookupTableMatrix, LookupTableData, 0);

		cvLUT(filterB, filterB, LookupTableMatrix);
		cvLUT(filterG, filterG, LookupTableMatrix);
		cvLUT(filterR, filterR, LookupTableMatrix);

		IplImage *dst = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		cvMerge(filterB, filterG, filterR, 0, dst);
		
		//release
		cvSaveImage(outputPath, dst);
		cvReleaseImage(&img);
		cvReleaseImage(&dst);
		cvReleaseImage(&filterB);
		cvReleaseImage(&filterG);
		cvReleaseImage(&filterR);

		//record Brightness Contrast
		char bcPath[SIZE] = "";
		sprintf(bcPath, "%s\\InstaFilter\\Brightness and Contrast.if", getenv("temp"));
		FILE *bc = fopen(bcPath, "wb");
		if(!bc) return false;
		fprintf(bc, "%d %d", Brightness, Contrast);
		fclose(bc);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("調整亮度和對比");
}//end getFIlterName