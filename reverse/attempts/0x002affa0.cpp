// ?bfmeDropXG@BfmeOwnerXG@@QAEXPAX@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 82/82, exact size, structure and instruction count. Residue is two instances
// of [[argument-shuttle-register]]:
//   * first call: retail carries the unit argument in ecx and the holder in eax
//     (lea ecx,[eax+8]); MSVC swaps them (add ecx,8).
//   * third call: retail loads the unit into ecx, pushes the two constants, then
//     pushes it and loads TheBfmeGameLogic into ecx last; MSVC preloads the
//     receiver before the pushes.
// Naming the unit at each of the three use sites DID fix the middle hook chain
// (retail eax then ecx) -- keep that. /G7 makes it worse (9 diffs, not 8).
// this is a secondary base: every member is spelled through
// ((BfmeOuterXG *)((char *)this - 0x20)) inline; a named outer local hoists
// lea esi,[ecx-0x20] and loses retail's [esi-0x18] addressing.
class BfmeHookXG
{
public:
	void bfmeNoteXG();
};

class BfmeUnitXG
{
public:
	unsigned char m_bfmeHeadXG[0x204];
	BfmeHookXG *m_bfmeHookXG;
};

struct BfmeSubXG
{
	bool bfmeTestXG(BfmeUnitXG *unit, void *arg);
};

class BfmeHolderXG
{
public:
	void *m_bfmeFrontXG[2];
	BfmeSubXG m_bfmeSubXG;
};

class BfmeLogicXG
{
public:
	void bfmeKillXG(BfmeUnitXG *unit, int reason, int flag);
};

extern BfmeLogicXG *TheBfmeLogicXG;

class BfmeOuterXG
{
public:
	void bfmeFinishXG(void *arg);

	unsigned char m_bfmeStartXG[4];
	BfmeHolderXG *m_bfmeHolderXG;
	BfmeUnitXG *m_bfmeUnitXG;
};

class BfmeOwnerXG
{
public:
	void bfmeDropXG(void *arg);
};

void BfmeOwnerXG::bfmeDropXG(void *arg)
{
	BfmeUnitXG *unit = ((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG;

	if (((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeHolderXG->m_bfmeSubXG.bfmeTestXG(unit, arg))
	{
		BfmeUnitXG *found = ((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG;

		if (found->m_bfmeHookXG != 0)
			found->m_bfmeHookXG->bfmeNoteXG();

		BfmeUnitXG *victim = ((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG;

		TheBfmeLogicXG->bfmeKillXG(victim, 0xffff, 1);
		((BfmeOuterXG *)((char *)this - 0x20))->bfmeFinishXG(arg);
	}
}
