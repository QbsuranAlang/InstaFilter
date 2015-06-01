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
		CvMat *img32f = cvCreateMat(img->height, img->width, CV_32FC3); 

		double k[] = {
		-1, -1, -1,
		-1,  5, -1,
		-1, -1, -1 };

		CvMat kernel = cvMat( 3, 3, CV_64FC1, k );
		cvFilter2D( img, img32f, &kernel, cvPoint( -1, -1 ) );
		cvConvertScale(img32f, img, -1/3., 0);

		cvSaveImage(outputPath, img);

		cvReleaseImage(&img);
		cvReleaseMat(&img32f);
		return true;
	}//end else

	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("°ª¤Ï®t«O¯d");
}//end getFIlterName