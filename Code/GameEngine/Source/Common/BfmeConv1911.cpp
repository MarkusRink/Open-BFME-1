class BfmeAgentBG
{
public:
	virtual void bfmeSlot00BG();
	virtual void bfmeSlot01BG();
	virtual void bfmeSlot02BG();
	virtual void bfmeSlot03BG();
	virtual void bfmeSlot04BG();
	virtual void bfmeSlot05BG();
	virtual void bfmeSlot06BG();
	virtual void bfmeSlot07BG();
	virtual void bfmeSlot08BG();
	virtual void bfmeBlockBG(void *dst, int size);
	virtual void bfmeSlot10BG();
	virtual void bfmeSlot11BG();
	virtual void bfmeSlot12BG();
	virtual void bfmeSlot13BG();
	virtual void bfmeSlot14BG();
	virtual void bfmeSlot15BG();
	virtual void bfmeSlot16BG();
	virtual void bfmeSlot17BG();
	virtual void bfmeSlot18BG();
	virtual void bfmeSlot19BG();
	virtual void bfmeSlot20BG();
	virtual void bfmeSlot21BG();
	virtual void bfmeSlot22BG();
	virtual void bfmeSlot23BG();
	virtual void bfmeSlot24BG();
	virtual void bfmeSlot25BG();
	virtual void bfmeMarkBG(void *dst);
	virtual void bfmeLateBG(void *dst);
	virtual void bfmeSlot28BG();
	virtual void bfmeSlot29BG();
	virtual void bfmeSlot30BG();
	virtual void bfmeSlot31BG();
	virtual void bfmeSlot32BG();
	virtual void bfmeSlot33BG();
	virtual void bfmeSlot34BG();
	virtual void bfmeByteBG(unsigned char *dst);
};

extern "C" void __cdecl bfmeXferOneBG(BfmeAgentBG *ag, void *dst);
extern "C" void __cdecl bfmeXferTwoBG(BfmeAgentBG *ag, void *dst);

class BfmeHostBG
{
public:
	void bfmeSaveBG(BfmeAgentBG *ag);

	unsigned char m_bfmeHeadBG[0x48];
	unsigned char m_bfmeSlotABG[4];
	unsigned char m_bfmeSlotBBG[4];
	unsigned char m_bfmePadOneBG[0x2c];
	unsigned char m_bfmeSlotCBG;
	unsigned char m_bfmeSlotDBG;
	unsigned char m_bfmeSlotEBG;
	unsigned char m_bfmePadTwoBG;
	unsigned char m_bfmeSlotFBG[4];
	unsigned char m_bfmeSlotGBG[4];
	unsigned char m_bfmeSlotHBG[4];
	unsigned char m_bfmeSlotIBG[4];
	unsigned char m_bfmeSlotJBG[4];
	unsigned char m_bfmeSlotKBG;
};

void BfmeHostBG::bfmeSaveBG(BfmeAgentBG *ag)
{
	ag->bfmeMarkBG(m_bfmeSlotHBG);

	bfmeXferOneBG(ag, m_bfmeSlotABG);
	bfmeXferTwoBG(ag, m_bfmeSlotBBG);

	ag->bfmeByteBG(&m_bfmeSlotCBG);
	ag->bfmeByteBG(&m_bfmeSlotDBG);
	ag->bfmeByteBG(&m_bfmeSlotEBG);
	ag->bfmeLateBG(m_bfmeSlotFBG);
	ag->bfmeLateBG(m_bfmeSlotGBG);
	ag->bfmeBlockBG(m_bfmeSlotIBG, 4);
	ag->bfmeBlockBG(m_bfmeSlotJBG, 4);
	ag->bfmeByteBG(&m_bfmeSlotKBG);
}
