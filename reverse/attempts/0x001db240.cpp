// ??0BfmeNodeAL@@QAE@PAX@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 96/93. Node constructor for the same class as the landed erase at 0x001DB1C0
// (begin/end/cap/key/next): zero the three vector pointers, store the key, then
// an inlined degenerate copy of the empty range, then null the next link.
// Everything matches except ONE thing: retail reads m_bfmeEndAL once and
// compares the register with itself (3b c0 `cmp eax,eax`), where MSVC emits a
// second load. The three c7-immediate zero stores and the live-but-dead memmove
// arm both REQUIRE the pointers to be volatile -- without volatile the whole
// body folds to 25-35 bytes. But volatile also blocks the CSE of the two reads:
//   plain members                       -> 25 B (all folded)
//   zero through a char** helper        -> 25 B (alias analysis sees through it)
//   volatile stores + plain reads       -> 28 B
//   volatile members + non-volatile cast reads -> 28 B
//   hoisting the read into one local    -> 35 B (MSVC folds `e != e`)
// So retail's `cmp eax,eax` is a CSE of two volatile loads that this MSVC will
// not perform. Arm polarity IS controllable: `if (first == last) return dst;`
// puts the memmove block last, matching retail.
extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *dst, const void *src, unsigned int count);

static inline char *bfmeCopyAL(char *first, char *last, char *dst)
{
	if (first == last)
		return dst;

	unsigned int n = last - first;

	return (char *)BfmeMemMove(dst, first, n) + n;
}

class BfmeNodeAL
{
public:
	BfmeNodeAL(void *key);

	char *volatile m_bfmeBeginAL;
	char *volatile m_bfmeEndAL;
	char *volatile m_bfmeCapAL;
	void *m_bfmeKeyAL;
	BfmeNodeAL *m_bfmeNextAL;
};

BfmeNodeAL::BfmeNodeAL(void *key)
{
	m_bfmeBeginAL = 0;
	m_bfmeEndAL = 0;
	m_bfmeCapAL = 0;
	m_bfmeKeyAL = key;
	m_bfmeEndAL = bfmeCopyAL(m_bfmeEndAL, m_bfmeEndAL, m_bfmeBeginAL);
	m_bfmeNextAL = 0;
}
