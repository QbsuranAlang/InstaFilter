#include <Windows.h>
#include <stdio.h>
#define SIZE 256
extern "C"
{
	__declspec(dllexport)bool _stdcall combineImage(LPWSTR csOriginalPath, LPWSTR csFilterPath, LPWSTR csOutputPath);
}//end extern "C"

bool _stdcall combineImage(LPWSTR csOriginalPath, LPWSTR csFilterPath, LPWSTR csOutputPath)
{
	char originalPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOriginalPath, -1, originalPath, SIZE, NULL, NULL);//wchar_t * to char
	char filterPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csFilterPath, -1, filterPath, SIZE, NULL, NULL);//wchar_t * to char *
	char outputPath[SIZE] = "";
	WideCharToMultiByte(950, 0, csOutputPath, -1, outputPath, SIZE, NULL, NULL);//wchar_t * to char *

	FILE *original = fopen(originalPath, "rb+"); //original file
	FILE *apply = fopen(filterPath, "rb+"); //apply filter file
	FILE *combine = fopen(outputPath, "wb+"); //combine file

	if(!original || !apply || !combine)
		return false;

	//write apply file
	while(!feof(apply))
		fputc(fgetc(apply), combine);

	//ID string
	fputs("Copyright, Qbsuran Alang", combine);

	//original
	while(!feof(original))
		fputc(fgetc(original), combine);

	fclose(original);
	fclose(apply);
	fclose(combine);

	return true;
}//end combineImage