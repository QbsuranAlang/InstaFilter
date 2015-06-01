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
	else if (img->nChannels >= 3) 
	{
		IplImage *reconstruction;
		if(img->nChannels == 3)
		{
			reconstruction = cvCreateImage( cvGetSize(img), img->depth, 3);
			cvCvtColor(img, reconstruction, CV_RGB2BGR);//inbluit function
		}//end 3 channel
		else if(img->nChannels == 4)
		{
			reconstruction = cvCreateImage( cvGetSize(img), img->depth, 4);
			cvCvtColor(img, reconstruction, CV_RGBA2BGRA);//inbluit function
		}//end 4 channel
		else return false;

		//release
		cvSaveImage(outputPath, reconstruction);
		cvReleaseImage(&reconstruction);
		cvReleaseImage(&img);

		return true;
	}//end else

	cvReleaseImage(&img);
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("¥æ´«ÂÅ¬õÀW¹D");
}//end getFIlterName