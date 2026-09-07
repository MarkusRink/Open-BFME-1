// ?bfmeAllowXR@BfmeOwnerXR@@QAEHPAX@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 72/77 bytes. Structure and every guard match; the gap is the mixed-width
// exits, the same class as 0x001C9980.
// Retail has FOUR exits and they do not merge because two are 8-bit and two
// are 32-bit: after the bool-returning check call it reuses al for `return 0`
// (no instruction at all) and writes `mov al,1`; after the pointer-returning
// lookup it writes `xor eax,eax` and `mov eax,1`. Declaring the check callee
// `bool` is necessary but not sufficient -- MSVC still emits `xor eax,eax`
// and `mov eax,1` in the first region.
// Tried: a `char` return (65 bytes, all four exits 8-bit) and nesting the tail
// so the return-1 blocks merge (67). The int return with four separate early
// returns, kept here, is the closest at 72.
class BfmeUnitXR
{
public:
	unsigned char m_bfmeHeadXR[0x344];
	unsigned char m_bfmeFlagsXR;
};

struct Rva00367E30Logic
{
	BfmeUnitXR *bfmeFindXR(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerXR
{
public:
	int bfmeAllowXR(void *item);
	bool bfmeCheckXR(void *item);

	unsigned char m_bfmeHeadXR[0x8c];
	void *m_bfmeKeyXR;
};

int BfmeOwnerXR::bfmeAllowXR(void *item)
{
	if (!bfmeCheckXR(item))
		return 0;

	void *key = m_bfmeKeyXR;

	if (key == 0)
		return 1;

	BfmeUnitXR *unit = TheBfmeGameLogic->bfmeFindXR(key);

	if (unit == 0)
		return 1;

	if (unit->m_bfmeFlagsXR & 1)
		return 1;

	return 0;
}
