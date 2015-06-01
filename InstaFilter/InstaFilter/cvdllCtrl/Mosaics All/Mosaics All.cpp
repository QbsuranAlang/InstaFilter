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

static int W = 10;
static int H = 10;
static char *windowName = "馬賽克";
IplImage *img, *dst;
static void work();

static void onTrackbarW(int position)
{
	W = position;
	work();
	cvShowImage(windowName, dst);
}

static void onTrackbarH(int position)
{
	H = position;
	work();
	cvShowImage(windowName, dst);
}

static void work()
{
	if( W == 0 || H == 0 )
		dst = cvCloneImage(img);
	else
	{
		CvPoint p0 = cvPoint(0, 0);
		CvPoint p1 = cvPoint(img->width, img->height);
		dst = cvCloneImage(img);
		for(int i = 1 ; i <= W ; i++)
			for(int j = 1 ; j <= H; j++)
			{
				int w = (p1.x-p0.x)/W;
				int h = (p1.y-p0.y)/H;
				int X = p0.x + w*(i-1);
				int Y = p0.y + h*(j-1);
				cvSetImageROI(dst, cvRect(X, Y, w, h));
				CvScalar mean = cvAvg(dst);
				cvSet(dst, mean);
				cvResetImageROI(dst);
			}
	}
}

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
	
		size.height += 90;

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		int initValueW = W;
		int initValueH = H;
		cvCreateTrackbar("寬", windowName, &initValueW, img->width / 10, onTrackbarW);
		cvCreateTrackbar("高", windowName, &initValueH, img->height / 10, onTrackbarH);
		work();

		cvShowImage(windowName, dst);
		cvWaitKey();
		cvSaveImage(outputPath, dst);
		cvDestroyAllWindows();
		cvReleaseImage(&img);
		cvReleaseImage(&dst);

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("馬賽克");
}//end getFIlterName