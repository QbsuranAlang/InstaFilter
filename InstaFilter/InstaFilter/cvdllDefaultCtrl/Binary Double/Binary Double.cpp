#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
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
	IplImage *img = cvLoadImage(inputPath, 0);
	if(!img)
		return false;
	else 
	{
		/*
		 *           TL        TH
		 * --------------------------------------
		 * 0  black      while        black     255
		 *
		 */
		for(int i = 0 ; i < img->height ; i++)
			for(int j = 0 ; j < img->width ; j++)
			{
				int index = i * img->width + j;
				unsigned char temp = img->imageData[index];

				if(250 > temp && temp >= 100)
					img->imageData[index] = 255;
				else
					img->imageData[index] = 0;
			}//end for

		//release
		cvSaveImage(outputPath, img);
		cvReleaseImage(&img);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("二值化影像 雙門檻值");
}//end getFIlterName