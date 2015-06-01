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
		Mat img0(src.size(),CV_8UC3);
		for (int y=1; y<src.rows-1; y++)
		{
			uchar *p0 = src.ptr<uchar>(y);
			uchar *p1 = src.ptr<uchar>(y+1);

			uchar *q0 = img0.ptr<uchar>(y);
			for (int x=1; x<src.cols-1; x++)
			{
				for (int i=0; i<3; i++)
				{
					int tmp0 = p1[3*(x+1)+i]-p0[3*(x-1)+i]+128;
					if (tmp0<0)
						q0[3*x+i]=0;
					else if(tmp0>255)
						q0[3*x+i]=255;
					else
						q0[3*x+i]=tmp0;
				}
			}
		}
		
		IplImage reslut = img0;
		cvSaveImage(outputPath, &reslut);
		img0.release();
		src.release();
		cvReleaseImage(&img);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("¯BÀJ");
}//end getFIlterName