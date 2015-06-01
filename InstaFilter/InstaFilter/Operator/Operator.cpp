#include <Windows.h>
#include <wchar.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <tchar.h>
#define SIZE 256

extern "C"
{
	__declspec(dllexport)bool _stdcall add(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall sub(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall subAbs(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall opacity(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall multiply(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall screen(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall overlay(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall darken(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall lighten(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall colorDodge(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall colorBurn(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall linearBurn(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall hardLight(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall softLight(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall linearLight(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall vividLight(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall hardMix(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)bool _stdcall exclusion(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath);
	__declspec(dllexport)double _stdcall PSNR(LPWSTR csInputPath1, LPWSTR csInputPath2);
	__declspec(dllexport)LPWSTR _stdcall getFilterName(void);
}//end extern "C"

__declspec(dllexport)bool _stdcall add(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		cvAdd(img1, img2, img1);

		cvSaveImage(outputPath, img1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);

		return true;
	}//end else
	return false;
}//end add

__declspec(dllexport)bool _stdcall sub(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		cvSub(img1, img2, img1);

		cvSaveImage(outputPath, img1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);

		return true;
	}//end else
	return false;
}//end sub

__declspec(dllexport)bool _stdcall subAbs(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		cvAbsDiff(img1, img2, img1);

		cvSaveImage(outputPath, img1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);

		return true;
	}//end else
	return false;
}//end subAbs

static char *windowName = "影像融合";
int trackPos = 50;
int gammaValue = 0.0;
IplImage *img1, *img2, *dst;

void work(int)
{
	double value = trackPos / 100.;
	double gamma = (double)gammaValue;

	cvAddWeighted(img1, value, img2, 1.0 - value, gamma, dst);
	cvShowImage(windowName, dst);
}//end work

__declspec(dllexport)bool _stdcall opacity(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	img1 = cvLoadImage(inputPath1, -1);
	img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		dst = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);

		CvSize size = cvGetSize(img1); 

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
		cvCreateTrackbar("權重", windowName, &trackPos, 100, work);
		cvCreateTrackbar("Gamma", windowName, &gammaValue, 255, work);
		work(0);

		cvWaitKey(0);
		cvSaveImage(outputPath, dst);

		cvReleaseImage(&dst);
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);

		return true;
	}//end else
	return false;
}//end addWeight

__declspec(dllexport)bool _stdcall multiply(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		// a*b/255
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *temp = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);

		cvConvertScale(img1, floatingImg1, 1./255.);
		cvConvertScale(img2, floatingImg2, 1./255.);

		cvMul(floatingImg1, floatingImg2, floatingImg1);//a*b
		cvConvertScale(floatingImg1, temp, 255);
		cvSaveImage(outputPath, temp);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&temp);
		return true;
		
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall screen(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		// 1 - (1-A)*(1-B)
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *floating1 = cvCloneImage(floatingImg1);
		IplImage *temp = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);

		cvConvertScale(img1, floatingImg1, 1./255.);
		cvConvertScale(img2, floatingImg2, 1./255.);
		cvSet(floating1, cvScalarAll(1.0));

		cvSub(floating1, floatingImg1, floatingImg1);//1-A
		cvSub(floating1, floatingImg2, floatingImg2);//1-B
		cvMul(floatingImg1, floatingImg2, floatingImg1); // (1-A)*(1-B)
		cvSub(floating1, floatingImg1, floatingImg1);//1 - (1-A)*(1-B)

		cvConvertScale(floatingImg1, temp, 255);
		cvSaveImage(outputPath, temp);
		
		cvReleaseImage(&temp);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&floating1);
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall overlay(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		// A + (B - 127.5) * (1 - abs(A-127.5)/127.5)
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);

		IplImage *temp32 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floating127 = cvCloneImage(temp32);
		IplImage *floating1 = cvCloneImage(temp32);
		IplImage *temp32_2 = cvCloneImage(temp32);

		IplImage *temp = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);

		cvSet(floating127, cvScalarAll(127.5));
		cvSet(floating1, cvScalarAll(1.0));
		cvConvertScale(img1, floatingImg1, 1.0);
		cvConvertScale(img2, floatingImg2, 1.0);

		cvAbsDiff(floatingImg1, floating127, temp32); //abs(A-127.5)
		cvDiv(temp32, floating127, temp32); //abs(A-127.5)/127.5
		cvSub(floating1, temp32, temp32); //(1 - abs(A-127.5)/127.5)

		cvSub(floatingImg2, floating127, temp32_2);//(B - 127.5)
		cvMul(temp32_2, temp32, temp32);//(B - 127.5) * (1 - abs(A-127.5)/127.5)

		cvAdd(floatingImg1, temp32, temp32);// A + (B - 127.5) * (1 - abs(A-127.5)/127.5)

		cvConvertScale(temp32, temp, 1);

		cvSaveImage(outputPath, temp);
		
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&temp32);
		cvReleaseImage(&temp32_2);
		cvReleaseImage(&floating127);
		cvReleaseImage(&floating1);
		cvReleaseImage(&temp);
		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall darken(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//B<=A: C=B
		//B>A: C=A
		IplImage *B1 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		IplImage *G1 = cvCloneImage(B1);
		IplImage *R1 = cvCloneImage(B1);
		IplImage *B2 = cvCloneImage(B1);
		IplImage *G2 = cvCloneImage(B1);
		IplImage *R2 = cvCloneImage(B1);
		IplImage *maskB = cvCloneImage(B1);
		IplImage *maskG = cvCloneImage(B1);
		IplImage *maskR = cvCloneImage(B1);
		IplImage *dstB = cvCloneImage(B1);
		IplImage *dstG = cvCloneImage(B1);
		IplImage *dstR = cvCloneImage(B1);
		IplImage *temp1 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp2 = cvCloneImage(temp1);

		cvSplit(img1, B1, G1, R1, 0);
		cvSplit(img2, B2, G2, R2, 0);

		//B<=A
		cvCmp(B2, B1, maskB, CV_CMP_LE);
		cvCmp(G2, G1, maskG, CV_CMP_LE);
		cvCmp(R2, R1, maskR, CV_CMP_LE);
		
		//C=B
		cvCopy(B2, dstB, maskB);
		cvCopy(G2, dstG, maskG);
		cvCopy(R2, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp1);

		cvZero(maskB);
		cvZero(maskG);
		cvZero(maskR);
		cvZero(dstB);
		cvZero(dstG);
		cvZero(dstR);
		//B>A
		cvCmp(B2, B1, maskB, CV_CMP_GT);
		cvCmp(G2, G1, maskG, CV_CMP_GT);
		cvCmp(R2, R1, maskR, CV_CMP_GT);
		
		//C=A
		cvCopy(B1, dstB, maskB);
		cvCopy(G1, dstG, maskG);
		cvCopy(R1, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp2);

		cvAdd(temp1, temp2, temp1);

		cvSaveImage(outputPath, temp1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&B1);
		cvReleaseImage(&G1);
		cvReleaseImage(&R1);
		cvReleaseImage(&B2);
		cvReleaseImage(&G2);
		cvReleaseImage(&R2);
		cvReleaseImage(&maskB);
		cvReleaseImage(&maskG);
		cvReleaseImage(&maskR);
		cvReleaseImage(&dstB);
		cvReleaseImage(&dstG);
		cvReleaseImage(&dstR);
		cvReleaseImage(&temp1);
		cvReleaseImage(&temp2);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall lighten(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//B<=A: C=A
		//B>A: C=B
		IplImage *B1 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		IplImage *G1 = cvCloneImage(B1);
		IplImage *R1 = cvCloneImage(B1);
		IplImage *B2 = cvCloneImage(B1);
		IplImage *G2 = cvCloneImage(B1);
		IplImage *R2 = cvCloneImage(B1);
		IplImage *maskB = cvCloneImage(B1);
		IplImage *maskG = cvCloneImage(B1);
		IplImage *maskR = cvCloneImage(B1);
		IplImage *dstB = cvCloneImage(B1);
		IplImage *dstG = cvCloneImage(B1);
		IplImage *dstR = cvCloneImage(B1);
		IplImage *temp1 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp2 = cvCloneImage(temp1);

		cvSplit(img1, B1, G1, R1, 0);
		cvSplit(img2, B2, G2, R2, 0);

		//B<=A
		cvCmp(B2, B1, maskB, CV_CMP_LE);
		cvCmp(G2, G1, maskG, CV_CMP_LE);
		cvCmp(R2, R1, maskR, CV_CMP_LE);
		
		//C=A
		cvCopy(B1, dstB, maskB);
		cvCopy(G1, dstG, maskG);
		cvCopy(R1, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp1);

		cvZero(maskB);
		cvZero(maskG);
		cvZero(maskR);
		cvZero(dstB);
		cvZero(dstG);
		cvZero(dstR);
		//B>A
		cvCmp(B2, B1, maskB, CV_CMP_GT);
		cvCmp(G2, G1, maskG, CV_CMP_GT);
		cvCmp(R2, R1, maskR, CV_CMP_GT);
		
		//C=B
		cvCopy(B2, dstB, maskB);
		cvCopy(G2, dstG, maskG);
		cvCopy(R2, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp2);

		cvAdd(temp1, temp2, temp1);

		cvSaveImage(outputPath, temp1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&B1);
		cvReleaseImage(&G1);
		cvReleaseImage(&R1);
		cvReleaseImage(&B2);
		cvReleaseImage(&G2);
		cvReleaseImage(&R2);
		cvReleaseImage(&maskB);
		cvReleaseImage(&maskG);
		cvReleaseImage(&maskR);
		cvReleaseImage(&dstB);
		cvReleaseImage(&dstG);
		cvReleaseImage(&dstR);
		cvReleaseImage(&temp1);
		cvReleaseImage(&temp2);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall colorDodge(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//B/(1-A)
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *floating1 = cvCloneImage(floatingImg1);
		IplImage *temp = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);

		cvSet(floating1, cvScalarAll(1.0));

		cvConvertScale(img1, floatingImg1, 1/255.);
		cvConvertScale(img2, floatingImg2, 1/255.);

		cvSub(floating1, floatingImg1, floatingImg1);//(1-A)
		cvAddS(floatingImg1, cvScalarAll(1/255.), floatingImg1);//avoid divide by zero
		cvDiv(floatingImg2, floatingImg1, floatingImg1); //B/(1-A)

		cvConvertScale(floatingImg1, temp, 255);

		cvSaveImage(outputPath, temp);

		cvReleaseImage(&temp);
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&floating1);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall colorBurn(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//1-(1-B)/A
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *floating1 = cvCloneImage(floatingImg1);
		IplImage *temp = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);

		cvSet(floating1, cvScalarAll(1.0));

		cvConvertScale(img1, floatingImg1, 1/255.);
		cvConvertScale(img2, floatingImg2, 1/255.);

		cvSub(floating1, floatingImg2, floatingImg2);//(1-B)
		cvAddS(floatingImg1, cvScalarAll(1/255.), floatingImg1);//avoid divide by zero
		cvDiv(floatingImg2, floatingImg1, floatingImg1); //(1-B)/A
		cvSub(floating1, floatingImg1, floatingImg1);//1-(1-B)/A

		cvConvertScale(floatingImg1, temp, 255);

		cvSaveImage(outputPath, temp);

		cvReleaseImage(&temp);
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&floating1);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall linearBurn(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//A+B-1
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *floating1 = cvCloneImage(floatingImg1);
		IplImage *temp = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);

		cvSet(floating1, cvScalarAll(1.0));

		cvConvertScale(img1, floatingImg1, 1/255.);
		cvConvertScale(img2, floatingImg2, 1/255.);

		cvAdd(floatingImg1, floatingImg2, floatingImg2);//A+B
		cvSub(floatingImg2, floating1, floatingImg2);//A+B-1

		cvConvertScale(floatingImg2, temp, 255);
		cvSaveImage(outputPath, temp);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&floating1);
		cvReleaseImage(&temp);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall hardLight(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//A<=0.5: C=2*A*B
		//A>0.5: C=1-2*(1-A)*(1-B)
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *floating1 = cvCloneImage(floatingImg1);
		IplImage *temp32 = cvCloneImage(floatingImg1);
		IplImage *under127 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *upper127 = cvCloneImage(under127);

		cvSet(floating1, cvScalarAll(1.0));

		cvConvertScale(img1, floatingImg1, 1/255.);
		cvConvertScale(img2, floatingImg2, 1/255.);

		//C=2*A*B
		cvMul(floatingImg1, floatingImg2, temp32, 2);
		cvConvertScale(temp32, under127, 127.);

		//C=1-2*(1-A)*(1-B)
		cvSub(floating1, floatingImg1, floatingImg1);//1-A
		cvSub(floating1, floatingImg2, floatingImg2);//1-B
		cvMul(floatingImg1, floatingImg2, floatingImg2, 2);//2*(1-A)*(1-B)
		cvSub(floating1, floatingImg2, temp32); //1-2*(1-A)*(1-B)
		cvConvertScale(temp32, upper127, 127.5, 127.5);

		IplImage *B1 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		IplImage *G1 = cvCloneImage(B1);
		IplImage *R1 = cvCloneImage(B1);
		IplImage *B2 = cvCloneImage(B1);
		IplImage *G2 = cvCloneImage(B1);
		IplImage *R2 = cvCloneImage(B1);
		IplImage *upperB127 = cvCloneImage(B1);
		IplImage *upperG127 = cvCloneImage(B1);
		IplImage *upperR127 = cvCloneImage(B1);
		IplImage *underB127 = cvCloneImage(B1);
		IplImage *underG127 = cvCloneImage(B1);
		IplImage *underR127 = cvCloneImage(B1);
		IplImage *maskB = cvCloneImage(B1);
		IplImage *maskG = cvCloneImage(B1);
		IplImage *maskR = cvCloneImage(B1);
		IplImage *dstB = cvCloneImage(B1);
		IplImage *dstG = cvCloneImage(B1);
		IplImage *dstR = cvCloneImage(B1);
		IplImage *temp1 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp2 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp127 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		
		cvSet(temp127, cvScalarAll(127));

		cvSplit(img1, B1, G1, R1, 0);
		cvSplit(img2, B2, G2, R2, 0);
		cvSplit(under127, underB127, underG127, underR127, 0);
		cvSplit(upper127, upperB127, upperG127, upperR127, 0);

		//A<=0.5
		cvCmp(B1, temp127, maskB, CV_CMP_LE);
		cvCmp(G1, temp127, maskG, CV_CMP_LE);
		cvCmp(R1, temp127, maskR, CV_CMP_LE);

		//C=2*A*B
		cvCopy(underB127, dstB, maskB);
		cvCopy(underG127, dstG, maskG);
		cvCopy(underR127, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp1);
		
		cvZero(maskB);
		cvZero(maskG);
		cvZero(maskR);
		cvZero(dstB);
		cvZero(dstG);
		cvZero(dstR);
		//A>0.5
		cvCmp(B1, temp127, maskB, CV_CMP_GT);
		cvCmp(G1, temp127, maskG, CV_CMP_GT);
		cvCmp(R1, temp127, maskR, CV_CMP_GT);

		//C=1-2*(1-A)*(1-B)
		cvCopy(upperB127, dstB, maskB);
		cvCopy(upperG127, dstG, maskG);
		cvCopy(upperR127, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp2);

		cvAdd(temp1, temp2, temp1);
		
		cvSaveImage(outputPath, temp1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&floating1);
		cvReleaseImage(&temp32);
		cvReleaseImage(&under127);
		cvReleaseImage(&upper127);
		cvReleaseImage(&B1);
		cvReleaseImage(&G1);
		cvReleaseImage(&R1);
		cvReleaseImage(&B2);
		cvReleaseImage(&G2);
		cvReleaseImage(&R2);
		cvReleaseImage(&upperB127);
		cvReleaseImage(&upperG127);
		cvReleaseImage(&upperR127);
		cvReleaseImage(&underB127);
		cvReleaseImage(&underG127);
		cvReleaseImage(&underR127);
		cvReleaseImage(&maskB);
		cvReleaseImage(&maskG);
		cvReleaseImage(&maskR);
		cvReleaseImage(&dstB);
		cvReleaseImage(&dstG);
		cvReleaseImage(&dstR);
		cvReleaseImage(&temp1);
		cvReleaseImage(&temp2);
		cvReleaseImage(&temp127);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall softLight(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//A<=0.5: C=(2*A-1)*(B-B*B)+B 
		//A>0.5: C=(2*A-1)*(sqrt(B)-B)+B
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *floating1 = cvCloneImage(floatingImg1);
		IplImage *temp32 = cvCloneImage(floatingImg1);
		IplImage *under127 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *upper127 = cvCloneImage(under127);

		cvSet(floating1, cvScalarAll(1.0));

		cvConvertScale(img1, floatingImg1, 1/255.);
		cvConvertScale(img2, floatingImg2, 1/255.);

		//A<=0.5: C=(2*A-1)*(B-B*B)+B 
		cvMul(floating1, floatingImg1, floatingImg1, 2);//2*A
		cvSub(floatingImg1, floating1, floatingImg1); //2*A-1
		cvMul(floatingImg2, floatingImg2, temp32);//B*B
		cvSub(floatingImg2, temp32, temp32); //B-B*B
		cvMul(floatingImg1, temp32, temp32); //(2*A-1)*(B-B*B)
		cvAdd(temp32, floatingImg2, temp32);//(2*A-1)*(B-B*B)+B
		cvConvertScale(temp32, under127, 255);//A<=0.5: C=(2*A-1)*(B-B*B)+B

		//A>0.5: C=(2*A-1)*(sqrt(B)-B)+B
		cvPow(floatingImg2, temp32, 0.5);//sqrt(B)
		cvSub(temp32, floatingImg2, temp32);//sqrt(B)-B
		cvMul(floatingImg1, temp32, temp32);//(2*A-1)*(sqrt(B)-B)
		cvAdd(temp32, floatingImg2, temp32);//(2*A-1)*(sqrt(B)-B)+B
		cvConvertScale(temp32, upper127, 255);////A>0.5: C=(2*A-1)*(sqrt(B)-B)+B


		IplImage *B1 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		IplImage *G1 = cvCloneImage(B1);
		IplImage *R1 = cvCloneImage(B1);
		IplImage *B2 = cvCloneImage(B1);
		IplImage *G2 = cvCloneImage(B1);
		IplImage *R2 = cvCloneImage(B1);
		IplImage *upperB127 = cvCloneImage(B1);
		IplImage *upperG127 = cvCloneImage(B1);
		IplImage *upperR127 = cvCloneImage(B1);
		IplImage *underB127 = cvCloneImage(B1);
		IplImage *underG127 = cvCloneImage(B1);
		IplImage *underR127 = cvCloneImage(B1);
		IplImage *maskB = cvCloneImage(B1);
		IplImage *maskG = cvCloneImage(B1);
		IplImage *maskR = cvCloneImage(B1);
		IplImage *dstB = cvCloneImage(B1);
		IplImage *dstG = cvCloneImage(B1);
		IplImage *dstR = cvCloneImage(B1);
		IplImage *temp1 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp2 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp127 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		
		cvSet(temp127, cvScalarAll(127));

		cvSplit(img1, B1, G1, R1, 0);
		cvSplit(img2, B2, G2, R2, 0);
		cvSplit(under127, underB127, underG127, underR127, 0);
		cvSplit(upper127, upperB127, upperG127, upperR127, 0);

		//A<=0.5
		cvCmp(B1, temp127, maskB, CV_CMP_LE);
		cvCmp(G1, temp127, maskG, CV_CMP_LE);
		cvCmp(R1, temp127, maskR, CV_CMP_LE);

		//C=(2*A-1)*(B-B*B)+B
		cvCopy(underB127, dstB, maskB);
		cvCopy(underG127, dstG, maskG);
		cvCopy(underR127, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp1);
		
		cvZero(maskB);
		cvZero(maskG);
		cvZero(maskR);
		cvZero(dstB);
		cvZero(dstG);
		cvZero(dstR);
		//A>0.5
		cvCmp(B1, temp127, maskB, CV_CMP_GT);
		cvCmp(G1, temp127, maskG, CV_CMP_GT);
		cvCmp(R1, temp127, maskR, CV_CMP_GT);

		//C=(2*A-1)*(sqrt(B)-B)+B
		cvCopy(upperB127, dstB, maskB);
		cvCopy(upperG127, dstG, maskG);
		cvCopy(upperR127, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp2);

		cvAdd(temp1, temp2, temp1);
		
		cvSaveImage(outputPath, temp1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&floating1);
		cvReleaseImage(&temp32);
		cvReleaseImage(&under127);
		cvReleaseImage(&upper127);
		cvReleaseImage(&B1);
		cvReleaseImage(&G1);
		cvReleaseImage(&R1);
		cvReleaseImage(&B2);
		cvReleaseImage(&G2);
		cvReleaseImage(&R2);
		cvReleaseImage(&upperB127);
		cvReleaseImage(&upperG127);
		cvReleaseImage(&upperR127);
		cvReleaseImage(&underB127);
		cvReleaseImage(&underG127);
		cvReleaseImage(&underR127);
		cvReleaseImage(&maskB);
		cvReleaseImage(&maskG);
		cvReleaseImage(&maskR);
		cvReleaseImage(&dstB);
		cvReleaseImage(&dstG);
		cvReleaseImage(&dstR);
		cvReleaseImage(&temp1);
		cvReleaseImage(&temp2);
		cvReleaseImage(&temp127);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall linearLight(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//C=B+2*A-1
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *floating1 = cvCloneImage(floatingImg1);

		cvConvertScale(img1, floatingImg1, 1/255.);
		cvConvertScale(img2, floatingImg2, 1/255.);
		cvSet(floating1, cvScalarAll(1.0));

		cvMul(floating1, floatingImg1, floatingImg1, 2);//2*A
		cvAdd(floatingImg2, floatingImg1, floatingImg1);//B+2*A
		cvSub(floatingImg1, floating1, floatingImg1);//B+2*A-1
		cvConvertScale(floatingImg1, img1, 255);

		cvSaveImage(outputPath, img1);
		
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floating1);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall vividLight(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//A<=0.5: C=1-(1-B)/2*A
		//A>0.5: C=B/(2*(1-A)) 
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *floating1 = cvCloneImage(floatingImg1);
		IplImage *temp32_upper = cvCloneImage(floatingImg1);
		IplImage *temp32_under = cvCloneImage(floatingImg1);
		IplImage *temp32 = cvCloneImage(floatingImg1);
		IplImage *under127 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *upper127 = cvCloneImage(under127);

		cvSet(floating1, cvScalarAll(1.0));

		cvConvertScale(img1, floatingImg1, 1/255.);
		cvConvertScale(img2, floatingImg2, 1/255.);

		//A<=0.5: C=1-(1-B)/2*A
		cvSub(floating1, floatingImg2, temp32_upper); //1-B
		cvMul(floating1, floatingImg1, temp32_under, 2);//2*A
		cvAddS(temp32_under, cvScalarAll(1/255.), temp32_under);//avoid divide by zero
		cvDiv(temp32_upper, temp32_under, temp32);//(1-B)/2*A
		cvSub(floating1, temp32, temp32);//1-(1-B)/2*A
		cvConvertScale(temp32, under127, 255);

		//A>0.5: C=B/(2*(1-A))
		cvSub(floating1, floatingImg1, temp32_under);//1-A
		cvMul(floating1, temp32_under, temp32_under, 2);//2*(1-A)
		cvAddS(temp32_under, cvScalarAll(1/255.), temp32_under);//avoid divide by zero
		cvDiv(floatingImg2, temp32_under, temp32);//B/(2*(1-A))
		cvConvertScale(temp32, upper127, 255);


		IplImage *B1 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		IplImage *G1 = cvCloneImage(B1);
		IplImage *R1 = cvCloneImage(B1);
		IplImage *B2 = cvCloneImage(B1);
		IplImage *G2 = cvCloneImage(B1);
		IplImage *R2 = cvCloneImage(B1);
		IplImage *upperB127 = cvCloneImage(B1);
		IplImage *upperG127 = cvCloneImage(B1);
		IplImage *upperR127 = cvCloneImage(B1);
		IplImage *underB127 = cvCloneImage(B1);
		IplImage *underG127 = cvCloneImage(B1);
		IplImage *underR127 = cvCloneImage(B1);
		IplImage *maskB = cvCloneImage(B1);
		IplImage *maskG = cvCloneImage(B1);
		IplImage *maskR = cvCloneImage(B1);
		IplImage *dstB = cvCloneImage(B1);
		IplImage *dstG = cvCloneImage(B1);
		IplImage *dstR = cvCloneImage(B1);
		IplImage *temp1 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp2 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp127 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		
		cvSet(temp127, cvScalarAll(127));

		cvSplit(img1, B1, G1, R1, 0);
		cvSplit(img2, B2, G2, R2, 0);
		cvSplit(under127, underB127, underG127, underR127, 0);
		cvSplit(upper127, upperB127, upperG127, upperR127, 0);

		//A<=0.5
		cvCmp(B1, temp127, maskB, CV_CMP_LE);
		cvCmp(G1, temp127, maskG, CV_CMP_LE);
		cvCmp(R1, temp127, maskR, CV_CMP_LE);

		//C=1-(1-B)/2*A
		cvCopy(underB127, dstB, maskB);
		cvCopy(underG127, dstG, maskG);
		cvCopy(underR127, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp1);
		
		cvZero(maskB);
		cvZero(maskG);
		cvZero(maskR);
		cvZero(dstB);
		cvZero(dstG);
		cvZero(dstR);
		//A>0.5
		cvCmp(B1, temp127, maskB, CV_CMP_GT);
		cvCmp(G1, temp127, maskG, CV_CMP_GT);
		cvCmp(R1, temp127, maskR, CV_CMP_GT);

		//C=B/(2*(1-A))
		cvCopy(upperB127, dstB, maskB);
		cvCopy(upperG127, dstG, maskG);
		cvCopy(upperR127, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp2);

		cvAdd(temp1, temp2, temp1);
		
		cvSaveImage(outputPath, temp1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&floating1);
		cvReleaseImage(&temp32);
		cvReleaseImage(&temp32_under);
		cvReleaseImage(&temp32_upper);
		cvReleaseImage(&under127);
		cvReleaseImage(&upper127);
		cvReleaseImage(&B1);
		cvReleaseImage(&G1);
		cvReleaseImage(&R1);
		cvReleaseImage(&B2);
		cvReleaseImage(&G2);
		cvReleaseImage(&R2);
		cvReleaseImage(&upperB127);
		cvReleaseImage(&upperG127);
		cvReleaseImage(&upperR127);
		cvReleaseImage(&underB127);
		cvReleaseImage(&underG127);
		cvReleaseImage(&underR127);
		cvReleaseImage(&maskB);
		cvReleaseImage(&maskG);
		cvReleaseImage(&maskR);
		cvReleaseImage(&dstB);
		cvReleaseImage(&dstG);
		cvReleaseImage(&dstR);
		cvReleaseImage(&temp1);
		cvReleaseImage(&temp2);
		cvReleaseImage(&temp127);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall hardMix(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//A<1-B: C=0
		//A>1-B: C=1
		//inverse img2 = 1-B
		unsigned char lut[256];
		CvMat *lut_mat;
		lut_mat = cvCreateMatHeader(1, 256, CV_8UC1);
		for (int i = 0; i < 256; i++)
			lut[i] = 255 - i;
		cvSetData(lut_mat, lut, 0);
		cvLUT(img2, img2, lut_mat);


		IplImage *B1 = cvCreateImage(cvGetSize(img1), img1->depth, 1);
		IplImage *G1 = cvCloneImage(B1);
		IplImage *R1 = cvCloneImage(B1);
		IplImage *B2 = cvCloneImage(B1);
		IplImage *G2 = cvCloneImage(B1);
		IplImage *R2 = cvCloneImage(B1);
		IplImage *maskB = cvCloneImage(B1);
		IplImage *maskG = cvCloneImage(B1);
		IplImage *maskR = cvCloneImage(B1);
		IplImage *dstB = cvCloneImage(B1);
		IplImage *dstG = cvCloneImage(B1);
		IplImage *dstR = cvCloneImage(B1);
		IplImage *srcB = cvCloneImage(B1);
		IplImage *srcG = cvCloneImage(B1);
		IplImage *srcR = cvCloneImage(B1);
		IplImage *temp1 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		IplImage *temp2 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
		
		cvSplit(img1, B1, G1, R1, 0);
		cvSplit(img2, B2, G2, R2, 0);//inversed

		cvZero(srcB);
		cvZero(srcG);
		cvZero(srcR);
		cvSet(dstB, cvScalar(255));
		cvSet(dstG, cvScalar(255));
		cvSet(dstR, cvScalar(255));

		//A<B, 255=>B>A, 0=>A>B
		cvCmp(B1, B2, maskB, CV_CMP_LT);
		cvCmp(G1, G2, maskG, CV_CMP_LT);
		cvCmp(R1, R2, maskR, CV_CMP_LT);

		//C=0
		cvCopy(srcB, dstB, maskB);
		cvCopy(srcG, dstG, maskG);
		cvCopy(srcR, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp1);
		
		cvZero(maskB);
		cvZero(maskG);
		cvZero(maskR);
		cvZero(dstB);
		cvZero(dstG);
		cvZero(dstR);
		cvSet(srcB, cvScalar(255));
		cvSet(srcG, cvScalar(255));
		cvSet(srcR, cvScalar(255));
		//A>B
		cvCmp(B1, B2, maskB, CV_CMP_GT);
		cvCmp(G1, G2, maskG, CV_CMP_GT);
		cvCmp(R1, R2, maskR, CV_CMP_GT);

		//C=1
		cvCopy(srcB, dstB, maskB);
		cvCopy(srcG, dstG, maskG);
		cvCopy(srcR, dstR, maskR);
		cvMerge(dstB, dstG, dstR, 0, temp2);

		cvAdd(temp1, temp2, temp1);
		
		cvSaveImage(outputPath, temp1);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&B1);
		cvReleaseImage(&G1);
		cvReleaseImage(&R1);
		cvReleaseImage(&B2);
		cvReleaseImage(&G2);
		cvReleaseImage(&R2);
		cvReleaseImage(&maskB);
		cvReleaseImage(&maskG);
		cvReleaseImage(&maskR);
		cvReleaseImage(&dstB);
		cvReleaseImage(&dstG);
		cvReleaseImage(&dstR);
		cvReleaseImage(&srcB);
		cvReleaseImage(&srcG);
		cvReleaseImage(&srcR);
		cvReleaseImage(&temp1);
		cvReleaseImage(&temp2);
		cvReleaseMat(&lut_mat);

		return true;
	}//end else
	return false;
}

__declspec(dllexport)bool _stdcall exclusion(LPWSTR csInputPath1, LPWSTR csInputPath2, LPWSTR csOutputPath)
{
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return false;
	if(img1->depth != IPL_DEPTH_8U || img2->depth != IPL_DEPTH_8U)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		img1 = cvLoadImage(inputPath1, 1);
		img2 = cvLoadImage(inputPath2, 1);
	}//end if
	if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
	{
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		return false;
	}//end if
	else
	{
		//C=A+B-2*A*B
		IplImage *floatingImg1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, img1->nChannels);
		IplImage *floatingImg2 = cvCloneImage(floatingImg1);
		IplImage *temp32 = cvCloneImage(floatingImg1);

		cvConvertScale(img1, floatingImg1, 1/255.);
		cvConvertScale(img2, floatingImg2, 1/255.);

		cvMul(floatingImg1, floatingImg2, temp32, 2);//2*A*B
		cvSub(floatingImg1, temp32, temp32);//A-2*A*B
		cvAdd(temp32, floatingImg2, temp32);//A-2*A*B+B
		cvConvertScale(temp32, img1, 255);
		
		cvSaveImage(outputPath, img1);
		
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&floatingImg1);
		cvReleaseImage(&floatingImg2);
		cvReleaseImage(&temp32);

		return true;
	}//end else
	return false;
}

double _stdcall PSNR(LPWSTR csInputPath1, LPWSTR csInputPath2)
{
	
	char inputPath1[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath1, -1, inputPath1, SIZE, NULL, NULL);//wchar_t * to char
	char inputPath2[SIZE] = "";
	WideCharToMultiByte(950, 0, csInputPath2, -1, inputPath2, SIZE, NULL, NULL);//wchar_t * to char *

	//load image
	IplImage *img1 = cvLoadImage(inputPath1, -1);
	IplImage *img2 = cvLoadImage(inputPath2, -1);

	if(!img1 || !img2)
		return -1.0;
	else
	{
		if (img1->nChannels != img2->nChannels || img1->height != img2->height || img1->widthStep != img2->widthStep)
		{
			cvReleaseImage(&img1);
			cvReleaseImage(&img2);
			return 0.;
		}//end if

		double MSE = .0;
		for (int i = 0 ; i < img1->height ; i++)
			for (int j = 0 ; j < img1->widthStep ; j++)
				MSE += (img1->imageData[i * img1->widthStep + j] - img2->imageData[i * img2->widthStep + j]) * (img1->imageData[i * img1->widthStep + j] - img2->imageData[i * img2->widthStep + j]);
		return 20. * log10(255. / sqrt(MSE / img1->height / img1->widthStep) );
	}//end else
}//end PSNR

LPWSTR _stdcall getFilterName(void)
{
	return _T("基本圖檔運算");
}//end getFIlterName