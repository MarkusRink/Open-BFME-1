// ?bfmeCheckYR@BfmeOwnerYR@@QAE_NPAVBfmeItemYR@@@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 53/55. Solved: a thiscall on this->m_14 with FIVE stack args pushed
// right-to-left (item->m_44, &item->m_38, item+0xac, this->m_18, &this->m_8),
// and the tail `sub al,[esi+0x1c] / neg al / sbb eax,eax / inc eax` is
// `== m_bfmeKindYR` returning bool ([[bool-gives-32bit-sbb]] -- the 32-bit sbb
// is what makes it bool rather than char).
// The `mov [esp+0xc],ecx` writing item->m_44 into the DEAD a1 parameter home
// slot is a dead local: `volatile int keep = item->m_bfme44YR;` reproduces it
// exactly, slot and all ([[dead-zeroed-local-is-volatile]],
// [[parameter-home-slot-reuse]]). Without it the body is 6 bytes short.
// Residue is 2 bytes: retail copies the value with `mov edx,ecx` and pushes
// edx, keeping ecx for the volatile store; MSVC pushes ecx and stores ecx, no
// copy needed. Splitting the read into a plain local and initialising the
// volatile from it does not introduce the copy.
class BfmeSubYR
{
public:
	char bfmeDoYR(void *a, void *b, void *c, void *d, int e);
};

class BfmeItemYR
{
public:
	unsigned char m_bfmeHeadYR[0x38];
	unsigned char m_bfmeAtYR[0xc];
	int m_bfme44YR;
	unsigned char m_bfmeMidYR[0x64];
	unsigned char m_bfmeTailYR[4];
};

class BfmeOwnerYR
{
public:
	bool bfmeCheckYR(BfmeItemYR *item);

	unsigned char m_bfmeHeadYR[8];
	unsigned char m_bfmeStateYR[0xc];
	BfmeSubYR *m_bfmeSubYR;
	void *m_bfmeArgYR;
	char m_bfmeKindYR;
};

bool BfmeOwnerYR::bfmeCheckYR(BfmeItemYR *item)
{
	int value = item->m_bfme44YR;
	volatile int keep = value;

	return m_bfmeSubYR->bfmeDoYR(m_bfmeStateYR, m_bfmeArgYR, item->m_bfmeTailYR,
	                             item->m_bfmeAtYR, value) == m_bfmeKindYR;
}
