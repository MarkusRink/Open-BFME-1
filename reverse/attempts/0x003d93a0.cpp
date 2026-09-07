// ?bfmeMaskGT@BfmeGridGT@@QAEHPAX@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 103/105 bytes; the only gap is a redundant `test eax,eax` retail emits
// between `add eax,esi` (the cell address) and the `je`. MSVC reuses the
// flags the add already set and drops it.
// Settled: the two ints filled by the locate call are one 2-int struct passed
// by address (lea esp+4), the bounds are four separate `if (... ) return 1;`
// guards, the row indexing is `m_rows[x] + y` (shl 4 then add, never a scaled
// lea), the flags member must be UNSIGNED (`shr eax,6`, not `sar`), and the
// last check must be written positively -- `if (cell != 0) return (f >> 6) &
// 0x3f; return 1;` -- so the shared `mov eax,1` lands last.
struct BfmePointGT
{
	int m_bfmeXGT;
	int m_bfmeYGT;
};

class BfmeCellGT
{
public:
	unsigned char m_bfmeHeadGT[0xc];
	unsigned int m_bfmeFlagsGT;
};

class BfmeGridGT
{
public:
	int bfmeMaskGT(void *item);
	char bfmeLocateGT(void *item, BfmePointGT *point);

	unsigned char m_bfmeHeadGT[0x10];
	BfmeCellGT **m_bfmeRowsGT;
	int m_bfmeMinXGT;
	int m_bfmeMinYGT;
	int m_bfmeMaxXGT;
	int m_bfmeMaxYGT;
};

int BfmeGridGT::bfmeMaskGT(void *item)
{
	if (m_bfmeRowsGT == 0)
		return 1;

	BfmePointGT point;

	if (bfmeLocateGT(item, &point))
		return 1;

	if (point.m_bfmeXGT < m_bfmeMinXGT)
		return 1;

	if (point.m_bfmeXGT > m_bfmeMaxXGT)
		return 1;

	if (point.m_bfmeYGT < m_bfmeMinYGT)
		return 1;

	if (point.m_bfmeYGT > m_bfmeMaxYGT)
		return 1;

	BfmeCellGT *cell = m_bfmeRowsGT[point.m_bfmeXGT] + point.m_bfmeYGT;

	if (cell != 0)
		return (cell->m_bfmeFlagsGT >> 6) & 0x3f;

	return 1;
}
