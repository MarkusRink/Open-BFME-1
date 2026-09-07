// ?bfmePruneAJ@BfmeOwnerAJ@@QAEXXZ (identity unknown)
// partial score=0.9 date=2026-09-07
// 92/94. Vector-of-pointers prune: delete the flagged element, memmove the tail
// down and drop the end pointer; otherwise release the link and step. Every
// instruction of the loop body matches retail one-for-one, including the
// second induction pointer `next` (ebx) that feeds the memmove size.
// Two residues, both in the pre-header:
//   * retail materialises m_bfmeEndAJ into eax (mov eax,[ebp+0xc] / cmp edi,eax)
//     where MSVC folds it (cmp reg,[ebp+0xc]) -- exactly the 2 missing bytes.
//     Tried: guard on the members directly, guard on the `it` local, both
//     operand orders, while/do-while/for rotations, and a volatile cast on the
//     end load. All produce the identical 92-byte form.
//   * callee-saved allocation: retail ebp/edi/ebx/esi = this/it/next/p,
//     MSVC ebx/ebp/esi/edi = it/this/p/next.
extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *dst, const void *src, unsigned int count);

class BfmeLinkAJ
{
public:
	BfmeLinkAJ *bfmeReleaseAJ();
};

class BfmeItemAJ
{
public:
	virtual ~BfmeItemAJ();

	BfmeLinkAJ *m_bfmeLinkAJ;
	char m_bfmeDeadAJ;
};

class BfmeOwnerAJ
{
public:
	void bfmePruneAJ();

	unsigned char m_bfmeHeadAJ[8];
	BfmeItemAJ **m_bfmeBeginAJ;
	BfmeItemAJ **m_bfmeEndAJ;
};

void BfmeOwnerAJ::bfmePruneAJ()
{
	if (m_bfmeEndAJ == m_bfmeBeginAJ)
		return;

	BfmeItemAJ **it = m_bfmeBeginAJ;
	BfmeItemAJ **next = it + 1;

	do
	{
		BfmeItemAJ *p = *it;

		if (p->m_bfmeDeadAJ != 0)
		{
			delete p;

			if (next != m_bfmeEndAJ)
				BfmeMemMove(it, next, (char *)m_bfmeEndAJ - (char *)next);

			m_bfmeEndAJ--;
		}
		else
		{
			if (p->m_bfmeLinkAJ != 0)
				p->m_bfmeLinkAJ = p->m_bfmeLinkAJ->bfmeReleaseAJ();

			it++;
			next++;
		}
	}
	while (it != m_bfmeEndAJ);
}
