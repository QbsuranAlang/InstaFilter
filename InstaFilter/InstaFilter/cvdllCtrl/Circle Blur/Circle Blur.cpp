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
static char *windowName = "Radio Blur";
static int num = 10;
static int mouseX, mouseY;
static void work(int, int);
Mat image;

static void onTrackbar(int position)
{
	num = position;
	if(num == 0)
		cvShowImage(windowName, img);
	else
	{
		mouseX = img->width / 2;
		mouseY = img->height / 2;
		work(mouseX, mouseY);
	}
}
static void on_mouse( int Event, int x, int y, int flags, void* ustc)
{
	mouseX = x;
	mouseY = y;
	if(flags & CV_EVENT_LBUTTONDOWN)
	{
		if(num == 0)
			cvShowImage(windowName, img);
		else
			work(mouseX, mouseY);
	}
}
static void work(int X, int Y)
{
	Mat src = img;
	src.copyTo(image);
	Mat src1u[3];
	split(src,src1u);

	int width = src.cols;
	int height = src.rows;

	Point center(X, Y);
	
	for (int y=0; y<height; y++)
	{
		uchar *imgP  = image.ptr<uchar>(y);
		for (int x=0; x<width; x++)
		{
			int R = norm(Point(x,y)-center);
			double angle = atan2((double)(y-center.y),(double)(x-center.x));
			int tmp0=0,tmp1=0,tmp2=0;

			for (int i=0;i<num;i++)
			{
				angle+=0.01;

				int newX = R*cos(angle) + center.x;
				int newY = R*sin(angle) + center.y;

				if(newX<0)newX=0;
				if(newX>width-1)newX=width-1;
				if(newY<0)newY=0;
				if(newY>height-1)newY=height-1;

				tmp0 += src1u[0].at<uchar>(newY,newX);
				tmp1 += src1u[1].at<uchar>(newY,newX);
				tmp2 += src1u[2].at<uchar>(newY,newX);
			}
			imgP[img->nChannels*x]=(uchar)(tmp0/num);
			imgP[img->nChannels*x+1]=(uchar)(tmp1/num);
			imgP[img->nChannels*x+2]=(uchar)(tmp2/num);
		}
	}
	reslut = image;
	cvShowImage(windowName, &reslut);
	src.release();
	src1u[2].release();
	src1u[1].release();
	src1u[0].release();
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
	
		size.height += 45;

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		int initValue = num;
		int stopValue = 40;
		cvCreateTrackbar("збн╚", windowName, &initValue, stopValue, onTrackbar);
		cvSetMouseCallback( windowName, on_mouse, 0 );

		mouseX = img->width / 2;
		mouseY = img->height / 2;
		work(mouseX, mouseY);

		reslut = image;
		cvShowImage(windowName, &reslut);
		cvWaitKey();
		if(num == 0)
			cvSaveImage(outputPath, img);
		else
			cvSaveImage(outputPath, &reslut);
		cvDestroyAllWindows();
		cvReleaseImage(&img);
		image.release();

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Circle Blur");
}//end getFIlterName