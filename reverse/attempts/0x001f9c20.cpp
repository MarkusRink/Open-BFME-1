// ?bfmeMaybeFW@BfmeOwnerFW@@QAEXH@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 50/50 bytes; 5 of 17 instructions differ, all from WHERE the secondary-base
// adjust lands. Retail hoists it between the flag load and its test --
//   mov al,[ecx+31h] / add ecx,-0ch / test al,al / jne
// -- so `this` is consumed in place and every later access is [ecx+4] and
// [ecx+3ch]. MSVC sinks it below the test and addresses the first member as
// [ecx-8], adjusting only later.
// Tried: declaring the base BEFORE the flag guard (MSVC then uses
// `lea eax,[ecx-0ch]`, keeps this in ecx and needs `mov ecx,eax` at the call --
// 10 diffs); respelling the cast at all three uses with no local (10 diffs);
// loading the flag into a local first, then the base (same lea form).
// The variant kept here is the closest.
struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadFW[0x6a];
	char m_bfmeBusyFW;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeThingFW
{
public:
	unsigned char m_bfmeHeadFW[0xc4];
	char m_bfmeFlagFW;
};

class BfmeBaseFW
{
public:
	void bfmeDoFW(void);

	int m_bfmeSpareFW;
	BfmeThingFW *m_bfmeThingFW;
	unsigned char m_bfmeGapFW[0x34];
	char m_bfmeOtherFW;
};

class BfmeOwnerFW
{
public:
	void bfmeMaybeFW(int unused);

	unsigned char m_bfmeHeadFW[0x31];
	char m_bfmeSkipFW;
};

void BfmeOwnerFW::bfmeMaybeFW(int unused)
{
	if (TheBfmeGameLogic->m_bfmeBusyFW != 0)
		return;

	if (m_bfmeSkipFW != 0)
		return;

	BfmeBaseFW *base = (BfmeBaseFW *)((char *)this - 0xc);

	if (base->m_bfmeThingFW->m_bfmeFlagFW != 0 || base->m_bfmeOtherFW != 0)
		base->bfmeDoFW();
}
