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
	IplImage *img = cvLoadImage(inputPath, 1);
	if(!img)
		return false;
	else  
	{
		Mat src = img;
		int width = src.cols;
		int heigh = src.rows;
		Point center(width/2,heigh/2);
		Mat img2(src.size(),CV_8UC3);
		src.copyTo(img2);

		for (int y=0; y<heigh; y++)
		{
			uchar *img2_p = img2.ptr<uchar>(y);
			for (int x=0; x<width; x++)
			{
				double theta = atan2((double)(y-center.y),(double)(x-center.x));

				int R2 = sqrtf(norm(Point(x,y)-center))*8;
			
				int newX = center.x+(int)(R2*cos(theta));

				int newY = center.y+(int)(R2*sin(theta));

				if(newX<0) newX=0;
				else if(newX>=width) newX=width-1;
				if(newY<0) newY=0;
				else if(newY>=heigh) newY=heigh-1;
					

				img2_p[3*x]=src.at<uchar>(newY,newX*3);
				img2_p[3*x+1]=src.at<uchar>(newY,newX*3+1);
				img2_p[3*x+2]=src.at<uchar>(newY,newX*3+2);
			}
		}
		
		IplImage reslut = img2;
		cvSaveImage(outputPath, &reslut);
		img2.release();
		src.release();
		cvReleaseImage(&img);

		return true;
	}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("凹透鏡");
}//end getFIlterName