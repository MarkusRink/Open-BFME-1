// ??0BfmeRecordXB@@QAE@HHH@Z
// partial score=0.99 date=2026-09-08
// pins needed (CRLF, append to reverse/symbols.csv):
//   ?bfmeLookupXB@BfmeGameXB@@QAEPAVBfmeEntryXB@@PBVBFMERetailAsciiString@@@Z,0x00032C86
//   _bfmeVftXB,0x00D16D64
//   _bfmeNamesXB,0x00EAA020
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufXB;

private:
	void releaseBuffer();
};

struct BfmeSlotJA
{
	unsigned char m_bfmeHeadJA[0xc];
	int m_bfme0CJA;
};

class BfmeHookJA
{
public:
	BfmeSlotJA *bfmeCallJA();
};

class BfmeEntryXB
{
public:
	void *m_bfme00XB;
	BfmeHookJA *m_bfme04XB;
	unsigned char m_bfme08XB[4];
	int m_bfme0CXB;
};

class BfmeGameXB
{
public:
	BfmeEntryXB *bfmeLookupXB(const BFMERetailAsciiString *name);
};

extern "C" BfmeGameXB *g_bfmeGameCW;
extern "C" unsigned char bfmeVftXB[];
extern "C" const char *bfmeNamesXB[];

static __forceinline BfmeSlotJA *bfmeResolveXB(BfmeEntryXB *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04XB == 0)
		return (BfmeSlotJA *)p;

	return p->m_bfme04XB->bfmeCallJA();
}

class BfmeRecordXB
{
public:
	BfmeRecordXB(int which, int first, int second);

	void *volatile m_bfmeVfXB;
	BfmeEntryXB *volatile m_bfme04XB;
	int m_bfme08XB;
	volatile int m_bfme0CXB;
	char m_bfme10XB;
	unsigned char m_bfme11XB[3];
	int m_bfme14XB;
	int m_bfme18XB;
	int m_bfme1CXB;
	int m_bfme20XB;
};

BfmeRecordXB::BfmeRecordXB(int which, int first, int second)
{
	m_bfmeVfXB = bfmeVftXB;
	m_bfme04XB = 0;
	m_bfme08XB = second;
	m_bfme0CXB = first;
	m_bfme10XB = 0;
	m_bfme14XB = 0;
	m_bfme18XB = 0;
	m_bfme1CXB = 0;
	m_bfme20XB = 0;

	{
		BFMERetailAsciiString name(bfmeNamesXB[which]);

		const BFMERetailAsciiString *np = &name;

		BfmeGameXB *g = g_bfmeGameCW;

		*(BfmeEntryXB **)&m_bfme04XB = g->bfmeLookupXB(np);
	}

	if (bfmeResolveXB(m_bfme04XB)->m_bfme0CJA == 0)
		m_bfme20XB = 5;
}
