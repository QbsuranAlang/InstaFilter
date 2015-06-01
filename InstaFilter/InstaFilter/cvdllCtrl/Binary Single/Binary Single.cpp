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

static void onTrackbar(int position);
IplImage *img, *bin;
static char *windowName = "二值化影像";
static char *trackbarName = "門檻";
static char *trackbarInverseName = "反轉";
static int initValue = 128;
static int otsu(const IplImage *image);

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	img = cvLoadImage(inputPath, 0);
	if(!img)
		return false;
	else 
	{
		initValue = otsu(img);

		CvSize size = cvGetSize(img); 
		
		int xScreen = GetSystemMetrics(SM_CXSCREEN);
		int yScreen = GetSystemMetrics(SM_CYSCREEN);
		
		while(size.width + 100 > xScreen || size.height + 100 > yScreen)
		{
			size.width /= 1.4;
			size.height /= 1.4;
		}//end while

		size.height += 90;

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		int zeroPosition = 0;
		cvCreateTrackbar(trackbarName, windowName, &initValue, 255, onTrackbar);
		cvCreateTrackbar(trackbarInverseName, windowName, &zeroPosition, 1, onTrackbar);
		onTrackbar(0);
		cvWaitKey(0);
			
		//release
		cvSaveImage(outputPath, bin);
		cvReleaseImage(&bin);
		cvReleaseImage(&img);
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("二值化影像");
}//end getFIlterName

static void onTrackbar(int)
{
	int thres = initValue;
	if(cvGetTrackbarPos(trackbarInverseName, windowName))
		thres = 255 - initValue;

	bin = cvCloneImage(img);

	//cvThreshold(img, bin, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	cvThreshold(img, bin, thres, 255, CV_THRESH_BINARY);
	cvShowImage(windowName, bin);

}//end onTrackbar

int otsu(const IplImage *image)
{
	assert(NULL != image);

	int width = image->width;
	int height = image->height;
	int x=0,y=0;
	int pixelCount[256];
	float pixelPro[256];
	int i, j, pixelSum = width * height, threshold = 0;

	uchar* data = (uchar*)image->imageData;

	//初始化
	for(i = 0; i < 256; i++)
	{
		pixelCount[i] = 0;
		pixelPro[i] = 0;
	}

	//统计灰度级中每个像素在整幅图像中的个数
	for(i = y; i < height; i++)
	{
		for(j = x;j <width;j++)
		{
			pixelCount[data[i * image->widthStep + j]]++;
		}
	}

	//计算每个像素在整幅图像中的比例
	for(i = 0; i < 256; i++)
	{
		pixelPro[i] = (float)(pixelCount[i]) / (float)(pixelSum);
	}

	//经典ostu算法,得到前景和背景的分割
	//遍历灰度级[0,255],计算出方差最大的灰度值,为最佳阈值
	float w0, w1, u0tmp, u1tmp, u0, u1, u,deltaTmp, deltaMax = 0;
	for(i = 0; i < 256; i++)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;

		for(j = 0; j < 256; j++)
		{
			if(j <= i) //背景部分
			{
				//以i为阈值分类，第一类总的概率
				w0 += pixelPro[j];		
				u0tmp += j * pixelPro[j];
			}
			else       //前景部分
			{
				//以i为阈值分类，第二类总的概率
				w1 += pixelPro[j];		
				u1tmp += j * pixelPro[j];
			}
		}

		u0 = u0tmp / w0;		//第一类的平均灰度
		u1 = u1tmp / w1;		//第二类的平均灰度
		u = u0tmp + u1tmp;		//整幅图像的平均灰度
		//计算类间方差
		deltaTmp = w0 * (u0 - u)*(u0 - u) + w1 * (u1 - u)*(u1 - u);
		//找出最大类间方差以及对应的阈值
		if(deltaTmp > deltaMax)
		{	
			deltaMax = deltaTmp;
			threshold = i;
		}
	}
	//返回最佳阈值;
	return threshold;
}//end otsu