#include <Windows.h>
#include <tchar.h>
extern "C"
{
	__declspec(dllexport)LPWSTR _stdcall getPassword(void);
}//end extern "C"

LPWSTR _stdcall getPassword(void)
{
	return _T("�ʶǤj�Ǹ�T�Ǽ��u�{�Ǩt01160032-01160315-01160554-01160714");
}//end getFIlterName