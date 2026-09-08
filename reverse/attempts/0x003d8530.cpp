// ?bfmeDrop@Rva003D8530Owner@@QAEXPAX@Z
// partial score=0.96 date=2026-09-08
// cl: /DNDEBUG /MD /O2 /EHsc
// The owner drops a grid cell after converting the owner's position. The
// conversion, owner check, clear call, and sink notification match retail.
// The remaining difference is callee-saved register allocation.

typedef int Int;

class BfmePosETD;
class BfmeOwnerETD;

struct BfmePairETD
{
	Int m_bfmeXETD;
	Int m_bfmeYETD;
};

struct BfmeCellETD
{
	void bfmeSetOwnerETD(BfmeOwnerETD *owner);

	unsigned char m_bfmeHeadETD[4];
	BfmeOwnerETD *m_bfmeOwnerETD;
	unsigned char m_bfmeTailETD[8];
};

class BfmeSinkETD
{
public:
	void bfmeNotifyETD(Int x, Int y, Int mode, BfmeOwnerETD *owner);
};

class Rva003D8530Owner
{
public:
	void bfmeDrop(void *entry);
	void bfmeCheckESF(BfmePosETD *position, BfmePairETD *cell);

private:
	unsigned char m_bfmeHeadETD[0x10];
	BfmeCellETD **m_bfmeCellsETD;
	Int m_bfmeMinXETD;
	Int m_bfmeMinYETD;
	Int m_bfmeMaxXETD;
	Int m_bfmeMaxYETD;
	unsigned char m_bfmeMidETD[0xc78];
	BfmeSinkETD m_bfmeSinkETD;
};

void Rva003D8530Owner::bfmeDrop(void *entry)
{
	BfmePairETD cell;

	bfmeCheckESF((BfmePosETD *)((char *)entry + 0x0c), &cell);

	Int x = cell.m_bfmeXETD;
	if (x < m_bfmeMinXETD || x > m_bfmeMaxXETD)
		return;

	Int y = cell.m_bfmeYETD;
	if (y < m_bfmeMinYETD || y > m_bfmeMaxYETD)
		return;

	BfmeCellETD *cellEntry = m_bfmeCellsETD[x] + y;
	if (cellEntry == 0)
		return;

	if (cellEntry->m_bfmeOwnerETD != entry)
		return;

	cellEntry->bfmeSetOwnerETD(0);
	m_bfmeSinkETD.bfmeNotifyETD(x, y, 0, (BfmeOwnerETD *)entry);
}
