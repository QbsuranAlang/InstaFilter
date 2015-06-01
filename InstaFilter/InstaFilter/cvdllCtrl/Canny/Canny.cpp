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
static char *windowName = "Canny";
static char *ctrlPanel = "控制面板";
int T1 = 100, T2 = 50, aSize = 3;

void work(int)
{
	if(!(aSize & 1)) aSize++;
	if(aSize < 3) aSize = 3; 

	cvCanny(img, dst, T1, T2, aSize);
	cvShowImage(windowName, dst);
}//end work

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	img = cvLoadImage(inputPath, 0);
	if(!img)
		return false;
	else  
	{
		dst = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);

		CvSize size = cvGetSize(img); 

		int xScreen = GetSystemMetrics(SM_CXSCREEN);
		int yScreen = GetSystemMetrics(SM_CYSCREEN);
		
		while(size.width + 100 > xScreen || size.height + 100 > yScreen)
		{
			size.width /= 1.4;
			size.height /= 1.4;
		}//end while

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 );
		cvNamedWindow(ctrlPanel, 1);
		CvSize panelSize = cvSize(600, 135);
		cvResizeWindow(ctrlPanel, panelSize.width, panelSize.height);
		cvMoveWindow(ctrlPanel, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		cvCreateTrackbar("門檻值 1", ctrlPanel, &T1, 255, work);
		cvCreateTrackbar("門檻值 2", ctrlPanel, &T2, 255, work);
		cvCreateTrackbar("大小", ctrlPanel, &aSize, 7, work);
		cvShowImage(ctrlPanel, NULL);

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
	return _T("Canny");
}//end getFIlterName