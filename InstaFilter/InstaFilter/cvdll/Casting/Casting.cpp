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
	else if(img->nChannels != 1)
	{
		for(int i = 0 ; i < img->height ; i++)
			for(int j = 0 ; j < img->widthStep ; j+=img->nChannels)
			{
				int index = i * img->widthStep + j;
				unsigned char B = img->imageData[index];
				unsigned char G = img->imageData[index + 1];
				unsigned char R = img->imageData[index + 2];

				double newB = B * 128. / (G + R + 1);
				double newG = G * 128. / (R + B + 1);
				double newR = R * 128. / (G + B + 1);

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

	cvReleaseImage(&img);
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("º²Å±");
}//end getFIlterName