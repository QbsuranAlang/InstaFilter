#include <Windows.h>
#include <tchar.h>
extern "C"
{
	__declspec(dllexport)LPWSTR _stdcall getPassword(void);
}//end extern "C"

LPWSTR _stdcall getPassword(void)
{
	return _T("get process time\'s dll");
}//end getFIlterName