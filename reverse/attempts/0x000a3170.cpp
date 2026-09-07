// ?bfmeMatchCC@@YADPAVBfmeThingCC@@0@Z (identity unknown)
// partial score=0.96 date=2026-09-07
// 61/61 at exact size. Every instruction matches, including the
// xor edx,edx / sete dl / mov al,dl char tail ([[mask-not-less-than-zero]]'s
// sibling idiom) and the rank local shared between the `< 0` test and the
// compare. The ONLY difference is where MSVC puts the shared `return 1` block:
// retail emits it INLINE between the two guards and the body (both guards jump
// forward a few bytes to it); MSVC sinks it past the body.
// Same residue class as 0x006128F0 -- see [[guard-polarity-places-blocks]] and
// that stash. Both spellings give byte-identical output here:
//   if (r == 0 || b == r) return 1;  <body>
//   if (r != 0 && b != r) { <body> }  return 1;
class BfmeThingCC
{
public:
	virtual void bfmeSlot00CC();
	virtual void bfmeSlot01CC();
	virtual void bfmeSlot02CC();
	virtual void bfmeSlot03CC();
	virtual void bfmeSlot04CC();
	virtual void *bfmeKeyCC();

	BfmeThingCC *bfmeResolveCC(void *key);

	unsigned char m_bfmeHeadCC[0x14];
	int m_bfmeRankCC;
};

char __cdecl bfmeMatchCC(BfmeThingCC *a, BfmeThingCC *b)
{
	BfmeThingCC *r = a->bfmeResolveCC(a->bfmeKeyCC());

	if (r == 0 || b == r)
		return 1;

	int rank = b->m_bfmeRankCC;

	if (rank < 0)
		return 0;

	return rank == r->m_bfmeRankCC ? 1 : 0;
}
