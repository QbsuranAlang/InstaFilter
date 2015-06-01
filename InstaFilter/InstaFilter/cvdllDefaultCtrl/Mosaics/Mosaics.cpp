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
		srand(unsigned int(time(NULL)));
		CvPoint p0 = cvPoint(rand() % img->width, rand() % img->height);
		//too close end
		if(p0.x > img->width - 50) p0.x -= rand() % 100;
		if(p0.y > img->height - 50) p0.y -= rand() % 100;
		//out of range then adjust
		if(p0.x < 0) p0.x = 0;
		if(p0.y < 0) p0.y = 0;

		CvPoint p1 = cvPoint(p0.x + 100, p0.y + 100);
		//out of range then adjust
		if(p1.x > img->width) p1.x = img->width;
		if(p1.y > img->height) p1.y = img->height;

		int wh = rand() % 10 + 5;
		for(int i = 1 ; i <= wh ; i++)
			for(int j = 1 ; j <= wh; j++)
			{
				int w = (p1.x-p0.x)/wh;
				int h = (p1.y-p0.y)/wh;
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
	return _T("自訂馬賽克區域");
}//end getFIlterName