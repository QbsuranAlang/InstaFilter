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
		CvPoint p0 = cvPoint(0, 0);
		CvPoint p1 = cvPoint(img->width, img->height);
		srand((unsigned int)time(NULL));
		int W = rand() % (img->width/10) + 2;
		int H = W;

		for(int i = 1 ; i <= W ; i++)
			for(int j = 1 ; j <= H; j++)
			{
				int w = (p1.x-p0.x)/W;
				int h = (p1.y-p0.y)/H;
				int X = p0.x + w*(i-1);
				int Y = p0.y + h*(j-1);
				cvSetImageROI(img, cvRect(X, Y, w, h));
				CvScalar mean = cvAvg(img);
				cvSet(img, mean);
				cvResetImageROI(img);
			}

		cvSaveImage(outputPath, img);
		cvReleaseImage(&img);

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("°¨ÁÉ§J");
}//end getFIlterName