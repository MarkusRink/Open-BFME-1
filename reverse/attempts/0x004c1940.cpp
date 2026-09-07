// ?bfmeSyncPT@@YAXXZ (identity unknown)
// partial score=0.85 date=2026-09-07
// 56/61 bytes. Control flow, both tail jmps, all four tests and the block order
// match; the five missing bytes are one register-allocation decision.
// Retail keeps the Glo012F368C pointer in eax for the whole body (so the
// receiver costs a `mov ecx,eax` and TheWritableGlobalData has to go in edx,
// 6 bytes not 5) and then loads the GlobalData byte into BL, shrink-wrapping
// `push ebx` / `pop ebx` around those two instructions. MSVC puts the pointer
// straight in ecx (it is only ever the receiver) and uses dl for the byte, so
// no save/restore and no copy.
// Tried: byte hoisted into a local at the top (worse, the load floats above the
// first guard), byte in a local scoped inside the guard, no local at all with
// the global respelled at each use, and a named local for
// TheWritableGlobalData. All four give the same 56 bytes.
class Glo012F368CType
{
public:
	void bfmeApplyPT(void);

	unsigned char m_bfmeHeadPT[0x11];
	unsigned char m_bfmeDonePT;
};

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadPT[0xbc4];
	unsigned char m_bfmeEnabledPT;
};

extern Glo012F368CType *Glo012F368C;
extern Rva006C9270GlobalData *TheWritableGlobalData;
extern unsigned char g_bfmeReadyPT;

void __cdecl bfmeIdlePT(void);

void __cdecl bfmeSyncPT(void)
{
	Glo012F368CType *target = Glo012F368C;

	if (target && target->m_bfmeDonePT)
		return;

	if (g_bfmeReadyPT && target && TheWritableGlobalData->m_bfmeEnabledPT)
		target->bfmeApplyPT();
	else
		bfmeIdlePT();
}
