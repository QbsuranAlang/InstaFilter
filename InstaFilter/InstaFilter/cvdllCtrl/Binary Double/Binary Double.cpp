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

static char *trackbarTH = "高門檻值";//named trackbar
static char *trackbarTL = "低門檻值";
static char *trackbarInverseName = "反轉";
static char *ctrlPanel = "控制面板";
IplImage *img, *bin;
//trackbar event handle function
static void onTrackbar1(int);
static void onTrackbar2(int);
int TH = 200, TL = 100;
static void work(int);
char *windowName = "二值化影像 雙門檻值";

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
		//Show window, then create trackbar
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

		CvSize panelSize = cvSize(600, 135);
		cvNamedWindow(ctrlPanel, 1);
		cvResizeWindow(ctrlPanel, panelSize.width, panelSize.height);
		cvMoveWindow(ctrlPanel, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		cvCreateTrackbar( trackbarTH, ctrlPanel, &TH, 255, onTrackbar1);
		cvCreateTrackbar( trackbarTL, ctrlPanel, &TL, 255, onTrackbar2);
		int zeroPosition = 0;
		cvCreateTrackbar( trackbarInverseName, ctrlPanel, &zeroPosition, 1, work);
		cvShowImage(ctrlPanel, NULL);

		work(0);

		cvWaitKey(0);
		//release
		cvSaveImage(outputPath, bin);
		cvReleaseImage(&img);
		cvReleaseImage(&bin);
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("二值化影像 雙門檻值");
}//end getFIlterName

static void onTrackbar1(int)
{
	if( TH <= TL )
	{
		cvSetTrackbarPos(trackbarTH, windowName, TL);
		cvSetTrackbarPos(trackbarTL, windowName, TL);
	}//end if
	work(0);//binary image
}//end onTrackbar1

static void onTrackbar2(int)
{
	if( TH <= TL )
	{
		cvSetTrackbarPos(trackbarTH, windowName, TH);
		cvSetTrackbarPos(trackbarTL, windowName, TH);
	}//end if
	work(0);//binary image
}//end onTrackbar1

static void work(int)
{
	bin = cvCloneImage(img);

	/*
	 *           TL        TH
	 * --------------------------------------
	 * 0  black      while        black     255
	 *
	 */
	for(int i = 0 ; i < bin->height ; i++)
		for(int j = 0 ; j < bin->width ; j++)
		{
			int index = i * bin->width + j;
			unsigned char temp = bin->imageData[index];

			bool reslut = (TH > temp && temp >= TL);
			if(cvGetTrackbarPos(trackbarInverseName, ctrlPanel))
				reslut = !reslut;
			if(reslut)
				bin->imageData[index] = 255;
			else
				bin->imageData[index] = 0;
		}//end for
	cvShowImage(windowName, bin);
}//end work