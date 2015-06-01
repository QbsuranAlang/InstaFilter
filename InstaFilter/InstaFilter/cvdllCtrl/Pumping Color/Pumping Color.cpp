#include <Windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#include <opencv2/imgproc/imgproc.hpp>
#define SIZE 256

extern "C"
{
	__declspec(dllexport)bool _stdcall opencvProcess(LPWSTR csInputPath, LPWSTR csOutputPath);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

IplImage *img, *dst, *colorMap;
static char *windowName = "抽色";
static char *ctrlPanel = "控制面板";
static char *trackbarUpperName = "上限";//named trackbar
static char *trackbarLowerName = "下限";
static char *trackbarInverseName = "反轉";
static char *refWindowName = "Color Map";
static int upper = 230, lower = 180;
IplImage *createColorMap();
IplImage *convertImageHSVtoRGB(const IplImage *imageHSV);
void RGBtoH(unsigned char R, unsigned char G, unsigned char B, int &h);
static void getColor(IplImage *src, int x, int y);

static void work(int)
{
	dst = cvCloneImage(img);
	colorMap = createColorMap();
	
	//source image
	for(int i = 0 ; i < img->height ; i++)
		for(int j = 0 ; j < img->widthStep ; j+=img->nChannels)
		{
			int index = i * img->widthStep + j;
			unsigned char B = img->imageData[index];
			unsigned char G = img->imageData[index + 1];
			unsigned char R = img->imageData[index + 2];

			int h;
			RGBtoH(R, G, B, h);

			bool reslut = (h  >= lower && h <= upper);
			if(cvGetTrackbarPos(trackbarInverseName, ctrlPanel))
				reslut = !reslut;
			if(reslut)
			{
				unsigned char gray = (unsigned char)(.299*R + .587*G + .114*B);
				dst->imageData[index] = dst->imageData[index + 1] = dst->imageData[index + 2 ] = gray;
			}//end if
		}//end for

	//ref image
	for(int i = 0 ; i < colorMap->height ; i++)
		for(int j = 0 ; j < colorMap->widthStep ; j+=colorMap->nChannels)
		{
			int index = i * colorMap->widthStep + j;
			unsigned char B = colorMap->imageData[index];
			unsigned char G = colorMap->imageData[index + 1];
			unsigned char R = colorMap->imageData[index + 2];

			int h;
			RGBtoH(R, G, B, h);

			bool reslut = (h  >= lower && h <= upper);
			if(cvGetTrackbarPos(trackbarInverseName, ctrlPanel))
				reslut = !reslut;
			if(reslut)
			{
				unsigned char gray = (unsigned char)(.299*R + .587*G + .114*B);
				colorMap->imageData[index] = colorMap->imageData[index + 1] = colorMap->imageData[index + 2 ] = gray;
			}//end if
		}//end for

	cvShowImage(refWindowName, colorMap);
	cvShowImage(windowName, dst);

}//end work

static void trackbarUpper(int)
{
	if( upper <= lower )
	{
		cvSetTrackbarPos(trackbarUpperName, ctrlPanel, lower);
		cvSetTrackbarPos(trackbarLowerName, ctrlPanel, lower);
	}//end if
	work(0);//binary image
}//end upper

static void trackbarLower(int)
{
	if( upper <= lower )
	{
		cvSetTrackbarPos(trackbarUpperName, ctrlPanel, upper);
		cvSetTrackbarPos(trackbarLowerName, ctrlPanel, upper);
	}//end if
	work(0);//binary image
}//end lower

static void on_mouse( int Event, int x, int y, int flags, void* ustc)
{
	if(flags & CV_EVENT_FLAG_LBUTTON)
	{
		getColor(img, x, y);
	}//end if
}//end mouse

static void on_mouseRef( int Event, int x, int y, int flags, void* ustc)
{

	if(flags & CV_EVENT_FLAG_LBUTTON)
	{
		getColor(colorMap, x, y);
	}//end if
}//end mouse

static void getColor(IplImage *src, int x, int y)
{
	int foo = 1;
	CvPoint p0 = cvPoint(x - foo, y - foo);
	CvPoint p1 = cvPoint(x + foo, y + foo);

	//deter ROI
	//corner
	if(x<foo && y<foo)
	{
		p0 = cvPoint(0, 0);
		p1 = cvPoint(2*foo, 2*foo);
	}
	else if(x>img->width-foo && y<foo)
	{
		p0 = cvPoint(img->width-2*foo, 0);
		p1 = cvPoint(img->width, 2*foo);
	}
	else if(x<foo && y>img->height-foo)
	{
		p0 = cvPoint(0, img->height-2*foo);
		p1 = cvPoint(2*foo, img->height);
	}
	else if(x>img->width-foo && y>img->height-foo)
	{
		p0 = cvPoint(img->width-2*foo, img->height-2*foo);
		p1 = cvPoint(img->width, img->height);
	}//end else
	//border
	else if(x < foo)
	{
		p0 = cvPoint(0, y-foo);
		p1 = cvPoint(2*foo, y+foo);
	}
	else if(x > img->width - foo)
	{
		p0 = cvPoint(img->width-2*foo, y-foo);
		p1 = cvPoint(img->width, y + foo);
	}

	else if(y < foo)
	{
		p0 = cvPoint(x-foo, 0);
		p1 = cvPoint(x+foo, 2*foo);
	}
	else if(y > img->height - foo)
	{
		p0 = cvPoint(x-foo, img->height-2*foo);
		p1 = cvPoint(x+foo, img->height);
	}

	//get averge color
	IplImage *temp = cvCloneImage(src);
	cvSetImageROI(temp, cvRect(p0.x, p0.y, p1.x-p0.x, p1.y-p0.y));
	CvScalar mean = cvAvg(temp);
	cvReleaseImage(&temp);

	int index = y * img->widthStep + x;
	int h;
	RGBtoH(mean.val[2], mean.val[1], mean.val[0], h);
	upper = h + 25;
	lower = h - 25;
	if(upper > 360) upper = 360;
	if(lower < 0) lower = 0;
	cvSetTrackbarPos(trackbarUpperName, ctrlPanel, upper);
	cvSetTrackbarPos(trackbarLowerName, ctrlPanel, lower);
	work(0);
}//end getColor

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
		if(img->nChannels == 1)
		{
			cvReleaseImage(&img);
			return false;
		}//end if
		else if(img->nChannels == 4 || img->depth != 8)
		{
			cvReleaseImage(&img);
			img = cvLoadImage(inputPath, 1);
		}//end else

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
		cvSetMouseCallback( windowName, on_mouse, 0 );
		CvSize panelSize = cvSize(600, 135);
		cvNamedWindow(ctrlPanel, 1);
		cvResizeWindow(ctrlPanel, panelSize.width, panelSize.height);
		cvMoveWindow(ctrlPanel, (xScreen-size.width)/2, (yScreen-size.height)/2 ); 
		cvCreateTrackbar(trackbarUpperName, ctrlPanel, &upper, 360, trackbarUpper);
		cvCreateTrackbar(trackbarLowerName, ctrlPanel, &lower, 360, trackbarLower);
		int zeroPosition = 0;
		cvCreateTrackbar(trackbarInverseName, ctrlPanel, &zeroPosition, 1, work);
		cvShowImage(ctrlPanel, NULL);

		cvNamedWindow(refWindowName, 1);
		cvMoveWindow(refWindowName, GetSystemMetrics(SM_CXSCREEN)/2, GetSystemMetrics(SM_CYSCREEN)/2 - 100);
		cvSetMouseCallback( refWindowName, on_mouseRef, 0 );
		work(0);
		cvWaitKey(0);

		cvSaveImage(outputPath, dst);

		cvDestroyAllWindows();
		cvReleaseImage(&img);
		cvReleaseImage(&dst);
		cvReleaseImage(&colorMap);
		return true;
		}//end else
	return false;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("抽色");
}//end getFIlterName

IplImage *createColorMap()
{
	CvSize size = cvSize(512, 512);
	IplImage *H = cvCreateImage(size, 8, 1);
	IplImage *S = cvCreateImage(size, 8, 1);
	IplImage *V = cvCreateImage(size, 8, 1);

	cvSet(H, cvScalar(255));
	cvSet(S, cvScalar(255));
	cvSet(V, cvScalar(255));

	for(int i = 0 ; i < H->height; i++)
		for(int j = 0 ; j < 256 ; j++)
		{
			int index = i*H->widthStep+j*2;
			H->imageData[index] = H->imageData[index+1] = j;

			if(i < H->height / 2)
				S->imageData[index] = S->imageData[index + 1] = i;
			else
				V->imageData[index] = V->imageData[index + 1] = 255 - i;
		}//end for

	IplImage *hsv = cvCreateImage(size, 8, 3);
	cvMerge(H, S, V, 0, hsv);
	IplImage *img = convertImageHSVtoRGB(hsv);

	cvReleaseImage(&H);
	cvReleaseImage(&S);
	cvReleaseImage(&V);
	cvReleaseImage(&hsv);

	return img;
}//end createColorMap

void RGBtoH(unsigned char R, unsigned char G, unsigned char B, int &h)
{
	double r = R / 255.;
	double g = G / 255.;
	double b = B / 255.;

	// RGB 轉 H 公式
	if (r >= g && g>= b)
		h = 60 * (g-b)/(r-b);
	else if (g > r && r >= b)
		h = 60 * (2-((r-b)/(g-b)));
	else if (g >= b && b > r)
		h = 60 * (2+ ((b-r)/(g-r)));
	else if (b >g && g>r)
		h = 60 * (4 - (g-r)/(b-r));
	else if (b>r && r>=g)
		h = 60 * (4 + (r-g)/(b-g));
	else if (r>=b && b>g)
		h = 60 * (6-(b-g)/(r-g));
	else
		h = 0;

	if( h < 0 )
		h += 360;
	else
		h %= 360;
}//end RGBtoH

IplImage *convertImageHSVtoRGB(const IplImage *imageHSV)
{
	float fH, fS, fV;
	float fR, fG, fB;
	const float FLOAT_TO_BYTE = 255.0f;
	const float BYTE_TO_FLOAT = 1.0f / FLOAT_TO_BYTE;

	// Create a blank RGB image
	IplImage *imageRGB = cvCreateImage(cvGetSize(imageHSV), 8, 3);
	if (!imageRGB || imageHSV->depth != 8 || imageHSV->nChannels != 3)
		return NULL;

	int h = imageHSV->height;			// Pixel height.
	int w = imageHSV->width;			// Pixel width.
	int rowSizeHSV = imageHSV->widthStep;		// Size of row in bytes, including extra padding.
	char *imHSV = imageHSV->imageData;		// Pointer to the start of the image pixels.
	int rowSizeRGB = imageRGB->widthStep;		// Size of row in bytes, including extra padding.
	char *imRGB = imageRGB->imageData;		// Pointer to the start of the image pixels.
	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			// Get the HSV pixel components
			uchar *pHSV = (uchar*)(imHSV + y*rowSizeHSV + x*3);
			int bH = *(uchar*)(pHSV+0);	// H component
			int bS = *(uchar*)(pHSV+1);	// S component
			int bV = *(uchar*)(pHSV+2);	// V component

			// Convert from 8-bit integers to floats
			fH = (float)bH * BYTE_TO_FLOAT;
			fS = (float)bS * BYTE_TO_FLOAT;
			fV = (float)bV * BYTE_TO_FLOAT;

			// Convert from HSV to RGB, using float ranges 0.0 to 1.0
			int iI;
			float fI, fF, p, q, t;

			if( bS == 0 ) {
				// achromatic (grey)
				fR = fG = fB = fV;
			}
			else {
				// If Hue == 1.0, then wrap it around the circle to 0.0
				if (fH >= 1.0f)
					fH = 0.0f;

				fH *= 6.0;			// sector 0 to 5
				fI = floor( fH );		// integer part of h (0,1,2,3,4,5 or 6)
				iI = (int) fH;			//		"		"		"		"
				fF = fH - fI;			// factorial part of h (0 to 1)

				p = fV * ( 1.0f - fS );
				q = fV * ( 1.0f - fS * fF );
				t = fV * ( 1.0f - fS * ( 1.0f - fF ) );

				switch( iI ) {
					case 0:
						fR = fV;
						fG = t;
						fB = p;
						break;
					case 1:
						fR = q;
						fG = fV;
						fB = p;
						break;
					case 2:
						fR = p;
						fG = fV;
						fB = t;
						break;
					case 3:
						fR = p;
						fG = q;
						fB = fV;
						break;
					case 4:
						fR = t;
						fG = p;
						fB = fV;
						break;
					default:		// case 5 (or 6):
						fR = fV;
						fG = p;
						fB = q;
						break;
				}
			}

			// Convert from floats to 8-bit integers
			int bR = (int)(fR * FLOAT_TO_BYTE);
			int bG = (int)(fG * FLOAT_TO_BYTE);
			int bB = (int)(fB * FLOAT_TO_BYTE);

			// Clip the values to make sure it fits within the 8bits.
			if (bR > 255)
				bR = 255;
			if (bR < 0)
				bR = 0;
			if (bG > 255)
				bG = 255;
			if (bG < 0)
				bG = 0;
			if (bB > 255)
				bB = 255;
			if (bB < 0)
				bB = 0;

			// Set the RGB pixel components. NOTE that OpenCV stores RGB pixels in B,G,R order.
			uchar *pRGB = (uchar*)(imRGB + y*rowSizeRGB + x*3);
			*(pRGB+0) = bB;		// B component
			*(pRGB+1) = bG;		// G component
			*(pRGB+2) = bR;		// R component
		}
	}
	return imageRGB;
}