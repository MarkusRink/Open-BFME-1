// ?bfmeEraseAM@BfmeStrAM@@QAEPAV1@II@Z (identity unknown)
// partial score=0.93 date=2026-09-07
// 87/90. string::erase(pos, n): clamp n to size-pos through a reference min,
// memmove the tail (plus the terminator, hence the +1) down over the hole and
// shrink the end pointer. The first 0x28 bytes are EXACT, including
//   * the min-by-reference address select (cmp/lea/jb/lea/mov reg,[eax])
//   * retail reusing the `pos` home slot at [esp+0x10] for the clamp value
//   * the `sub edx,esi / inc edx / je` zero-length test
// Residue: retail spills the min result into ebp (push ebp .. pop ebp, 3 bytes)
// and builds last as lea esi,[ecx+edi] + add esi,ebp, where MSVC loads the min
// into the free esi and accumulates (mov esi,[eax]/add esi,ecx/add esi,edi).
// Tried: last-then-first and first-then-last declaration order, explicit
// (begin+pos)+cnt parenthesisation, and materialising the min into a named
// local first. All three give the same 86-87 byte accumulate form.
extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *dst, const void *src, unsigned int count);

static inline const unsigned int &bfmeMinAM(const unsigned int &a, const unsigned int &b)
{
	return a < b ? a : b;
}

class BfmeStrAM
{
public:
	BfmeStrAM *bfmeEraseAM(unsigned int pos, unsigned int n);

	char *m_bfmeBeginAM;
	char *m_bfmeEndAM;
};

BfmeStrAM *BfmeStrAM::bfmeEraseAM(unsigned int pos, unsigned int n)
{
	unsigned int avail = (unsigned int)(m_bfmeEndAM - m_bfmeBeginAM) - pos;
	const unsigned int &cnt = bfmeMinAM(avail, n);
	char *last = (m_bfmeBeginAM + pos) + cnt;
	char *first = m_bfmeBeginAM + pos;

	if (first != last)
	{
		unsigned int len = (unsigned int)(m_bfmeEndAM - last) + 1;

		if (len != 0)
			BfmeMemMove(first, last, len);

		m_bfmeEndAM += first - last;
	}

	return this;
}
