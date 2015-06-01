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
	IplImage *img = cvLoadImage(inputPath, 0);
	if(!img)
		return false;
	else
	{
		IplImage *reconstruction;
		reconstruction = cvCreateImage( cvGetSize(img), img->depth, 3);
		cvCvtColor(img, reconstruction, CV_BayerGR2BGR);//inbluit function
			
		//release
		cvSaveImage(outputPath, reconstruction);
		cvReleaseImage(&reconstruction);
		cvReleaseImage(&img);

		return true;
	}//end else

	cvReleaseImage(&img);
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("BayerGRGB to BGR");
}//end getFIlterName