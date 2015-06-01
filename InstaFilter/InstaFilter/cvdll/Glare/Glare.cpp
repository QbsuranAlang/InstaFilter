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
	IplImage *image = cvLoadImage(inputPath, 1);
	if(!image)
		return false;
	else  
	{
		Mat src = image;
		int width = src.cols;
		int heigh = src.rows;
		Mat img;
		src.copyTo(img);

		Mat dst(img.size(),CV_8UC3);
		Mat dst1u[3];

		float tmp, r;
		for (int y = 0;y < heigh ; y++)
		{
			uchar* imgP = img.ptr<uchar>(y);
			uchar* dstP = dst.ptr<uchar>(y);
			for (int x = 0;x < width ; x++)
			{
				r = (float)imgP[3*x];
				if(r>127.5)
					tmp = r+(255-r)*(r-127.5)/127.5;
				else
					tmp = r*r/127.5;
				tmp=tmp>255?255:tmp;
				tmp=tmp<0?0:tmp;
				dstP[3*x]=(uchar)(tmp);

				r = (float)imgP[3*x+1];
				if(r>127.5)
					tmp = r+(255-r)*(r-127.5)/127.5;
				else
					tmp = r*r/127.5;
				tmp=tmp>255?255:tmp;
				tmp=tmp<0?0:tmp;
				dstP[3*x+1]=(uchar)(tmp);

				r = (float)imgP[3*x+2];
				if(r>127.5)
					tmp = r+(255-r)*(r-127.5)/127.5;
				else
					tmp = r*r/127.5;
				tmp=tmp>255?255:tmp;
				tmp=tmp<0?0:tmp;
				dstP[3*x+2]=(uchar)(tmp);
			}
		}
		
		IplImage reslut = dst;
		cvSaveImage(outputPath, &reslut);

		src.release();
		img.release();
		dst.release();
		dst1u[0].release();
		dst1u[1].release();
		dst1u[2].release();
		cvReleaseImage(&image);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("±j¥ú");
}//end getFIlterName