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
		//dynamic allocate memory
		unsigned char *blue, *green, *red;
		blue = new unsigned char[img->height*img->width*sizeof(unsigned char)];
		green = new unsigned char[img->height*img->width*sizeof(unsigned char)];
		red = new unsigned char[img->height*img->width*sizeof(unsigned char)];

		//load image
		for(int i = 0; i < img->height*img->width*img->nChannels;i+=img->nChannels)
		{
			blue[i/img->nChannels] = img->imageData[i];
			green[i/img->nChannels] = img->imageData[i+1];
			red[i/img->nChannels] = img->imageData[i+2];
		}//end for
		//process image
		for(int i = 0; i < img->height*img->width*img->nChannels;i+=img->nChannels)
			img->imageData[i] = img->imageData[i+1] = img->imageData[i+2] = ( blue[i/img->nChannels]+green[i/img->nChannels]+red[i/img->nChannels] )/3.0;
	
		cvSaveImage(outputPath, img);

		delete[] blue;
		delete[] green;
		delete[] red;
		cvReleaseImage(&img);
		return true;
	}
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("¦Ç¶¥ RGB°£¥H¤T");
}//end getFIlterName