// ?bfmeEraseZU@BfmeListZU@@QAEXPAVBfmeKeyZU@@@Z (identity unknown)
// partial score=0.7 date=2026-09-07
// 93/84 in this (member-spelled) form. Semantics are fully recovered: an STL
// list erase-by-value -- walk the circular list from the sentinel POINTER at
// this+0x80, compare node+8 against *key, unlink via prev/next, run the
// destructor on node+8, `_M_deallocate(node, 0x14)`, then decrement the count at
// this+0x8c. Node is 20 bytes: next, prev, then a 12-byte value at +8.
// TWO competing problems, and fixing either creates the other:
//   * spelling the sentinel as the member (this form) keeps retail's block
//     structure -- back-edge `cmp esi,eax / jne`, fall through to a SECOND
//     `cmp esi,eax / je` -- but re-reads `[edi+0x80]` in the loop where retail
//     uses the cached eax (6 bytes vs 2).
//   * caching it in a local (`BfmeNodeZU *end = m_bfmeSentinelZU;`) fixes the
//     re-read but lets MSVC prove the loop-exit implies `node == end`, so it
//     jumps the exit straight to a DUPLICATED epilogue and drops the re-test
//     (94 bytes). A do/while with the entry test hoisted does the same.
// So the wanted shape is "cached sentinel AND an un-merged re-test", which no
// spelling tried so far produces. Related: [[flat-ifs-force-a-retest]],
// [[retail-duplicates-early-return]].
struct BfmeValueZU
{
	void bfmeFreeZU();

	int m_bfmeIdZU;
	unsigned char m_bfmePadZU[8];
};

struct BfmeNodeZU
{
	BfmeNodeZU *m_bfmeNextZU;
	BfmeNodeZU *m_bfmePrevZU;
	BfmeValueZU m_bfmeValueZU;
};

class BfmeKeyZU
{
public:
	int m_bfmeIdZU;
};

void __cdecl bfmeDeallocZU(void *p, unsigned int n);

class BfmeListZU
{
public:
	void bfmeEraseZU(BfmeKeyZU *key);

	unsigned char m_bfmeHeadZU[0x80];
	BfmeNodeZU *m_bfmeSentinelZU;
	unsigned char m_bfmeMidZU[8];
	int m_bfmeCountZU;
};

void BfmeListZU::bfmeEraseZU(BfmeKeyZU *key)
{
	BfmeNodeZU *node = m_bfmeSentinelZU->m_bfmeNextZU;

	while (node != m_bfmeSentinelZU)
	{
		if (node->m_bfmeValueZU.m_bfmeIdZU == key->m_bfmeIdZU)
			break;

		node = node->m_bfmeNextZU;
	}

	if (node == m_bfmeSentinelZU)
		return;

	node->m_bfmePrevZU->m_bfmeNextZU = node->m_bfmeNextZU;
	node->m_bfmeNextZU->m_bfmePrevZU = node->m_bfmePrevZU;

	node->m_bfmeValueZU.bfmeFreeZU();

	bfmeDeallocZU(node, 0x14);

	m_bfmeCountZU--;
}
