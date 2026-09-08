// ?bfmeRefreshZR@BfmeHostZR@@QAEXABV?$StringBase@D@@@Z
// partial score=0.96 date=2026-09-08
extern "C" void *__cdecl memset(void *d, int c, unsigned int n);
#pragma intrinsic(memset)

template <class T>
class StringBase
{
public:
	void *m_bfmeStrZR;
};

class Rva006AEE00Tree
{
public:
	struct InsertResult
	{
		void *m_bfmeNodeZR;
		char m_bfmeOkZR;
		unsigned char m_bfmePadZR[3];
	};

	void insert_unique(InsertResult *out, const StringBase<char> &key);
};

class BfmeHostZR
{
public:
	void bfmeRefreshZR(const StringBase<char> &name);

	unsigned char m_bfmeHeadZR[0x9c];
	unsigned int m_bfme9CZR;
	Rva006AEE00Tree m_bfmeA0ZR;
	unsigned char m_bfmeGapZR[0xe7];
	unsigned char m_bfme188ZR[48];
};

void BfmeHostZR::bfmeRefreshZR(const StringBase<char> &name)
{
	Rva006AEE00Tree::InsertResult r;

	m_bfmeA0ZR.insert_unique(&r, name);

	if (r.m_bfmeOkZR && m_bfme9CZR != 0x3f800000)
		memset(m_bfme188ZR, 2, 48);
}
