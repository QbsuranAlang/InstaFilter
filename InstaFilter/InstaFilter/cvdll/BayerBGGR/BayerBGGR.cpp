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
	IplImage *img = cvLoadImage(inputPath, 1);
	if(!img)
		return false;
	else 
	{
		IplImage *srcB, *srcG, *srcR, *bayer;
		srcB = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		srcG = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		srcR = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		bayer = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);//bayer image
		cvSplit(img, srcR, srcG, srcB, NULL);//split all channel

		// BG   <=fliter format 
		// GR 
		for (int i = 0 ; i < bayer->height ; i++)//row
			for (int j = 0 ; j < bayer->width ; j++)//column
			{
				int index = i * bayer->width + j;
				if (i % 2 == 0)//even row
					if (j % 2 == 0)//even column
						bayer->imageData[index] = srcB->imageData[index];
					else//odd column
						bayer->imageData[index] = srcG->imageData[index];
				else//odd row
					if (j % 2 == 0)//even column
						bayer->imageData[index] = srcG->imageData[index];
					else//odd column
						bayer->imageData[index] = srcR->imageData[index];
			}//end for

		//release
		cvSaveImage(outputPath, bayer);
		cvReleaseImage(&img);
		cvReleaseImage(&bayer);
		cvReleaseImage(&srcR);
		cvReleaseImage(&srcG);
		cvReleaseImage(&srcB);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("BayerBGGR");
}//end getFIlterName