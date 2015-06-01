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

		Mat dst = Mat::zeros(src.size(), CV_8UC3);
		Mat cir = Mat::zeros(src.size(), CV_8UC1);
		int bsize = 10;

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
		IplImage *reslut = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);

		cvCopy(&backdround, reslut, &circle);

		cvSaveImage(outputPath, reslut);
		src.release();
		dst.release();
		cir.release();
		cvReleaseImage(&reslut);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Color Dot");
}//end getFIlterName