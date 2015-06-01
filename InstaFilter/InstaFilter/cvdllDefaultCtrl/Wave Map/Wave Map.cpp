#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#define SIZE 256
using namespace cv;

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

double angle;
int deltaI=10;	
int A=10;		
Mat src, img;
IplImage reslut, *image;

static void onTrackbar(int position)
{
	int width=src.cols;
	int heigh=src.rows;
	angle = 0.0;
	
	for (int y=0; y<heigh; y++)
	{
		int changeX = A*sin(angle);
		uchar *srcP = src.ptr<uchar>(y);
		uchar *imgP = img.ptr<uchar>(y);
		for (int x=0; x<width; x++)
		{
			if(changeX+x<width && changeX+x>0)		//sin（-1,1）
			{
				imgP[image->nChannels*x]=srcP[image->nChannels*(x+changeX)];
				imgP[image->nChannels*x+1]=srcP[image->nChannels*(x+changeX)+1];
				imgP[image->nChannels*x+2]=srcP[image->nChannels*(x+changeX)+2];
			}
			
			else if(x<=changeX)       
			{
				imgP[image->nChannels*x]=srcP[0];
				imgP[image->nChannels*x+1]=srcP[1];
				imgP[image->nChannels*x+2]=srcP[2];
			}
			else if (x>=width-changeX)
			{
				imgP[image->nChannels*x]=srcP[image->nChannels*(width-1)];
				imgP[image->nChannels*x+1]=srcP[image->nChannels*(width-1)+1];
				imgP[image->nChannels*x+2]=srcP[image->nChannels*(width-1)+2];
			}
		}
		angle += ((double)deltaI)/100;
	}
	reslut = img;
}

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	image = cvLoadImage(inputPath, -1);
	if(!image)
		return false;
	else 
	{
		src = image;

		src.copyTo(img);
		onTrackbar(0);
			
		//release
		cvSaveImage(outputPath, &reslut);
		src.release();
		img.release();
		cvReleaseImage(&image);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("波浪");
}//end getFIlterName