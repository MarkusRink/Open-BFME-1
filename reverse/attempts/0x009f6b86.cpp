// ?bfmeAddABH@BfmeHostABH@@QAE_NPAX@Z
// partial score=0.9 date=2026-09-09
// cl: /Oy-
struct BfmeLockTEA;

extern "C" __declspec(dllimport) void __stdcall bfmeEnterTEA(BfmeLockTEA *lock);

class BfmeThingDWD
{
public:
	BfmeThingDWD(BfmeLockTEA *lock)
	{
		m_bfmeLockDWD = lock;
		bfmeEnterTEA(lock);
		m_bfmeOwnedDWD = 1;
	}

	~BfmeThingDWD() throw();

	BfmeLockTEA *m_bfmeLockDWD;
	char m_bfmeOwnedDWD;
};

class BfmeArrayABH
{
public:
	int bfmeAddABH(void *const &item) throw();
};

class BfmeHostABH
{
public:
	bool bfmeAddABH(void *item);

	unsigned char m_bfmeHeadABH[0x18];
	BfmeLockTEA *m_bfme18ABH;
	unsigned char m_bfmeGapABH[0x30 - 0x1c];
	BfmeArrayABH m_bfme30ABH;
};

bool BfmeHostABH::bfmeAddABH(void *item)
{
	BfmeThingDWD guard((BfmeLockTEA *)&m_bfme18ABH);

	return m_bfme30ABH.bfmeAddABH(item) != 0;
}
