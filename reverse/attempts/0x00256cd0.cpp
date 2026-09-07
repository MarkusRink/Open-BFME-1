// ?bfmeSetTimeCG@BfmeHostCG@@QAEXI@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 60/63. Shape, both call sites, the 0x3fffffff sentinel and the shared final
// ret all match. The gap is a register choice with a size consequence: retail
// puts the sub pointer in EDX (`mov edx,[ecx+8]`), which leaves it short of
// scratch registers in the subtract arm and forces a shrink-wrapped
// `push esi / mov esi,[TheBfmeGameLogic] / sub eax,[esi+0x3c] / pop esi`.
// MSVC reuses ECX for the sub (it already holds `this`, which dies), so edx
// stays free and the save/restore disappears -- 3 bytes short.
// Tried: naming the logic global in a local inside the arm. No change.
// To crack this, find a spelling that keeps `this` live past the m_8 load so
// ecx cannot be recycled.
class BfmeSubCG
{
public:
	unsigned char m_bfmeHeadCG[0x90];
	unsigned char m_bfmeFlagsCG;
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadCG[0x3c];
	unsigned int m_bfmeFrameCG;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

extern "C" void __stdcall bfmeApplyCG(BfmeSubCG *sub, unsigned int when);

class BfmeHostCG
{
public:
	void bfmeSetTimeCG(unsigned int when);

	unsigned char m_bfmeHeadCG[8];
	BfmeSubCG *m_bfmeSubCG;
};

void BfmeHostCG::bfmeSetTimeCG(unsigned int when)
{
	BfmeSubCG *sub = m_bfmeSubCG;

	if ((sub->m_bfmeFlagsCG & 1) == 0)
	{
		if (when != 0 && when != 0x3fffffff)
			bfmeApplyCG(sub, when - TheBfmeGameLogic->m_bfmeFrameCG);
		else
			bfmeApplyCG(sub, 0x3fffffff);
	}
}
