// ?bfmeSetAI@BfmeOwnerAI@@QAEXPAPAVBfmeThingAI@@@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 94/94 bytes, every instruction and every branch displacement identical; the
// ONLY residue is that retail puts p in esi and this in edi while MSVC picks
// the opposite pair (and so saves edi one instruction earlier).
// Levers tried, all insensitive or worse:
//   - naming this in a local (before AND after p): identical output
//   - naming &m_bfmePtrAI in a `slot` local after p: identical; before p: 92 B
//   - respelling *src instead of a p local: loses ebx for src, 4 diffs
// The redundant `test esi,esi` before the deleting-dtor call is NOT recoverable
// from a nested `if (old != 0)` nor from `delete old` -- MSVC folds both away.
// It comes from releasing through the slot pointer (bfmeReleaseAI below): the
// call in between stops MSVC proving *slot still non-null, so the test stays.
extern "C" long (__stdcall *g_bfmeIncAI)(long *value);
extern "C" long (__stdcall *g_bfmeDecAI)(long *value);

class BfmeSubAI
{
public:
	int bfmeCheckAI(void *tag);
};

class BfmeThingAI
{
public:
	virtual ~BfmeThingAI();

	long m_bfmeRefAI;
	BfmeSubAI m_bfmeSubAI;
};

class BfmeOwnerAI
{
public:
	void bfmeSetAI(BfmeThingAI **src);

	unsigned char m_bfmeHeadAI[8];
	BfmeThingAI *m_bfmePtrAI;
	unsigned char m_bfmeMidAI[8];
	unsigned char m_bfmeTagAI[4];
};

static inline void bfmeReleaseAI(BfmeThingAI **slot)
{
	if (*slot != 0 && (*g_bfmeDecAI)(&(*slot)->m_bfmeRefAI) <= 0)
		delete *slot;
}

void BfmeOwnerAI::bfmeSetAI(BfmeThingAI **src)
{
	BfmeThingAI *p = *src;

	if (p != 0 && p->m_bfmeSubAI.bfmeCheckAI(m_bfmeTagAI) != 0)
		return;

	BfmeThingAI **slot = &m_bfmePtrAI;

	if (slot == src)
		return;

	if (p != 0)
		(*g_bfmeIncAI)(&p->m_bfmeRefAI);

	bfmeReleaseAI(slot);

	*slot = *src;
}
