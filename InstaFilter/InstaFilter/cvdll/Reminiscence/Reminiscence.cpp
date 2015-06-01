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
		for(int i = 0 ; i < img->height ; i++)
			for(int j = 0 ; j < img->widthStep ; j+=img->nChannels)
			{
				int index = i * img->widthStep + j;
				unsigned char B = img->imageData[index];
				unsigned char G = img->imageData[index + 1];
				unsigned char R = img->imageData[index + 2];

				double newB = .272 * R + .534 * G + .131 * B;
				double newG = .349 * R + .686 * G + .168 * B;
				double newR = .393 * R + .769 * G + .189 * B;

				if(newB < 0) newB = 0; else if(newB > 255) newB = 255;
				if(newG < 0) newG = 0; else if(newG > 255) newG = 255;
				if(newR < 0) newR = 0; else if(newR > 255) newR = 255;

				img->imageData[index] =  (unsigned char)newB; //B
				img->imageData[index + 1] = (unsigned char)newG; //G
				img->imageData[index + 2] = (unsigned char)newR; //R
			}
		cvSaveImage(outputPath, img);
		cvReleaseImage(&img);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("ÃhÂÂ");
}//end getFIlterName