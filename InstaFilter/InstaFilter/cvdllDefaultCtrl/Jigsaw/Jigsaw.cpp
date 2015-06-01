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
		IplImage *des = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		CvPoint p0 = cvPoint(0, 0);
		CvPoint p1 = cvPoint(img->width, img->height);

		cv::RNG rng(cvGetTickCount());
		int HW = rng.uniform(3, 5);

		//dynamic alloc
		int *a = new int[HW*HW];
		for(int i = 0 ; i < HW*HW ; i++)
			a[i] = i;

		//rand array
		for(int i = 0 ; i < HW*HW ; i++)
		{
			int index = rand() % HW*HW;
			int temp = a[index];
			a[index] = a[i];
			a[i] = temp;
		}

		for(int i = 0 ; i < HW ; i++)
			for(int j = 0 ; j < HW; j++)
			{
				int w = (p1.x-p0.x)/HW + 1;
				int h = (p1.y-p0.y)/HW + 1;
				int X = p0.x + w*(a[i*HW+j]%HW);
				int Y = p0.y + h*(a[i*HW+j]/HW);

				cvSetImageROI(des, cvRect(X, Y, w, h)); //rand position
				cvSetImageROI(img, cvRect(p0.x + w*i, p0.y + h*j, w, h));//step by step postion
				cvResize(img, des, CV_INTER_LINEAR);
				cvResetImageROI(des);
				cvResetImageROI(img);
			}

		cvSaveImage(outputPath, des);
		cvReleaseImage(&img);
		cvReleaseImage(&des);

		delete[] a;
		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("«÷¹Ï");
}//end getFIlterName