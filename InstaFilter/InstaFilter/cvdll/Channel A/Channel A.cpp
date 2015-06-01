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
	else
	{
		if(img->nChannels == 4)
		{
			//split channel
			IplImage *A = cvCreateImage(cvGetSize(img), img->depth, 1);
			cvSplit(img, NULL, NULL, NULL, A);

			cvSaveImage(outputPath, A);

			cvReleaseImage(&img);
			cvReleaseImage(&A);

			return true;
		}//end if
		else
		{
			cvReleaseImage(&img);
			return false;
		}//end else
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Channel A");
}//end getFIlterName