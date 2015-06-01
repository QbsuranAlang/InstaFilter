#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#include <opencv2/contrib/contrib.hpp>
using namespace cv;
#define SIZE 256

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img = cvLoadImage(inputPath, 1);
	if(!img)
		return false;
	else 
	{
		Mat src = img;
		int width = src.cols;
		int heigh = src.rows;
		Mat imgColor[12];

		//rand array
		srand( (unsigned int)time(NULL) );
		int a[12] = {};
		for(int i = 0 ; i < 12 ; i++) a[i] = i;
		for(int i = 0 ; i < 12 ; i++)
		{
			int x = rand() % 12;
			int t = a[i];
			a[i] = a[x];
			a[x] = t;
		}//end for

		Mat display(heigh * 3, width * 4, CV_8UC3);
		for(int i = 0; i < 12; i++)
		{
			applyColorMap(src, imgColor[i], a[i]);
			int x = i % 4;
			int y = i / 4;
			Mat displayROI = display( Rect(x*width, y*heigh, width, heigh) );
			resize(imgColor[i], displayROI, displayROI.size());
		}//end for

		IplImage reslut = display;
		IplImage *des = &reslut;
		CvSize size = cvGetSize(des), desSize = cvGetSize(des);

		int xScreen = GetSystemMetrics(SM_CXSCREEN);
		int yScreen = GetSystemMetrics(SM_CYSCREEN);

		while(size.width + 100 > xScreen || size.height + 100 > yScreen)
		{
			size.width /= 1.3;
			size.height /= 1.3;
		}//end while
		des = cvCreateImage( size, des->depth, des->nChannels);
		cvResize(&reslut, des, CV_INTER_LINEAR);

		cvSaveImage(outputPath, des);

		//release source
		cvReleaseImage(&des);
		cvReleaseImage(&img);
		src.release();
		for(int i = 0 ; i < 12 ; i++)
			imgColor[i].release();

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("ColorMap «÷¹Ï");
}//end getFIlterName