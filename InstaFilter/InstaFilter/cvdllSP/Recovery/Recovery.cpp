#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
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

	FILE *input = fopen(inputPath, "rb+");
    
	if(!input)
		return false;

	bool found = false;
	//find ID : Copyright, Qbsuran Alang
	while(!feof(input))
		//Copyright 
		if(fgetc(input) == 'C' && fgetc(input) == 'o' && fgetc(input) == 'p' &&
			fgetc(input) == 'y' && fgetc(input) == 'r' && fgetc(input) == 'i' &&
			fgetc(input) == 'g' && fgetc(input) == 'h' && fgetc(input) == 't' &&
			fgetc(input) == ',' && fgetc(input) == ' ' &&
			//Qbsuran Alang 
			fgetc(input) == 'Q' && fgetc(input) == 'b' && fgetc(input) == 's' &&
			fgetc(input) == 'u' && fgetc(input) == 'r' && fgetc(input) == 'a' &&
			fgetc(input) == 'n' && fgetc(input) == ' ' && fgetc(input) == 'A' &&
			fgetc(input) == 'l' && fgetc(input) == 'a' && fgetc(input) == 'n' &&
			fgetc(input) == 'g' )
		{ found = true; break; }//end if
    
	if(!found)
	{
		fclose(input);
		return false;
	}//end if

	//ID location found
	FILE *output = fopen(outputPath, "wb+");
	
	if(!output)
	{
		fclose(input);
		return false;
	}//end if

	while(!feof(input))
		fputc(fgetc(input), output);

	fclose(input);
	fclose(output);

	return true;
}//end opencvProcess

LPWSTR _stdcall getFilterName(void)
{
	return _T("備份影像");
}//end getFIlterName