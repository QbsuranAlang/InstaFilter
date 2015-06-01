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

static int HW = 5;
static char *windowName = "«÷¹Ï";
IplImage *img, *des;

static void onTrackbar(int)
{
	CvPoint p0 = cvPoint(0, 0);
	CvPoint p1 = cvPoint(img->width, img->height);

	//dynamic alloc
	int *a = new int[HW*HW];
	for(int i = 0 ; i < HW*HW ; i++)
		a[i] = i;

	cv::RNG rng(cvGetTickCount());
	//rand array
	for(int i = 0 ; i < HW*HW ; i++)
	{
		int index = rng.uniform(0, HW*HW);
		int temp = a[index];
		a[index] = a[i];
		a[i] = temp;
	}

	for(int i = 0 ; i < HW ; i++)
		for(int j = 0 ; j < HW; j++)
		{
			int w = (p1.x-p0.x)/HW + 1; //+1 float error corrected
			int h = (p1.y-p0.y)/HW + 1;
			int X = p0.x + w*(a[i*HW+j]%HW);
			int Y = p0.y + h*(a[i*HW+j]/HW);

			cvSetImageROI(des, cvRect(X, Y, w, h)); //rand position
			cvSetImageROI(img, cvRect(p0.x + w*i, p0.y + h*j, w, h));//step by step postion
			cvResize(img, des, CV_INTER_LINEAR);
			cvResetImageROI(des);
			cvResetImageROI(img);
		}
	cvShowImage(windowName, des);

	delete[] a;
}//end work

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
		cvCreateTrackbar("¼e°ª", windowName, &HW, 20, onTrackbar);
		
		des = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
		onTrackbar(0);

		cvShowImage(windowName, des);
		cvWaitKey();
		cvSaveImage(outputPath, des);
		cvDestroyAllWindows();
		cvReleaseImage(&img);
		cvReleaseImage(&des);

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("«÷¹Ï");
}//end getFIlterName