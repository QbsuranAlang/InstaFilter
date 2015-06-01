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

IplImage *img, reslut;
static int num = 5;
Mat image;

static void work(int X, int Y)
{
	image = img;
	Mat src1u[3];
	split(image,src1u);

	int width = img->width;
	int height = img->height;

	Point center(X, Y);
	
	for (int y = 0; y < height ; y++)
	{
		uchar *imgP  = image.ptr<uchar>(y);
		for (int x = 0; x < width; x++)
		{
			int R = norm(Point(x,y)-center);
			double angle = atan2((double)(y-center.y), (double)(x-center.x));
			int tmp0 = 0, tmp1 = 0, tmp2 = 0;

			for (int i = 0 ; i < num ; i++)
			{
				int tmpR = (R - i) > 0 ? (R-i) : 0;
				
				int newX = tmpR * cos(angle) + center.x;
				int newY = tmpR * sin(angle) + center.y;
				
				if(newX < 0)newX = 0;
				if(newX > width - 1) newX = width-1;
				if(newY < 0)newY = 0;
				if(newY > height - 1)newY = height-1;

				tmp0 += src1u[0].at<uchar>(newY,newX);
				tmp1 += src1u[1].at<uchar>(newY,newX);
				tmp2 += src1u[2].at<uchar>(newY,newX);
			}
			imgP[img->nChannels*x] = (uchar)(tmp0 / num);
			imgP[img->nChannels*x + 1] = (uchar)(tmp1 / num);
			imgP[img->nChannels*x + 2] = (uchar)(tmp2 / num);
		}
	}
	reslut = image;
	src1u[2].release();
	src1u[1].release();
	src1u[0].release();
}//end work

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
		work(img->width / 2, img->height / 2);

		cvSaveImage(outputPath, &reslut);
		cvReleaseImage(&img);
		image.release();

		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("Radio Blur");
}//end getFIlterName