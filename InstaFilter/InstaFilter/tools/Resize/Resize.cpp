#include <string.h>
#include <Windows.h>
#include <wchar.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#define SIZE 256
#define TMP_IMAGE_MAX 220

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvResize(LPWSTR csInputPath, LPWSTR csOutputPath);
}//end extern "C"

bool _stdcall opencvResize(LPWSTR csInputPath, LPWSTR csOutputPath)
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
		CvSize size = cvGetSize(img);
		while(size.width > TMP_IMAGE_MAX || size.height > TMP_IMAGE_MAX)
		{
			size.width /= 1.1;
			size.height /= 1.1;
		}//end while

		//重新製作圖檔
		IplImage *temp = cvCloneImage(img);
		cvReleaseImage(&img);
		img = cvCreateImage( size, temp->depth, temp->nChannels);
		cvResize(temp, img, CV_INTER_LINEAR); //等比例縮小影像
	
		//release
		cvSaveImage(outputPath, img);
		cvReleaseImage(&img);
		cvReleaseImage(&temp);

		return true;
	}//end else
	return false;
}//end opencvResize