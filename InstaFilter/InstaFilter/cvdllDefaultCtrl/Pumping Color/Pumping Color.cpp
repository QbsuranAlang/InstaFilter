#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#include <opencv2/imgproc/imgproc.hpp>
#define SIZE 256

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

void RGBtoH(unsigned char R, unsigned char G, unsigned char B, int &h)
{
	double r = R / 255.;
	double g = G / 255.;
	double b = B / 255.;

	// RGB 轉 H 公式
	if (r >= g && g>= b)
		h = 60 * (g-b)/(r-b);
	else if (g > r && r >= b)
		h = 60 * (2-((r-b)/(g-b)));
	else if (g >= b && b > r)
		h = 60 * (2+ ((b-r)/(g-r)));
	else if (b >g && g>r)
		h = 60 * (4 - (g-r)/(b-r));
	else if (b>r && r>=g)
		h = 60 * (4 + (r-g)/(b-g));
	else if (r>=b && b>g)
		h = 60 * (6-(b-g)/(r-g));
	else
		h = 0;

	if( h < 0 )
		h += 360;
	else
		h %= 360;
}//end RGBtoH

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
		if(img->nChannels == 1)
		{
			cvReleaseImage(&img);
			return false;
		}//end if
		else if(img->nChannels == 4 || img->depth != 8)
		{
			cvReleaseImage(&img);
			img = cvLoadImage(inputPath, 1);
		}//end else

		for(int i = 0 ; i < img->height ; i++)
		for(int j = 0 ; j < img->widthStep ; j+=img->nChannels)
		{
			int index = i * img->widthStep + j;
			unsigned char B = img->imageData[index];
			unsigned char G = img->imageData[index + 1];
			unsigned char R = img->imageData[index + 2];

			int h;
			RGBtoH(R, G, B, h);

			cv::RNG rng(cvGetTickCount());
			if(h  >= 180 && h <= 230)
			{
				unsigned char gray = (unsigned char)(.299*R + .587*G + .114*B);
				img->imageData[index] = img->imageData[index + 1] = img->imageData[index + 2 ] = gray;
			}//end if
		}//end for

		cvSaveImage(outputPath, img);
		cvReleaseImage(&img);
		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("抽色");
}//end getFIlterName