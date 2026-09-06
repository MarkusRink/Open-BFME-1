// ??0BfmeOwnCU@@QAE@XZ (identity unknown)
// partial score=0.88 date=2026-09-07
// 89 bytes against retail's 87. Structure recovered: a destructible head
// member of three zeroed ints, a self-pointer at +0xc, and a two-element
// array member at +0x10 constructed through the vector-constructor iterator
// ??_L@YGXPAXIHP6EX0@Z1@Z with size 4 and count 2.
// The head member's destructor is what creates the SEH frame -- without it
// MSVC emits 45 bytes and no frame at all (same diagnostic as 0x00754F70).
// Residue: retail reuses the zeroing eax for `lea eax,[esi+0x10]` once the
// three zero stores are done, so it needs no extra register; MSVC keeps eax
// live and saves edi for the array address, costing the two bytes.
class BfmeElemCU
{
public:
	BfmeElemCU(void);
	~BfmeElemCU();

	int m_bfmeDataCU;
};

class BfmeHeadCU
{
public:
	BfmeHeadCU(void)
	{
		m_bfmeACU = 0;
		m_bfmeBCU = 0;
		m_bfmeCCU = 0;
	}
	~BfmeHeadCU();

	int m_bfmeACU;
	int m_bfmeBCU;
	int m_bfmeCCU;
};

class BfmeOwnCU
{
public:
	BfmeOwnCU(void);

	BfmeHeadCU m_bfmeHeadCU;
	BfmeElemCU *m_bfmeItemsCU;
	BfmeElemCU m_bfmeArrayCU[2];
};

BfmeOwnCU::BfmeOwnCU(void)
{
	m_bfmeItemsCU = m_bfmeArrayCU;
}
