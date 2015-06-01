#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#include <opencv2/imgproc/imgproc.hpp>
#define SIZE 256
using namespace cv;

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
	IplImage *img = cvLoadImage(inputPath, -1);
	if(!img)
		return false;
	else 
	{
		RNG rng(cvGetTickCount());
		int num = rng.uniform(10, 50);
		for(int i = 0 ; i < (img->height*img->widthStep)/255 * num ; i++)
		{
			int x = rng.uniform(0, img->height-1);
			int y = rng.uniform(0, img->widthStep-1);
			int index = x * img->widthStep + y;
			img->imageData[index] = rng.uniform(0, 255);
			img->imageData[index+1] = rng.uniform(0, 255);
			img->imageData[index+2] = rng.uniform(0, 255);
		}//end for

		cvSaveImage(outputPath, img);
		cvReleaseImage(&img);

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("¼W¥[Âø°T");
}//end getFIlterName