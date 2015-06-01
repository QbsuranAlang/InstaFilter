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
		int width=src.cols;
		int heigh=src.rows;
		Mat gray0,gray1;
		//convert to gray
		cvtColor(src,gray0,CV_BGR2GRAY);
		//inverse
		addWeighted(gray0, -1, NULL, 0, 255, gray1);
		//GaussianBlur
		GaussianBlur(gray1, gray1, Size(11, 11), 0);

		//conbine
		Mat image(gray1.size(),CV_8UC1);
		for (int y=0; y<heigh; y++)
		{
			uchar* P0  = gray0.ptr<uchar>(y);
			uchar* P1  = gray1.ptr<uchar>(y);
			uchar* P  = image.ptr<uchar>(y);
			for (int x=0; x<width; x++)
			{
				int tmp0=P0[x];
				int tmp1=P1[x];
				P[x] =(uchar) min((tmp0+(tmp0*tmp1)/(256-tmp1)),255);
			}
		}

		IplImage reslut = image;
		cvSaveImage(outputPath, &reslut);
		image.release();
		gray0.release();
		gray1.release();
		cvReleaseImage(&img);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("¯À´y");
}//end getFIlterName