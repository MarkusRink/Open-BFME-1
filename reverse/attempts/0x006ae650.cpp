// ?d_006ae650@@YAXXZ
// partial score=0.9 date=2026-09-08
__declspec(dllimport) void __stdcall bfmeClose1012(void *h);
__declspec(dllimport) int __stdcall bfmeWait1012(void *h, int t);

class BfmeLockTM
{
public:
	__forceinline BfmeLockTM(void *h)
	{
		m_bfmeOkTM = 0;
		m_bfmeHandleTM = h;

		if (bfmeWait1012(h, -1) != 0x102)
			m_bfmeOkTM = 1;
	}

	__forceinline ~BfmeLockTM()
	{
		if (m_bfmeOkTM)
			bfmeClose1012(m_bfmeHandleTM);
	}

	void *m_bfmeHandleTM;
	char m_bfmeOkTM;
};

struct BfmeOutTM
{
	int m_bfmeATM;
	int m_bfmeBTM;
};

class BfmeSlotTM
{
public:
	void bfmeFillTM(BfmeOutTM *out, int key);

	unsigned char m_bfmeBodyTM[0xc];
};

class BfmeHostTM
{
public:
	virtual void bfmeSlot00TM();
	virtual void bfmeSlot01TM();
	virtual void bfmeSlot02TM();
	virtual void bfmeSlot03TM();
	virtual void bfmeSlot04TM();
	virtual void bfmeSlot05TM();
	virtual void bfmeSlot06TM();
	virtual void bfmeSlot07TM();
	virtual void bfmeSlot08TM();
	virtual void bfmeSlot09TM();
	virtual void bfmeSlot10TM();
	virtual void bfmeSlot11TM();
	virtual void bfmeSlot12TM();
	virtual void bfmeSlot13TM();
	virtual void bfmeSlot14TM();
	virtual void bfmeSlot15TM();
	virtual void bfmeSlot16TM();
	virtual void bfmeSlot17TM();
	virtual void bfmeStepTM(int a, int b);

	void bfmeRunTM(int a, int b);

	unsigned char m_bfmeHeadTM[0x958];
	void *m_bfmeMutexTM;
	BfmeSlotTM m_bfmeArrTM[4];
};

void BfmeHostTM::bfmeRunTM(int a, int b)
{
	BfmeLockTM lock(m_bfmeMutexTM);

	bfmeStepTM(a, b);

	BfmeOutTM out;

	m_bfmeArrTM[b].bfmeFillTM(&out, a);
}
