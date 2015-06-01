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

IplImage *img, reslut;
static char *windowName = "¼Ò½k";
Mat src, dst;

static void onTrackbar(int position)
{
	if(position != 0)
		blur( src, dst, Size( position, position), Point(-1,-1) );
	else
		src.copyTo(dst);
	reslut = dst;
	cvShowImage(windowName, &reslut);
}//end onTrackbar

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	img = cvLoadImage(inputPath, -1);
	if(!img)
		return false;
	else 
	{
		src = img;

		CvSize size = cvGetSize(img); 

		int xScreen = GetSystemMetrics(SM_CXSCREEN);
		int yScreen = GetSystemMetrics(SM_CYSCREEN);
		
		while(size.width + 100 > xScreen || size.height + 100 > yScreen)
		{
			size.width /= 1.4;
			size.height /= 1.4;
		}//end while
	
		size.height += 45;

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		int initValue = 11;
		int MAX = img->width > img->height ? img->width : img->height;
		cvCreateTrackbar("¤j¤p", windowName, &initValue, MAX / 3, onTrackbar);
		onTrackbar(initValue);
		cvWaitKey(0);
			
		//release
		cvSaveImage(outputPath, &reslut);
		dst.release();
		src.release();
		cvReleaseImage(&img);
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("¼Ò½k");
}//end getFIlterName