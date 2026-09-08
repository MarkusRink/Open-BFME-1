// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail 0x006BAC30.  This is the Win32GameEngine implementation from the
// upstream GameEngineDevice Win32 common source.  The service slot is the
// sixteenth inherited GameEngine slot (+0x40) in the BFME vtable.

#include <windows.h>

#define BFME_GAME_ENGINE_SLOT(n) virtual void slot##n() = 0;

class Win32GameEngine
{
public:
	BFME_GAME_ENGINE_SLOT(0)
	BFME_GAME_ENGINE_SLOT(1)
	BFME_GAME_ENGINE_SLOT(2)
	BFME_GAME_ENGINE_SLOT(3)
	BFME_GAME_ENGINE_SLOT(4)
	BFME_GAME_ENGINE_SLOT(5)
	BFME_GAME_ENGINE_SLOT(6)
	BFME_GAME_ENGINE_SLOT(7)
	BFME_GAME_ENGINE_SLOT(8)
	BFME_GAME_ENGINE_SLOT(9)
	BFME_GAME_ENGINE_SLOT(10)
	BFME_GAME_ENGINE_SLOT(11)
	BFME_GAME_ENGINE_SLOT(12)
	BFME_GAME_ENGINE_SLOT(13)
	BFME_GAME_ENGINE_SLOT(14)
	BFME_GAME_ENGINE_SLOT(15)
	virtual void serviceWindowsOS();
};

#undef BFME_GAME_ENGINE_SLOT

extern DWORD TheMessageTime;

void Win32GameEngine::serviceWindowsOS(void)
{
	MSG msg;
	int returnValue;

	while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		returnValue = GetMessage(&msg, NULL, 0, 0);
		TheMessageTime = msg.time;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		TheMessageTime = 0;
	}
}
