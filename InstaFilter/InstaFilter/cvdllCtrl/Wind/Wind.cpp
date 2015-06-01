#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
using namespace cv;
#define SIZE 256

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

static int D = 10;//d
static int length = 20;//length
IplImage *img, reslut;
Mat image;
static char *windowName = "風";
static char *trackbarInverseName = "反轉";
static char *ctrlPanel = "控制面板";

static void work(int)
{
	Mat src = img;
	Mat src1u[3];
	split(src, src1u);
	int width = img->width;
	int height = img->height;
	src.copyTo(image);
	if(D != 0 && length != 0)
	{
		Point center(width / 2, height / 2);
		RNG rng;
		for (int y = 0 ; y < height ; y++)
		{
			uchar *imageP  = image.ptr<uchar>(y);
			for (int i = 0 ; i < D ; i++)
			{
				int newX = rng.uniform(i * width / D, (i+1) * width / D);
				int newY = y;

				if(newX < 0)newX = 0;
				if(newX > width - 1)newX = width - 1;

				uchar tmp0 = src1u[0].at<uchar>(newY,newX);
				uchar tmp1 = src1u[1].at<uchar>(newY,newX);
				uchar tmp2 = src1u[2].at<uchar>(newY,newX);

				bool direct = true;
				if(cvGetTrackbarPos(trackbarInverseName, ctrlPanel))
				direct = false;
				for (int j = 0; j < length; j++)
				{
					int tmpX;
					if(direct)
						tmpX = newX + j;//sub : wind to right, add : wind to left
					else
						tmpX = newX - j;

					if(tmpX < 0)tmpX = 0;
					if(tmpX > width - 1)tmpX = width - 1;
					
					imageP[tmpX*img->nChannels] = tmp0;
					imageP[tmpX*img->nChannels+1] = tmp1;
					imageP[tmpX*img->nChannels+2] = tmp2;
				}
			}
		}
	}//end if

	reslut = image;
	cvShowImage(windowName, &reslut);
	src.release();
	src1u[0].release();
	src1u[1].release();
	src1u[2].release();
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
		//Show window, then create trackbar
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
		cvCreateTrackbar( "密度", ctrlPanel, &D, img->height / 10, work);
		cvCreateTrackbar( "長度", ctrlPanel, &length, img->width / 10, work);
		int zeroPosition = 0;
		cvCreateTrackbar( trackbarInverseName, ctrlPanel, &zeroPosition, 1, work);
		work(0);
		
		cvWaitKey();
		cvSaveImage(outputPath, &reslut);

		cvDestroyAllWindows();
		image.release();
		cvReleaseImage(&img);

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("風");
}//end getFIlterName