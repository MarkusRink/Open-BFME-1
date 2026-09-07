// ?bfmePushXN@BfmeOwnerXN@@QAEXPAVBfmeItemXN@@@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 87/86. Inline vector push_back: placement new (its null check is the
// test eax,eax) plus the grow call when end == cap. The whole copy block, the
// vftable store, the 0x10 increment and the five-argument grow call all match.
// Residue is a register permutation plus its one-byte cost:
//   retail  vec=ecx (add ecx,0xa8 -- `this` is dead), value=esi pushed and
//           popped *inside* the copy block only, cap in edx
//   MSVC    vec=esi (lea esi,[ecx+0xa8], push esi in the prologue), value=ecx,
//           cap folded into `cmp eax,[ecx+0xb0]` -- that fold is the extra byte
// Hoisting end, cap and vec into locals in retail's order does make MSVC
// materialise the vector pointer, but as lea/esi rather than add/ecx.
// Inverting the guard polarity does not help (28 diff lines vs 27); the one-byte
// size gap shifts every later address so the raw diff count is not a useful score.
// The grow call's third argument is &value, the parameter home slot
// ([[param-slot-is-the-buffer]]); the fourth and fifth are literal 1s.
extern "C" void *bfmeVftXN[];

inline void *__cdecl operator new(unsigned int size, void *place)
{
	return place;
}

class BfmeItemXN
{
public:
	BfmeItemXN(const BfmeItemXN &other)
	{
		m_bfmeVfptrXN = bfmeVftXN;
		m_bfmeAXN = other.m_bfmeAXN;
		m_bfmeBXN = other.m_bfmeBXN;
		m_bfmeCXN = other.m_bfmeCXN;
	}

	void *m_bfmeVfptrXN;
	int m_bfmeAXN;
	unsigned char m_bfmeBXN;
	unsigned char m_bfmePadXN[3];
	int m_bfmeCXN;
};

class BfmeVecXN
{
public:
	void bfmeGrowXN(BfmeItemXN *where, BfmeItemXN *value, BfmeItemXN **slot, int a, int b);

	BfmeItemXN *m_bfmeBeginXN;
	BfmeItemXN *m_bfmeEndXN;
	BfmeItemXN *m_bfmeCapXN;
};

class BfmeOwnerXN
{
public:
	void bfmePushXN(BfmeItemXN *value);

	unsigned char m_bfmeHeadXN[0xa8];
	BfmeVecXN m_bfmeVecXN;
};

void BfmeOwnerXN::bfmePushXN(BfmeItemXN *value)
{
	BfmeItemXN *end = m_bfmeVecXN.m_bfmeEndXN;
	BfmeItemXN *cap = m_bfmeVecXN.m_bfmeCapXN;
	BfmeVecXN *vec = &m_bfmeVecXN;

	if (end != cap)
	{
		new (end) BfmeItemXN(*value);
		++vec->m_bfmeEndXN;
	}
	else
	{
		vec->bfmeGrowXN(end, value, &value, 1, 1);
	}
}
