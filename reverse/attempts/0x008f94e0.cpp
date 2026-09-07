// ?bfmeStateWH@BfmeGridWH@@QAEHHHH@Z (identity unknown)
// partial score=0.93 date=2026-09-07
// 101/99 bytes -- two OVER, not short. Every instruction of the body matches:
// the inlined bounds-checked cell accessor (four guards plus the separate null
// test on base + index*68h), the 6-byte entry stride via lea edx,[edx+edx*2],
// the `xor edx,edx / test ax,ax / sete dl / mov eax,edx` result and the
// trailing `if (result == 1 && !m_flag) result = 0;`.
// Residue is block layout: retail puts the `mov eax,2` else-block INLINE,
// between the good path (which ends `jmp` over it) and the shared tail, so the
// epilogue exists once and `pop esi` is shrink-wrapped between `cmp eax,1` and
// its `jne`. MSVC sinks that block past the tail and duplicates
// `pop esi; ret 0ch`.
// Tried: nested if/else (this file), a single && chain, and the inverted
// `if (cell == 0 || value == 0ffffh)` form (much worse, 17 diffs).
struct BfmeEntryWH
{
	unsigned short m_bfmeFirstWH;
	unsigned short m_bfmeSecondWH;
	unsigned short m_bfmeThirdWH;
};

class BfmeCellWH
{
public:
	int m_bfmeSpareWH;
	BfmeEntryWH m_bfmeEntriesWH[1];
	unsigned char m_bfmeTailWH[0x5e];
};

class BfmeGridWH
{
public:
	BfmeCellWH *bfmeCellWH(int x, int y)
	{
		if (x < 0 || x >= m_bfmeWidthWH || y < 0 || y >= m_bfmeHeightWH)
			return 0;

		return &m_bfmeCellsWH[m_bfmeWidthWH * y + x];
	}

	int bfmeStateWH(int slot, int x, int y);

	unsigned char m_bfmeHeadWH[0x24];
	int m_bfmeWidthWH;
	int m_bfmeHeightWH;
	BfmeCellWH *m_bfmeCellsWH;
	unsigned char m_bfmeGapWH[0x38];
	char m_bfmeFlagWH;
};

int BfmeGridWH::bfmeStateWH(int slot, int x, int y)
{
	int result;
	BfmeCellWH *cell = bfmeCellWH(x, y);

	if (cell)
	{
		unsigned short value = cell->m_bfmeEntriesWH[slot].m_bfmeFirstWH;

		if (value == 0xffff)
			result = 2;
		else
			result = (value == 0);
	}
	else
		result = 2;

	if (result == 1 && m_bfmeFlagWH == 0)
		result = 0;

	return result;
}
