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
static char *windowName = "自訂馬賽克區域";
static char *ctrlPanel = "控制面板";
static int foo = 50;//ROI rect
static int Thickness = 5;//ROI bound
static int MosaicsW = 5;//mosaics width
static int MosaicsH = 5;//mosaics height
static int isDo = 1; //do or undo

static void onTrackbarROI(int position)
{
	foo = position / 2;
}

static void onTrackbarBound(int position)
{
	Thickness = position;
}

static void onTrackbarMosaicsW(int position)
{
	MosaicsW = position;
}

static void onTrackbarMosaicsH(int position)
{
	MosaicsH = position;
}

static void doOrUndo(int position)
{
	isDo = position;
}

static void on_mouse( int Event, int x, int y, int flags, void* ustc)
{
	CvPoint p0 = cvPoint(x - foo, y - foo);
	CvPoint p1 = cvPoint(x + foo, y + foo);

	//deter ROI
	//corner
	if(x<foo && y<foo)
	{
		p0 = cvPoint(0, 0);
		p1 = cvPoint(2*foo, 2*foo);
	}
	else if(x>img->width-foo && y<foo)
	{
		p0 = cvPoint(img->width-2*foo, 0);
		p1 = cvPoint(img->width, 2*foo);
	}
	else if(x<foo && y>img->height-foo)
	{
		p0 = cvPoint(0, img->height-2*foo);
		p1 = cvPoint(2*foo, img->height);
	}
	else if(x>img->width-foo && y>img->height-foo)
	{
		p0 = cvPoint(img->width-2*foo, img->height-2*foo);
		p1 = cvPoint(img->width, img->height);
	}//end else
	//border
	else if(x < foo)
	{
		p0 = cvPoint(0, y-foo);
		p1 = cvPoint(2*foo, y+foo);
	}
	else if(x > img->width - foo)
	{
		p0 = cvPoint(img->width-2*foo, y-foo);
		p1 = cvPoint(img->width, y + foo);
	}

	else if(y < foo)
	{
		p0 = cvPoint(x-foo, 0);
		p1 = cvPoint(x+foo, 2*foo);
	}
	else if(y > img->height - foo)
	{
		p0 = cvPoint(x-foo, img->height-2*foo);
		p1 = cvPoint(x+foo, img->height);
	}

	if(flags & CV_EVENT_FLAG_LBUTTON)//left mouse click
	{
		if(isDo)
			//draw mosaics
			for(int i = 1 ; i <= MosaicsW ; i++)
				for(int j = 1 ; j <= MosaicsH; j++)
				{
					int w = (p1.x-p0.x)/MosaicsW;
					int h = (p1.y-p0.y)/MosaicsH;
					int X = p0.x + w*(i-1);
					int Y = p0.y + h*(j-1);
					cvSetImageROI(dst, cvRect(X, Y, w, h));
					CvScalar mean = cvAvg(dst);
					cvSet(dst, mean);
					cvResetImageROI(dst);
				}//end for
		else//undo
		{
			cvSetImageROI(img, cvRect(p0.x, p0.y, p1.x-p0.x, p1.y-p0.y));
			cvSetImageROI(dst, cvRect(p0.x, p0.y, p1.x-p0.x, p1.y-p0.y));
			cvResize(img, dst, CV_INTER_LINEAR);
			cvResetImageROI(img);
			cvResetImageROI(dst);
		}//end else
	}//end else

	//draw rect ROI
	IplImage *rectImg = cvCloneImage(dst);
	cvRectangle(rectImg, p0, p1, CV_RGB(180, 255, 0), Thickness); //draw
	cvShowImage( windowName, rectImg );
	cvReleaseImage(&rectImg);
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
		dst = cvCloneImage(img);
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
		cvSetMouseCallback( windowName, on_mouse, 0 );//add mouse event
		cvShowImage(windowName, img);

		//ctrl panel window
		int initROIValue = foo * 2;
		int initWHBValue = 5;
		cvNamedWindow(ctrlPanel, 1);
		cvResizeWindow(ctrlPanel, 600, 215); 
		cvMoveWindow(ctrlPanel, (xScreen-size.width)/2, (yScreen-size.height)/2 );
		int MAX = img->width > img->height ? img->width : img->height; //set max of rect size
		cvCreateTrackbar("矩形大小", ctrlPanel, &initROIValue, MAX / 2, onTrackbarROI);
		cvCreateTrackbar("矩形邊框", ctrlPanel, &initWHBValue, MAX / 40, onTrackbarBound);
		cvCreateTrackbar("馬賽克寬", ctrlPanel, &initWHBValue, img->width / 10, onTrackbarMosaicsW);
		cvCreateTrackbar("馬賽克高", ctrlPanel, &initWHBValue, img->height / 10, onTrackbarMosaicsH);
		int i = 1;
		cvCreateTrackbar("復原/製作", ctrlPanel, &i, 1, doOrUndo);
		cvShowImage(ctrlPanel, NULL);

		cvWaitKey(0);
		cvSaveImage(outputPath, dst);
		cvReleaseImage(&img);
		cvReleaseImage(&dst);
		cvDestroyAllWindows();

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("自訂馬賽克區域");
}//end getFIlterName