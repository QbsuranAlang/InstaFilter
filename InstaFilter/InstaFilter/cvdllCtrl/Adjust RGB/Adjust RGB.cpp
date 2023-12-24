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

IplImage *img, *des;
static char *windowName = "�վ�RGB";
static char *ctrlPanel1 = "����O �W�[";
static char *ctrlPanel2 = "����O ���";

static void work(int)
{
	int r, b, g, subR, subB, subG;
	r = cvGetTrackbarPos("�W�[��", ctrlPanel1);
	b = cvGetTrackbarPos("�W�[��", ctrlPanel1);
	g = cvGetTrackbarPos("�W�[��", ctrlPanel1);
	subR = cvGetTrackbarPos("��֬�", ctrlPanel2);
	subB = cvGetTrackbarPos("�����", ctrlPanel2);
	subG = cvGetTrackbarPos("��ֺ�", ctrlPanel2);

	des = cvCloneImage(img);
	cvAddS(img, CV_RGB(r, g, b), des, 0);
	cvSubS(des, CV_RGB(subR, subG, subB), des, 0);
	cvShowImage(windowName, des);
}

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
		if(img->nChannels == 1)//if gray img
		{
			cvReleaseImage(&img);
			img = cvLoadImage(inputPath, 1);
		}//end if

		//read color from file
		char rgbPath[SIZE] = "";
		sprintf(rgbPath, "%s\\InstaFilter\\adjustRGB.if", getenv("temp"));
		FILE *rgb = fopen(rgbPath, "rb");
		if(!rgb) return false;
		//read
		int randValue[6];
		char data[SIZE];
		fgets(data, SIZE, rgb);
		char *token = strtok(data, " ");
		for(int i = 0 ; i < sizeof(randValue)/sizeof(*randValue) && token ; i++)
		{
			randValue[i] = atoi(token);
			token = strtok(NULL, " ");
		}//end for
		fclose(rgb);
		//get color

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
		cvNamedWindow(ctrlPanel1, 1);
		cvNamedWindow(ctrlPanel2, 1);
		cvResizeWindow(ctrlPanel1, panelSize.width, panelSize.height);
		cvResizeWindow(ctrlPanel2, panelSize.width, panelSize.height);
		cvMoveWindow(ctrlPanel1, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		cvMoveWindow(ctrlPanel2, (xScreen-size.width)/2 + 100, (yScreen-size.height)/2 + 100 ); 
		cvCreateTrackbar("�W�[��", ctrlPanel1, randValue, 255, work);
		cvCreateTrackbar("�W�[��", ctrlPanel1, randValue+1, 255, work);
		cvCreateTrackbar("�W�[��", ctrlPanel1, randValue+2, 255, work);
		cvCreateTrackbar("��֬�", ctrlPanel2, randValue+3, 255, work);
		cvCreateTrackbar("��ֺ�", ctrlPanel2, randValue+4, 255, work);
		cvCreateTrackbar("�����", ctrlPanel2, randValue+5, 255, work);
		cvShowImage(ctrlPanel1, NULL);
		cvShowImage(ctrlPanel2, NULL);
		work(0);

		cvWaitKey(0);
		//release
		cvSaveImage(outputPath, des);

		cvReleaseImage(&img);
		cvReleaseImage(&des);
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("�վ�RGB");
}//end getFIlterName