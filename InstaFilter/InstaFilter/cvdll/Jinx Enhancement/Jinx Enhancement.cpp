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

bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath)
{
	char inputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath, -1, inputPath, SIZE, NULL, NULL);//wchar_t * to char
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img = cvLoadImage(inputPath, 0);
	if(!img)
		return false;
	else 
	{
		//inverse
		unsigned char lut[256];
		CvMat *lut_mat;
		lut_mat = cvCreateMatHeader(1, 256, CV_8UC1);
		for (int i = 0; i < 256; i++)
			lut[i] = 255 - i;
		cvSetData(lut_mat, lut, 0);
		cvLUT(img, img, lut_mat);

		Mat src = img;
		int w = src.cols;
		int h = src.rows;
		Mat reslut(h, w, CV_8UC3);

		for(int i = 0 ; i < 4 ; i++)
		{
			IplImage *temp = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
			IplImage *filter = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

			CvScalar scalar = CV_RGB(20, 20, 20); 
			cvAddS(img, scalar, filter, 0); 

			switch(i)
			{
				//G
			case 0:
				cvMerge(img, filter, img, NULL, temp);
				break;
				//en B
			case 1:
				scalar = CV_RGB(10, 10, 10); 
				cvAddS(filter, scalar, filter, 0); 
				cvMerge(filter, img, img, NULL, temp);
				break;
				//R
			case 2:
				cvMerge(img, img, filter, NULL, temp);
				break;
				//gray
			case 3:
				cvMerge(img, img, img, NULL, temp);
				break;
			}//end switch
			
			//en yellow to all channel
			scalar = CV_RGB(15, 15, 15); 
			cvAddS(temp, scalar, temp, 0); 

			Mat imgColor = temp;
		
			//combine
			int x = i % 2;
			int y = i / 2;
			Mat ROI = reslut( Rect(x*w /2, y*h /2, w /2, h /2) );
			resize(imgColor, ROI, ROI.size());
			ROI.release();
			cvReleaseImage(&temp);
			cvReleaseImage(&filter);
		}//end for

		//inverse again
		IplImage des = reslut;
		cvLUT(&des, &des, lut_mat);

		cvSaveImage(outputPath, &des);

		//release source
		cvReleaseImage(&img);
		src.release();
		reslut.release();
		cvReleaseMat(&lut_mat);

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Jinx ¥[±jª©");
}//end getFIlterName