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

IplImage *img, *dst;
static char *windowName = "Morphological Gradient";
static int times = 1;
static int isColor = 0;

void work(int)
{
	cvReleaseImage(&dst);
	if(isColor)
	{
		dst = cvCloneImage(img);
		if(times != 0)
			cvMorphologyEx(img, dst, 0, 0, CV_MOP_GRADIENT, times);
	}//end if
	else
	{
		IplImage *gray = cvCreateImage(cvGetSize(img), img->depth, 1);
		cvCvtColor(img, gray, CV_BGR2GRAY);
		dst = cvCloneImage(gray);

		if(times != 0)
			cvMorphologyEx(gray, dst, 0, 0, CV_MOP_GRADIENT, times);

		cvReleaseImage(&gray);
	}
	cvShowImage(windowName, dst);
}//end work

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	img = cvLoadImage(inputPath, 1);
	if(!img)
		return false;
	else  
	{
		CvSize size = cvGetSize(img); 

		int xScreen = GetSystemMetrics(SM_CXSCREEN);
		int yScreen = GetSystemMetrics(SM_CYSCREEN);
		
		while(size.width + 100 > xScreen || size.height + 100 > yScreen)
		{
			size.width /= 1.4;
			size.height /= 1.4;
		}//end while

		size.height += 90;

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 );
		cvCreateTrackbar("次數", windowName, &times, 50, work);
		cvCreateTrackbar("黑白/彩色", windowName, &isColor, 1, work);

		work(0);
		cvWaitKey(0);

		//release
		cvDestroyAllWindows();
		cvSaveImage(outputPath, dst);
		cvReleaseImage(&dst);
		cvReleaseImage(&img);
		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Morphological Gradient");
}//end getFIlterName