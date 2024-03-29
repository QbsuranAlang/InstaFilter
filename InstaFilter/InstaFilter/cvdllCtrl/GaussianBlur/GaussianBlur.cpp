#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#define SIZE 256
using namespace cv;

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

IplImage *img, reslut;
static char *windowName = "高斯模糊";
Mat src, dst;

static void onTrackbar(int position)
{
	if(position == 0)
		src.copyTo(dst);
	else if(position & 1)
		GaussianBlur( src, dst, Size( position, position ), 0, 0 );
	else
		GaussianBlur( src, dst, Size( position + 1, position + 1 ), 0, 0 );

	reslut = dst;
	cvShowImage(windowName, &reslut);
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
		if(img->depth != 8)
		{
			cvReleaseImage(&img);
			img = cvLoadImage(inputPath, 1);
		}//end if

		src = img;

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
		int initValue = 11;
		int MAX = img->width > img->height ? img->width : img->height;
		cvCreateTrackbar("大小", windowName, &initValue, MAX / 4, onTrackbar);
		onTrackbar(initValue);
		cvWaitKey(0);
			
		//release
		cvSaveImage(outputPath, &reslut);
		dst.release();
		src.release();
		cvReleaseImage(&img);
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("高斯模糊");
}//end getFIlterName