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

IplImage *image;
static char *windowName = "羽化";
Mat des;

static void onTrackbar(int position)
{
	float mSize = (1000 - position)/1000.;

	if(!mSize) mSize  += 0.001;

	Mat src = image;
	int width=src.cols;
	int heigh=src.rows;
	int centerX=width>>1;
	int centerY=heigh>>1;
	
	int maxV=centerX*centerX+centerY*centerY;
	int minV=(int)(maxV*(1-mSize));
	int diff= maxV -minV;
	float ratio = width >heigh ? (float)heigh/(float)width : (float)width/(float)heigh;
	
	Mat img;
	src.copyTo(img);

	Scalar avg=mean(src);
	Mat dst(img.size(),CV_8UC3);
	Mat mask1u[3];
	float tmp,r;
	for (int y=0;y<heigh;y++)
	{
		uchar* imgP=img.ptr<uchar>(y);
		uchar* dstP=dst.ptr<uchar>(y);
		for (int x=0;x<width;x++)
		{
			int b=imgP[3*x];
			int g=imgP[3*x+1];
			int r=imgP[3*x+2];

			float dx=centerX-x;
			float dy=centerY-y;
			
			if(width > heigh)
					dx= (dx*ratio);
			else
				dy = (dy*ratio);

			int dstSq = dx*dx + dy*dy;

			float v = ((float) dstSq / diff)*255;

			r = (int)(r +v);
			g = (int)(g +v);
			b = (int)(b +v);
			r = (r>255 ? 255 : (r<0? 0 : r));
			g = (g>255 ? 255 : (g<0? 0 : g));
			b = (b>255 ? 255 : (b<0? 0 : b));

			dstP[3*x] = (uchar)b;
			dstP[3*x+1] = (uchar)g;
			dstP[3*x+2] = (uchar)r;
		}
	}

	IplImage reslut = dst;
	dst.copyTo(des);
	cvShowImage(windowName, &reslut);

	//release
	src.release();
	img.release();
	dst.release();
	mask1u[0].release();
	mask1u[1].release();
	mask1u[2].release();
}//end onTrackbar

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
		CvSize size = cvGetSize(image); 

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
		int initValue = 250;
		cvCreateTrackbar("大小", windowName, &initValue, 1000, onTrackbar);
		onTrackbar(initValue);
		cvWaitKey(0);
			
		//release
		IplImage reslut = des;
		cvSaveImage(outputPath, &reslut);

		cvReleaseImage(&image);
		des.release();
		cvDestroyAllWindows();
		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("羽化");
}//end getFIlterName