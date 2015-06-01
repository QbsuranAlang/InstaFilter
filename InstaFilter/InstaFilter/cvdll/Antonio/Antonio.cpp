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
		//load gray
		IplImage *tempGray = cvLoadImage(inputPath, 0);
		IplImage *gray = cvCreateImage(cvGetSize(img), img->depth, 3);
		cvMerge(tempGray, tempGray, tempGray, 0, gray);
		cvReleaseImage(&tempGray);

		//blur
		Mat Gray = gray;
		GaussianBlur( Gray, Gray, Size( 71, 71 ), 0, 0 );

		//blend
		IplImage *reslut = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		cvAddWeighted(img, 0.5, gray, 0.5, 0, reslut);
		
		cvSaveImage(outputPath, reslut);

		cvReleaseImage(&reslut);
		Gray.release();
		cvReleaseImage(&img);
		cvReleaseImage(&gray);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Antonio");
}//end getFIlterName