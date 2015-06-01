#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#include <opencv2/imgproc/imgproc.hpp>
#define SIZE 256
using namespace cv;

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

IplImage *img, *dst, *reslut;
static char *windowName = "雜訊";
static int position = 10;
static void work(int num);

static void onTrackbar(int)
{
	work(position);
	cvShowImage(windowName, dst);
	cvReleaseImage(&dst);
}//end onTrackbar

static void work(int num)
{
	dst = cvCloneImage(img);
	RNG rng(cvGetTickCount());
	for(int i = 0 ; i < (dst->height*dst->widthStep)/255 * num ; i++)
	{
		int x = rng.uniform(0, img->height-1);
		int y = rng.uniform(0, img->widthStep-1);
		int index = x * dst->widthStep + y;
		dst->imageData[index] = rng.uniform(0, 255);
		dst->imageData[index+1] = rng.uniform(0, 255);
		dst->imageData[index+2] = rng.uniform(0, 255);
	}//end for
}//end work

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
		cvCreateTrackbar("雜訊量", windowName, &position, 255, onTrackbar);
		onTrackbar(0);

		cvWaitKey(0);

		work(position);
		cvDestroyAllWindows();
		cvSaveImage(outputPath, dst);
		cvReleaseImage(&img);
		cvReleaseImage(&dst);
		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("增加雜訊");
}//end getFIlterName