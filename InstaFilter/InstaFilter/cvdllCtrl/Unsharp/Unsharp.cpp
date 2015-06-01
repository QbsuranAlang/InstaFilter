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

static char *windowName = "反銳化";
IplImage *img, *dst;
int trackbarValue = 11;
CvMat kernel, *dstFloat;
double k[] = {
	1., 1., 1.,
	1., 1., 1.,
	1., 1., 1. };

void onTrackbar(int)
{
	cvFilter2D( img, dstFloat, &kernel, cvPoint( -1, -1 ) );
	cvConvertScale(dstFloat, dst, 1/9., 0);
	cvSub(img, dst, dst, 0); 
	cvConvertScale(dst, dst, trackbarValue / 10, 0); 
	cvAdd(img, dst, dst, 0);

	cvShowImage(windowName, dst);
}//end onTrackbar

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	img = cvLoadImage(inputPath, -1);
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
	
		size.height += 45;

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 

		cvCreateTrackbar("大小", windowName, &trackbarValue, 255, onTrackbar);

		//create kernel
		if(img->nChannels == 1)
			dstFloat = cvCreateMat(img->height, img->width, CV_64FC1);
		else if(img->nChannels == 3)
			dstFloat = cvCreateMat(img->height, img->width, CV_64FC3);
		else if(img->nChannels == 4)
			dstFloat = cvCreateMat(img->height, img->width, CV_64FC4);
		else
		{
			cvReleaseImage(&img);
			cvReleaseImage(&dst);
			return false;
		}//end else

		kernel = cvMat( 3, 3, CV_64FC1, k );
		dst = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		onTrackbar(trackbarValue);

		cvWaitKey(0);

		cvSaveImage(outputPath, dst);
		cvReleaseImage(&img);
		cvReleaseImage(&dst);
		cvReleaseMat(&dstFloat);
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("反銳化");
}//end getFIlterName