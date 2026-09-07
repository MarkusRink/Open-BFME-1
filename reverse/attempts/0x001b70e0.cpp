// ?bfmeLookupERA@@YGPAXPAVBfmeStrERA@@@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 92/92 EXACT SIZE. __stdcall name-to-key lookup: inline AsciiString::str(),
// TheNameKeyGenerator->nameToKey(), the key parked in the dead parameter home
// slot, then a map find() through an out-parameter compared against the
// collection head.
//
// Single residue: block layout. Retail keeps the shared "return 0" block
// INLINE right after the first test (jne to the main block; the second test
// then jumps BACKWARD to it):
//     test eax,eax / mov [esp+8],eax / jne MAIN
//     xor eax,eax / pop ecx / ret 4
//   MAIN: ... / je back / mov eax,[eax+0x14] / pop ecx / ret 4
// MSVC sinks that cold block to the end and inverts both branches instead.
// Ruled out: if (key == 0) return 0 early-out; if (key != 0) { ... } return 0;
// a merged result variable (97 bytes); explicit goto/label spelling retail's
// exact block order; /Os (86) /G7 (90) /Ot /Ob1 /Gy /GF (all 92, same shape).
//
// FAMILY: 17 unclaimed gen_asm bodies call the nameToKey thunk 0x0003ADD7
// (scratchpad callsto.py 43add7 240): 0x001B70E0 92, 0x006128F0 95,
// 0x00380270 104, 0x00754970 119, 0x0033C290 132, 0x000CDBB0 149,
// 0x001C1EA0 155, 0x00322430 169, 0x00773270 180, 0x0029CD20 187,
// 0x00323460 190, 0x0021CF70 191, 0x001CAF20 196, 0x00589750 216,
// 0x00206460 220, 0x0036F1B0 228, 0x003240F0 230.
// 0x006128F0 is the SAME body with a different global (0x00EF706C + 0x27C)
// and find thunk (0x0002DF6F), so it will hit the same layout residue.
// Pins added for this attempt are still in symbols.csv.
extern char g_bfmeEmptyERA[];

struct BfmeStrDataERA
{
	int m_bfmeRefERA;
	int m_bfmeLenERA;
	char m_bfmeTextERA[1];
};

class BfmeStrERA
{
public:
	const char *bfmeTextERA() const
	{
		return m_bfmeDataERA ? m_bfmeDataERA->m_bfmeTextERA : g_bfmeEmptyERA;
	}

	BfmeStrDataERA *m_bfmeDataERA;
};

class BfmeKeyGenERA
{
public:
	int bfmeNameToKeyERA(const char *name);
};

extern BfmeKeyGenERA *g_bfmeKeyGenERA;

class BfmeNodeERA
{
public:
	unsigned char m_bfmeHeadERA[0x14];
	void *m_bfmeValueERA;
};

class BfmeMapERA
{
public:
	void bfmeFindERA(BfmeNodeERA **out, int *key);

	BfmeNodeERA *m_bfmeEndERA;
};

class BfmeOwnerERA
{
public:
	unsigned char m_bfmeHeadERA[8];
	BfmeMapERA m_bfmeMapERA;
};

extern BfmeOwnerERA *g_bfmeOwnerERA;

void * __stdcall bfmeLookupERA(BfmeStrERA *name)
{
	int key = g_bfmeKeyGenERA->bfmeNameToKeyERA(name->bfmeTextERA());

	if (key == 0)
		return 0;

	BfmeMapERA *map = &g_bfmeOwnerERA->m_bfmeMapERA;
	BfmeNodeERA *node;

	map->bfmeFindERA(&node, &key);

	if (node == map->m_bfmeEndERA)
		return 0;

	return node->m_bfmeValueERA;
}
