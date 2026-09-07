// ?bfmeSetEQU@BfmeHolderEQU@@QAEXVBfmePtrEQU@@H@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 162/166. Ref-counted smart-pointer assignment: a by-value BfmePtrEQU
// parameter, an inlined operator= with the &dest != &src self-check, an
// InterlockedIncrement addRef, an InterlockedDecrement release of the old
// pointee, the store, the m_23c store, then the by-value parameter's own
// destructor. Pins wanted: __imp__bfmeIncEQU@4 -> 0x00F58E5C and
// __imp__bfmeDecEQU@4 -> 0x00F58E54 (removed from symbols.csv while unused).
//
// Single residue, 4 bytes: retail keeps a SECOND null test of the old
// pointee between the InterlockedDecrement and the virtual drop call
//     test esi,esi / je / mov eax,[esi] / push 1 / mov ecx,esi / call [eax]
// while MSVC folds it against the identical test three instructions earlier.
// The by-value parameter's own release, further down, has exactly one test in
// BOTH builds -- so this is MSVC pass-ordering, not a spelling: the same
// source construct folded in one expansion and not the other.
// Ruled out: free-function helper with if (p); member helper with if (this);
// nested ifs instead of an && chain; naming the destination in a local;
// /Ob1 /Og /G7 /Oy- (all 162). The esi/edi swap on &m_238 vs the old pointee
// follows from the shorter live range and should settle with the null test.
extern "C" __declspec(dllimport) long __stdcall bfmeIncEQU(long *p);
extern "C" __declspec(dllimport) long __stdcall bfmeDecEQU(long *p);

class BfmeObjEQU
{
public:
	virtual void bfmeDropEQU(int flag);

	void bfmeKillEQU()
	{
		if (this)
			bfmeDropEQU(1);
	}

	void bfmeReleaseEQU()
	{
		if (this && bfmeDecEQU(&m_bfmeRefEQU) <= 0)
			bfmeKillEQU();
	}

	long m_bfmeRefEQU;
};

class BfmePtrEQU
{
public:
	BfmePtrEQU(const BfmePtrEQU &other);

	~BfmePtrEQU() { m_bfmeObjEQU->bfmeReleaseEQU(); }

	BfmePtrEQU &operator=(const BfmePtrEQU &other)
	{
		if (this != &other)
		{
			BfmeObjEQU *p = other.m_bfmeObjEQU;

			if (p)
				bfmeIncEQU(&p->m_bfmeRefEQU);

			m_bfmeObjEQU->bfmeReleaseEQU();
			m_bfmeObjEQU = p;
		}

		return *this;
	}

	BfmeObjEQU *m_bfmeObjEQU;
};

class BfmeHolderEQU
{
public:
	void bfmeSetEQU(BfmePtrEQU src, int extra);

	unsigned char m_bfmeHeadEQU[0x238];
	BfmePtrEQU m_bfmePtrEQU;
	int m_bfmeExtraEQU;
};

void BfmeHolderEQU::bfmeSetEQU(BfmePtrEQU src, int extra)
{
	m_bfmePtrEQU = src;
	m_bfmeExtraEQU = extra;
}
