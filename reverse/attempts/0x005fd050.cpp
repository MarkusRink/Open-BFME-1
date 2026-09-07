// ?bfmeSaveBF@BfmeHostBF@@QAEXPAVBfmeAgentBF@@@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 161/164. Xfer-family body with TWO info blocks (one in the `push ecx` slot,
// one in the dead parameter home slot), both {1,1} and both ignored, then eight
// member visits. Everything matches except that the member at +0x34 is visited
// TWICE: retail recomputes `lea eax,[edi+0x34]` at both call sites, MSVC CSEs
// the address into ebx and pushes the register the second time (-3 bytes).
// The constant 1 lives in bl across both fill calls in BOTH builds; retail's
// allocator simply never reuses ebx afterwards, MSVC does.
// Tried: splitting the member into two names with a union at the same offset
// (address value is identical, CSE still fires). Nothing syntactic reaches a
// value-based CSE -- this needs the allocator to leave ebx alone.
struct BfmeInfoBF
{
	unsigned char m_bfmeFlagBF;
	unsigned char m_bfmeLevelBF;
};

class BfmeAgentBF
{
public:
	virtual void bfmeSlot00BF();
	virtual void bfmeSlot01BF();
	virtual void bfmeSlot02BF();
	virtual void bfmeSlot03BF();
	virtual void bfmeSlot04BF();
	virtual void bfmeSlot05BF();
	virtual void bfmeSlot06BF();
	virtual void bfmeSlot07BF();
	virtual void bfmeSlot08BF();
	virtual void bfmeSlot09BF();
	virtual void bfmeFillBF(BfmeInfoBF *info);
	virtual void bfmeSlot11BF();
	virtual void bfmeSlot12BF();
	virtual void bfmeSlot13BF();
	virtual void bfmeSlot14BF();
	virtual void bfmeSlot15BF();
	virtual void bfmeSlot16BF();
	virtual void bfmeSlot17BF();
	virtual void bfmeSlot18BF();
	virtual void bfmeSlot19BF();
	virtual void bfmeSlot20BF();
	virtual void bfmeSlot21BF();
	virtual void bfmeSlot22BF();
	virtual void bfmeSlot23BF();
	virtual void bfmeSlot24BF();
	virtual void bfmeSlot25BF();
	virtual void bfmeMarkBF(void *dst);
	virtual void bfmeSlot27BF();
	virtual void bfmeSlot28BF();
	virtual void bfmeWordBF(void *dst);
	virtual void bfmeSlot30BF();
	virtual void bfmeSlot31BF();
	virtual void bfmeSlot32BF();
	virtual void bfmeSlot33BF();
	virtual void bfmeSlot34BF();
	virtual void bfmeByteBF(unsigned char *dst);
};

extern "C" void __cdecl bfmeXferBF(BfmeAgentBF *ag, void *dst);

class BfmeHostBF
{
public:
	void bfmeSaveBF(BfmeAgentBF *ag);

	unsigned char m_bfmeHeadBF[0x1c];
	unsigned char m_bfmeSlotABF;
	unsigned char m_bfmeSlotBBF;
	unsigned char m_bfmePadOneBF[6];
	unsigned char m_bfmeSlotCBF[4];
	unsigned char m_bfmeSlotDBF[4];
	unsigned char m_bfmePadTwoBF[8];
	union
	{
		unsigned char m_bfmeSlotEBF;
		unsigned char m_bfmeSlotE2BF;
	};
	unsigned char m_bfmePadThreeBF[7];
	unsigned char m_bfmeSlotFBF[4];
	unsigned char m_bfmeSlotGBF;
};

void BfmeHostBF::bfmeSaveBF(BfmeAgentBF *ag)
{
	BfmeInfoBF first;
	BfmeInfoBF second;

	first.m_bfmeFlagBF = 1;
	first.m_bfmeLevelBF = 1;
	ag->bfmeFillBF(&first);

	second.m_bfmeFlagBF = 1;
	second.m_bfmeLevelBF = 1;
	ag->bfmeFillBF(&second);

	bfmeXferBF(ag, m_bfmeSlotDBF);
	ag->bfmeMarkBF(m_bfmeSlotCBF);
	ag->bfmeByteBF(&m_bfmeSlotEBF);
	ag->bfmeByteBF(&m_bfmeSlotABF);
	ag->bfmeByteBF(&m_bfmeSlotBBF);
	ag->bfmeByteBF(&m_bfmeSlotE2BF);
	ag->bfmeByteBF(&m_bfmeSlotGBF);
	ag->bfmeWordBF(m_bfmeSlotFBF);
}
