// ?bfmeTakeABC@BfmeHolderABC@@QAEXUBfmeIterABB@@@Z
// partial score=0.84 date=2026-09-08
struct BfmeNodeABB
{
	unsigned char m_bfmeHeadABB[0x14];
	void *m_bfme14ABB;
};

struct BfmeIterABB
{
	BfmeNodeABB *m_bfmeNodeABB;
};

class BfmeSubABB
{
public:
	void bfmeRangeABB(BfmeIterABB *first, BfmeIterABB *last);

	BfmeNodeABB *m_bfmeHeadABB;
};

BfmeNodeABB *__stdcall bfmeDiagABB(BfmeIterABB *it, const void *desc);

extern void *const g_bfmeDescABB;

class BfmeHolderABC
{
public:
	void bfmeTakeABC(BfmeIterABB last);

	unsigned char m_bfmeHeadHABC[4];
	BfmeSubABB m_bfme04ABC;
	unsigned char m_bfmeGapABC[0x18 - 8];
	BfmeNodeABB *m_bfme18ABC;
};

void BfmeHolderABC::bfmeTakeABC(BfmeIterABB last)
{
	BfmeIterABB first;

	m_bfme04ABC.bfmeRangeABB(&first, &last);

	if (first.m_bfmeNodeABB == m_bfme04ABC.m_bfmeHeadABB)
	{
		last.m_bfmeNodeABB = (BfmeNodeABB *)0xdead0003;
		bfmeDiagABB(&last, &g_bfmeDescABB);
	}

	m_bfme18ABC = last.m_bfmeNodeABB;
}
