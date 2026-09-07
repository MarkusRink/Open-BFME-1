// ?bfmeShowLK@@YGXPAVBfmeHolderLK@@@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 72/75 bytes. Structure is exact: four byte tests short-circuiting to a
// shared true arm, the handle read from the same object in both arms, and an
// `ff 15` DLL import called with (handle, flag) -- so it needs
// `extern "C" __declspec(dllimport) void __stdcall f(void *, int);` plus an
// `__imp__f@8` pin.
// Residue (3 bytes): retail materialises the bool in the FULL register --
// `xor ecx,ecx` and `mov ecx,1` -- then still `movzx ecx,cl` before pushing;
// MSVC uses `xor cl,cl` / `mov cl,1`.
// Tried: int flag (69), unsigned char flag (72), a bool second parameter on
// the import (62), and /G7 (68) /G6 /GB /Ot (72).
extern "C" __declspec(dllimport) void __stdcall bfmeApiLK(void *handle, int flag);

class BfmeThingLK
{
public:
	unsigned char m_bfmeHeadLK[8];
	void *m_bfmeHandleLK;
	unsigned char m_bfmeGapLK[0x2d];
	char m_bfmeALK;
	char m_bfmeBLK;
	char m_bfmeCLK;
	char m_bfmeDLK;
};

class BfmeHolderLK
{
public:
	BfmeThingLK *m_bfmeThingLK;
};

void __stdcall bfmeShowLK(BfmeHolderLK *holder)
{
	BfmeThingLK *thing = holder->m_bfmeThingLK;
	bool flag = thing->m_bfmeALK || thing->m_bfmeBLK || thing->m_bfmeCLK || thing->m_bfmeDLK;

	bfmeApiLK(thing->m_bfmeHandleLK, flag);
}
