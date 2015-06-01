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
		unsigned char max_level = 0, min_level = 255;

		for(int i = 0 ; i < img->height ; i++)
			for(int j = 0 ; j < img->widthStep ; j += img->nChannels)
			{
				int index = i * img->widthStep + j;
				unsigned char B = img->imageData[index];
				unsigned char G = img->imageData[index + 1];
				unsigned char R = img->imageData[index + 2];
				//find max and min level
				max_level = B > max_level ? B : max_level;
				min_level = B < min_level ? B : min_level;
				max_level = G > max_level ? G : max_level;
				min_level = G < min_level ? G : min_level;
				max_level = R > max_level ? R : max_level;
				min_level = R < min_level ? R : min_level;
			}//end for

		if(min_level <= 0 && max_level >= 255)
		{
			cvReleaseImage(&img);
			return false;
		}//end if

		//set silde value
		int silde = min_level;
		float stretch = 255./(max_level - min_level);

		for(int i = 0 ; i < img->height ; i++)
			for(int j = 0 ; j < img->widthStep ; j+=img->nChannels)
			{
				int index = i * img->widthStep + j;
				unsigned char B = img->imageData[index];
				unsigned char G = img->imageData[index + 1];
				unsigned char R = img->imageData[index + 2];

				img->imageData[index] = (unsigned char)((B - silde)*stretch);
				img->imageData[index+1] = (unsigned char)((G - silde)*stretch);
				img->imageData[index+2] = (unsigned char)((R - silde)*stretch);
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
	return _T("直方圖縮放");
}//end getFIlterName