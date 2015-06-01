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

IplImage *img, *reslut;
static char *windowName = "Color Dot";
static void work(int);

static void onTrackbar(int position)
{
	if(position > 3)
		work(position);
	else
		reslut = cvCloneImage(img);
	cvShowImage(windowName, reslut);
}//end onTrackbar

static void work(int bsize)
{
	Mat src = img;

	Mat dst = Mat::zeros(src.size(), CV_8UC3);
	Mat cir = Mat::zeros(src.size(), CV_8UC1);

	//draw circle
	for (int i = 0; i < src.rows; i += bsize)
		for (int j = 0; j < src.cols; j += bsize)
		{
			Rect rect = Rect(j, i, bsize, bsize) & Rect(0, 0, src.cols, src.rows);

			Mat sub_dst(dst, rect);
			sub_dst.setTo(mean(src(rect)));

			circle( cir, Point(j+bsize/2, i+bsize/2), bsize/2-1, CV_RGB(255,255,255), -1, CV_AA);
		}//end for

	IplImage backdround = dst, circle = cir;
	cvZero(reslut);

	cvCopy(&backdround, reslut, &circle);
	dst.release();
	cir.release();
	src.release();
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
		reslut = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);

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
		int stopValue = ((img->height+img->width) / 10.0);
		int initValue = 10;
		cvCreateTrackbar("¤j¤p", windowName, &initValue, stopValue, onTrackbar);
		onTrackbar(initValue);

		cvWaitKey(0);
		cvSaveImage(outputPath, reslut);
		cvReleaseImage(&img);
		cvReleaseImage(&reslut);
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Color Dot");
}//end getFIlterName