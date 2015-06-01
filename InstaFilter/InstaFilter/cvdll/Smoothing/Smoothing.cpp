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
		double k[] = {
			1., 1., 1.,
			1., 1., 1.,
			1., 1., 1. };

		IplImage *dst = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		CvMat *dstFloat;
		CvMat kernel = cvMat( 3, 3, CV_64FC1, k );

		//create kernel
		if(img->nChannels == 1)
			dstFloat = cvCreateMat(img->height, img->width, CV_64FC1);
		else if(img->nChannels == 3)
			dstFloat = cvCreateMat(img->height, img->width, CV_64FC3);
		else if(img->nChannels == 4)
			dstFloat = cvCreateMat(img->height, img->width, CV_64FC4);
		else
		{
			cvReleaseImage(&img);
			cvReleaseImage(&dst);
			return false;
		}//end else

		cvFilter2D( img, dstFloat, &kernel, cvPoint( -1, -1 ) );
		cvConvertScale(dstFloat, dst, 1/9., 0);

		//release
		cvSaveImage(outputPath, dst);
		cvReleaseImage(&img);
		cvReleaseImage(&dst);
		cvReleaseMat(&dstFloat);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("º“Ωk√‰Ωt");
}//end getFIlterName