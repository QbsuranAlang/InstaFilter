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
		Mat img1(src.size(),CV_8UC3);
		for (int y=1; y<src.rows-1; y++)
		{
			uchar *p0 = src.ptr<uchar>(y);
			uchar *p1 = src.ptr<uchar>(y+1);

			uchar *q1 = img1.ptr<uchar>(y);
			for (int x=1; x<src.cols-1; x++)
			{
				for (int i=0; i<3; i++)
				{
					int tmp1 = p0[3*(x-1)+i]-p1[3*(x+1)+i]+128;
					if (tmp1<0)
						q1[3*x+i]=0;
					else if(tmp1>255)
						q1[3*x+i]=255;
					else
						q1[3*x+i]=tmp1;
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
	return _T("ÀJ¨è");
}//end getFIlterName