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

int BrightnessPosition = 100;
int ContrastPosition = 100;
IplImage *img,*dst;
unsigned char LookupTableData[256];
CvMat *LookupTableMatrix;
static char *windowName = "調整亮度和對比";

void onTrackbar(int)
{
    int Brightness = BrightnessPosition - 100;
    int Contrast = ContrastPosition - 100;
    double Delta;
    double a,b;
	int y;

	IplImage *filterB = cvCreateImage(cvGetSize(img), img->depth, 1);
	IplImage *filterG = cvCreateImage(cvGetSize(img), img->depth, 1);
	IplImage *filterR = cvCreateImage(cvGetSize(img), img->depth, 1);
	cvSplit(img, filterB, filterG, filterR, 0);

    //Brightness/Contrast Formula
    if(Contrast > 0)
    {
        Delta = 127 * Contrast / 100;
        a=255 / (255 - Delta * 2);
        b = a * (Brightness - Delta);
    }
    else
    {
        Delta = -128 * Contrast / 100;
        a = (256 - Delta*2) / 255;
        b = a * Brightness + Delta;
    }

	for(int x = 0 ; x < 256 ; x++)
    {
        y=(int)(a * x + b);
		if(y < 0) y = 0; else if(y > 255) y = 255;

        LookupTableData[x]=(uchar)y;
    }

    cvLUT(filterB, filterB,LookupTableMatrix);
	cvLUT(filterG, filterG,LookupTableMatrix);
	cvLUT(filterR, filterR,LookupTableMatrix);

	cvMerge(filterB, filterG, filterR, 0, dst);

    cvShowImage(windowName, dst);
    cvReleaseImage(&filterB);
	cvReleaseImage(&filterG);
	cvReleaseImage(&filterR);
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
	
		size.height += 90;

		cvNamedWindow(windowName, 0);
		cvResizeWindow(windowName, size.width, size.height); 
		cvMoveWindow(windowName, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		
		dst = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
	
		LookupTableMatrix = cvCreateMatHeader(1,256,CV_8UC1);
		cvSetData(LookupTableMatrix, LookupTableData, 0);

		cvNamedWindow(windowName, 1);

		//read Brightness Contrast from file
		char bcPath[SIZE] = "";
		sprintf(bcPath, "%s\\InstaFilter\\Brightness and Contrast.if", getenv("temp"));
		FILE *bc = fopen(bcPath, "rb");
		if(!bc) return false;
		//read
		char data[SIZE];
		fgets(data, SIZE, bc);
		char *token = strtok(data, " ");
		BrightnessPosition += atoi(token);
		token = strtok(NULL, " ");
		ContrastPosition += atoi(token);
		fclose(bc);

		cvCreateTrackbar("亮度", windowName, &BrightnessPosition, 200, onTrackbar);
		cvCreateTrackbar("對比", windowName, &ContrastPosition, 200, onTrackbar);

		onTrackbar(0);

		cvWaitKey(0);
			
		//release
		cvSaveImage(outputPath, dst);
		cvReleaseImage(&img);
		cvReleaseImage(&dst);
		cvDestroyAllWindows();

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("調整亮度和對比");
}//end getFIlterName