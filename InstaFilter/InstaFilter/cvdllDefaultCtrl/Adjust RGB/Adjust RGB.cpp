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
		if(img->nChannels == 1)//if gray img
		{
			cvReleaseImage(&img);
			img = cvLoadImage(inputPath, 1);
		}//end if

		cv::RNG rng(cvGetTickCount());
		int randA = rng.uniform(10, 110), randB = rng.uniform(10, 110), randC = rng.uniform(10, 110);
		int randD = rng.uniform(10, 60), randE = rng.uniform(10, 60), randF = rng.uniform(10, 60);
		
		cvAddS(img, CV_RGB(randA, randB, randC), img, 0);
		cvSubS(img, CV_RGB(randD, randE, randF), img, 0);
		
		//record value
		char rgbPath[SIZE] = "";
		sprintf(rgbPath, "%s\\InstaFilter\\adjustRGB.if", getenv("temp"));
		FILE *rgb = fopen(rgbPath, "wb");
		if(!rgb) return false;
		fprintf(rgb, "%d %d %d %d %d %d", randA, randB, randC, randD, randE, randF);
		fclose(rgb);

		//release
		cvSaveImage(outputPath, img);
		cvReleaseImage(&img);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Ω’æ„RGB");
}//end getFIlterName