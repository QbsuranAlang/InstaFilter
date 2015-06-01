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

IplImage *img, reslut;
static void work(int x, int y);
static char *windowName = "凸透鏡";
static int slider;
Mat dst;

static void onTrackbar(int position)
{
	slider = position;
	work(img->width/2, img->height/2);
}

static void on_mouse( int Event, int x, int y, int flags, void* ustc)
{
	if(flags & CV_EVENT_FLAG_LBUTTON)
		work(x, y);
}

static void work(int x, int y)
{
	Mat src = img;
	int width = src.cols;
	int heigh = src.rows;
	Point center(x, y);
	Mat img1(src.size(),CV_8UC3);
	src.copyTo(img1);

	int R1 = slider;
	
	for (int y=0; y<heigh; y++)
	{
		uchar *img1_p = img1.ptr<uchar>(y);
		for (int x=0; x<width; x++)
		{
			int dis = norm(Point(x,y)-center);
			if (dis<R1)
			{
				int newX = (x-center.x)*dis/R1+center.x;
				int newY = (y-center.y)*dis/R1+center.y;

				img1_p[3*x]=src.at<uchar>(newY,newX*3);
				img1_p[3*x+1]=src.at<uchar>(newY,newX*3+1);
				img1_p[3*x+2]=src.at<uchar>(newY,newX*3+2);
			}
		}
	}
	img1.copyTo(dst);
	reslut = dst;
	cvShowImage(windowName, &reslut);
	src.release();
	img1.release();
}

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
	
		size.height += 45;

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		cvSetMouseCallback( windowName, on_mouse, 0 );

		slider = (img->width + img->height) / 5;
		cvCreateTrackbar("變形量", windowName, &slider, slider * 2, onTrackbar);
		work(img->width/2, img->height/2);

		cvWaitKey(0);
		cvSaveImage(outputPath, &reslut);
		cvReleaseImage(&img);
		dst.release();
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("凸透鏡");
}//end getFIlterName