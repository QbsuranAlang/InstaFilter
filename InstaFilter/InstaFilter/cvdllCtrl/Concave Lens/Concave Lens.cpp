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
static char *windowName = "凹透鏡";
static int slider, stopValue;
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
	Mat img2(src.size(),CV_8UC3);
	src.copyTo(img2);

	int R1 = slider / (stopValue/40);
	
	for (int y=0; y<heigh; y++)
		{
			uchar *img2_p = img2.ptr<uchar>(y);
			for (int x=0; x<width; x++)
			{
				double theta = atan2((double)(y-center.y),(double)(x-center.x));

				int R2 = sqrtf(norm(Point(x,y)-center))*R1;
			
				int newX = center.x+(int)(R2*cos(theta));

				int newY = center.y+(int)(R2*sin(theta));

				if(newX<0) newX=0;
				else if(newX>=width) newX=width-1;
				if(newY<0) newY=0;
				else if(newY>=heigh) newY=heigh-1;
					

				img2_p[3*x]=src.at<uchar>(newY,newX*3);
				img2_p[3*x+1]=src.at<uchar>(newY,newX*3+1);
				img2_p[3*x+2]=src.at<uchar>(newY,newX*3+2);
			}
		}

	img2.copyTo(dst);
	reslut = dst;
	cvShowImage(windowName, &reslut);
	src.release();
	img2.release();
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
	
		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		cvSetMouseCallback( windowName, on_mouse, 0 );
		
		size.height += 45;

		slider = (img->width + img->height) / 5;
		stopValue = slider * 2;
		cvCreateTrackbar("變形量", windowName, &slider, stopValue, onTrackbar);
		work(img->width/2, img->height/2);

		cvWaitKey();
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
	return _T("凹透鏡");
}//end getFIlterName