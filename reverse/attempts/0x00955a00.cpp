// ?bfmeSetWG@BfmeOwnerWG@@QAEXIPBUBfmeVec3WG@@M@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 75/71 bytes -- four OVER. Everything matches except the final flag clear and
// a whole-body eax/edx swap (retail keeps the index in edx and the element
// address in eax; ours the other way round).
// Settled: an unsigned bounds test, a 12-byte element array indexed with
// `lea eax,[edx+edx*2]` + `lea eax,[esi+eax*4]`, a POD struct assignment as
// three dword moves, the float argument loaded BEFORE the copy and stored
// last, and a separate float array at m_dc.
// Residue: retail clears the flag with a single read-modify-write
// `and dword ptr [ecx+10h],0fffdffffh` (7 bytes); MSVC splits it into
// load / and / store (11 bytes). Making the member unsigned with an explicit
// mask does not change it, and moving the statement to the top of the block is
// worse (76 bytes, 22 differing lines).
struct BfmeVec3WG
{
	float m_bfmeXWG;
	float m_bfmeYWG;
	float m_bfmeZWG;
};

class BfmeOwnerWG
{
public:
	void bfmeSetWG(unsigned int index, const BfmeVec3WG *value, float amount);

	unsigned char m_bfmeHeadWG[0x10];
	int m_bfmeFlagsWG;
	unsigned char m_bfmeGapWG[0xb8];
	BfmeVec3WG *m_bfmeVecsWG;
	unsigned char m_bfmeSpaceWG[4];
	unsigned int m_bfmeCountWG;
	unsigned char m_bfmeSpace2WG[4];
	float *m_bfmeAmountsWG;
};

void BfmeOwnerWG::bfmeSetWG(unsigned int index, const BfmeVec3WG *value, float amount)
{
	if (index < m_bfmeCountWG)
	{
		m_bfmeVecsWG[index] = *value;
		m_bfmeAmountsWG[index] = amount;
		m_bfmeFlagsWG &= ~0x20000;
	}
}
