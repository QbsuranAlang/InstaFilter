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
		int width = src.cols;
		int heigh = src.rows;
		Point center(width/2,heigh/2);
		Mat img1(src.size(),CV_8UC3);
		src.copyTo(img1);

		int R1 = sqrtf(width*width+heigh*heigh)/2;
	
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
		
		IplImage reslut = img1;
		cvSaveImage(outputPath, &reslut);
		img1.release();
		src.release();
		cvReleaseImage(&img);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("凸透鏡");
}//end getFIlterName