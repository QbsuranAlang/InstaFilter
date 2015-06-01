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
	IplImage *img = cvLoadImage(inputPath, -1);

	if(!img)
		return false;
	if(img->nChannels > 1)
	{
		if(img->depth != 8)
		{
			cvReleaseImage(&img);
			img = cvLoadImage(inputPath, 1);
		}//end if

		//process
		IplImage *G = cvCreateImage(cvGetSize(img), img->depth, 1);
		IplImage *des = cvCreateImage(cvGetSize(img), img->depth, 3);
		cvSplit(img, NULL, G, NULL, NULL);
		cvMerge(NULL, G, NULL, NULL, des);
		cvSaveImage(outputPath, des);

		cvReleaseImage(&img);
		cvReleaseImage(&G);
		cvReleaseImage(&des);

		return true;
	}//end if

	cvReleaseImage(&img);
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Channel G Image");
}//end getFIlterName