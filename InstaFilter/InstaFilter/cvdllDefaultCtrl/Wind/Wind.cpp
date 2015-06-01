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
		int D = 10;//d
		int length = 20;//length

		Mat src = img;
		Mat src1u[3];
		split(src, src1u);
		int width = img->width;
		int height = img->height;

		Point center(width / 2, height / 2);
		RNG rng;
		for (int y = 0 ; y < height ; y++)
		{
			uchar *imageP  = src.ptr<uchar>(y);
			for (int i = 0 ; i < D ; i++)
			{
				int newX = rng.uniform(i * width / D, (i+1) * width / D);
				int newY = y;

				if(newX < 0)newX = 0;
				if(newX > width - 1)newX = width - 1;

				uchar tmp0 = src1u[0].at<uchar>(newY,newX);
				uchar tmp1 = src1u[1].at<uchar>(newY,newX);
				uchar tmp2 = src1u[2].at<uchar>(newY,newX);

				for (int j = 0; j < length; j++)
				{
					int tmpX = newX - j;//sub : wind to right, add : wind to left

					if(tmpX < 0)tmpX = 0;
					if(tmpX > width - 1)tmpX = width - 1;
					
					imageP[tmpX*img->nChannels] = tmp0;
					imageP[tmpX*img->nChannels+1] = tmp1;
					imageP[tmpX*img->nChannels+2] = tmp2;
				}
			}
		}
		IplImage reslut = src;

		cvSaveImage(outputPath, &reslut);

		src.release();
		src1u[0].release();
		src1u[1].release();
		src1u[2].release();
		cvReleaseImage(&img);

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("­·");
}//end getFIlterName