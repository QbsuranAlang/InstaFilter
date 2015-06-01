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

IplImage *img, *dst;
static char *windowName = "Sobel";
static char *ctrlPanel = "控制面板";
int isColor = 0, isY = 0, aSize = 3;

void onTrackbar(int)
{
	if(!(aSize & 1)) aSize++;

	if(isColor)
	{
		dst = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
		//create BGR layer and splitt
		IplImage *B = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		IplImage *G = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		IplImage *R = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		IplImage *B16s = cvCreateImage(cvGetSize(img), IPL_DEPTH_16S, 1);
		IplImage *G16s = cvCreateImage(cvGetSize(img), IPL_DEPTH_16S, 1);
		IplImage *R16s = cvCreateImage(cvGetSize(img), IPL_DEPTH_16S, 1);
		cvSplit(img, B, G, R, 0);

		//sobel
		cvSobel(B, B16s, isY, 1 - isY, aSize);
		cvSobel(G, G16s, isY, 1 - isY, aSize);
		cvSobel(R, R16s, isY, 1 - isY, aSize);
		cvConvertScaleAbs(B16s, B, 1, 0);
		cvConvertScaleAbs(G16s, G, 1, 0);
		cvConvertScaleAbs(R16s, R, 1, 0);

		cvMerge(B, G, R, 0, dst);

		cvReleaseImage(&B);
		cvReleaseImage(&G);
		cvReleaseImage(&R);
		cvReleaseImage(&B16s);
		cvReleaseImage(&G16s);
		cvReleaseImage(&R16s);
	}//end if
	else
	{
		dst = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		IplImage *gray = cvCreateImage(cvGetSize(img), img->depth, 1);
		IplImage *img16s = cvCreateImage(cvGetSize(img), IPL_DEPTH_16S, 1);
		cvCvtColor(img, gray, CV_BGR2GRAY);

		//sobel
		cvSobel(gray, img16s, isY, 1 - isY, aSize);
		cvConvertScaleAbs(img16s, dst, 1, 0);

		cvReleaseImage(&gray);
		cvReleaseImage(&img16s);
	}//end else

	cvShowImage(windowName, dst);
}

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	img = cvLoadImage(inputPath, 1);
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

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 );

		CvSize panelSize = cvSize(600, 135);
		cvNamedWindow(ctrlPanel, 1);
		cvResizeWindow(ctrlPanel, panelSize.width, panelSize.height);
		cvMoveWindow(ctrlPanel, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		cvCreateTrackbar("黑白/彩色", ctrlPanel, &isColor, 1, onTrackbar);
		cvCreateTrackbar("水平/垂直", ctrlPanel, &isY, 1, onTrackbar);
		cvCreateTrackbar("大小", ctrlPanel, &aSize, 7, onTrackbar);
		cvShowImage(ctrlPanel, NULL);

		onTrackbar(0);
		cvWaitKey(0);

		//release
		cvSaveImage(outputPath, dst);
		cvReleaseImage(&dst);
		cvReleaseImage(&img);
		cvDestroyAllWindows();
		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Sobel");
}//end getFIlterName