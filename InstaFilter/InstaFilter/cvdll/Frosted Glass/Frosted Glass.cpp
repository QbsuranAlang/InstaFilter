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
		RNG rng(cvGetTickCount());
		Mat image(src.size(), CV_8UC3);
		for (int y = 1; y < heigh-1; y++)
		{
			uchar *P0  = src.ptr<uchar>(y);
			uchar *P1  = image.ptr<uchar>(y);
			for (int x = 1; x < width-1; x++)
			{
				int tmp = rng.uniform(0, 9);
				P1[img->nChannels * x]=src.at<uchar>(y-1 + tmp / img->nChannels, img->nChannels * (x-1+tmp % img->nChannels));
				P1[img->nChannels * x + 1]=src.at<uchar>(y-1 + tmp / img->nChannels, img->nChannels * (x-1+tmp % img->nChannels)+1);
				P1[img->nChannels * x + 2]=src.at<uchar>(y-1 + tmp / img->nChannels, img->nChannels * (x-1+tmp % img->nChannels)+2);
			}
		}
		IplImage reslut = image;
		cvSaveImage(outputPath, &reslut);
		image.release();
		src.release();
		cvReleaseImage(&img);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("¤ò¬Á¼þ");
}//end getFIlterName