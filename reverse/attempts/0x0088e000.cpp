// _Rva0088E000DialogProc@16
// partial score=0.97 date=2026-09-08
// cl: /DNDEBUG /MD /EHs-c- /Oy-
// Clean C++ conversion of the debug dialog procedure at retail 0x0088E000.

typedef void *HWND;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef int INT_PTR;

extern "C" __declspec(dllimport) HWND __stdcall GetDlgItem(HWND, int);
extern "C" __declspec(dllimport) int __stdcall ShowWindow(HWND, int);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextA(HWND, const char *);
extern "C" __declspec(dllimport) long __stdcall SendDlgItemMessageA(
	HWND, int, UINT, WPARAM, LPARAM);
extern "C" __declspec(dllimport) int __stdcall EndDialog(HWND, INT_PTR);

extern bool Rva0088EAF0IsDebuggerPresent(void);
extern const char *g_rva0088E000WindowText;
extern const char *g_rva0088E000MessageText;

enum
{
	WM_INITDIALOG = 0x0110,
	WM_COMMAND = 0x0111
};

// _Rva0088E000DialogProc@16
extern "C" INT_PTR __stdcall Rva0088E000DialogProc(
	HWND hDlg, UINT message, WPARAM wParam, LPARAM)
{
	int messageOffset = (int)message - WM_INITDIALOG;
	if (messageOffset != 0)
	{
		--messageOffset;
		if (messageOffset == 0)
		{
			unsigned short command = (unsigned short)wParam;
			if (command == 1 || command == 2 || command == 3 ||
				command == 5 || command == 7)
				EndDialog(hDlg, command);
		}
		return 0;
	}

	if (!Rva0088EAF0IsDebuggerPresent())
		ShowWindow(GetDlgItem(hDlg, 2), 0);

	SetWindowTextA(hDlg, g_rva0088E000WindowText);
	SendDlgItemMessageA(hDlg, 100, 12, 0, (LPARAM)g_rva0088E000MessageText);
	return 1;
}
