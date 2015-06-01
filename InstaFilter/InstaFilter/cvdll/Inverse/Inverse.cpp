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
	IplImage *img = cvLoadImage(inputPath, -1);
	if(!img)
		return false;
	else 
	{
		if(img->depth != 8)
		{
			cvReleaseImage(&img);
			img = cvLoadImage(inputPath, 1);
		}//end if

		//lookup table
		unsigned char lut[256];
		CvMat *lut_mat;
		lut_mat = cvCreateMatHeader(1, 256, CV_8UC1);
		for (int i = 0; i < 256; i++)
			lut[i] = 255 - i;
		cvSetData(lut_mat, lut, 0);

		if(img->nChannels <= 3)
		{
			//lookup table
			cvLUT(img, img, lut_mat);
		}//end if
		else if(img->nChannels == 4)
		{
			IplImage *A = cvCreateImage(cvGetSize(img), img->depth, 1);

			cvSplit(img, 0, 0, 0, A);//copy alpha channel
			cvLUT(img, img, lut_mat);//inverse
			cvMerge(0, 0, 0, A, img);

			cvReleaseImage(&A);
		}//end if
		else
		{
			cvReleaseImage(&img);
			return false;
		}//end else

		cvSaveImage(outputPath, img);
		cvReleaseImage(&img);
		cvReleaseMat(&lut_mat);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("­t¤ù");
}//end getFIlterName