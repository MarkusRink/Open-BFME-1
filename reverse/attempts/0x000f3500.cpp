// ?bfmeGetKX@BfmeOwnerKX@@QAEPAUBfmeVec3KX@@PAU2@@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 59/59 bytes; 9 of 20 instructions differ and every one is the same ecx/edx
// swap (retail holds the adjusted pointer in edx and uses ecx as the copy
// scratch; we do the reverse).
// Settled: the body takes the out-buffer as an ordinary parameter and returns
// it (`ret 4` with eax = out on BOTH paths -- write `return out;` in each
// arm), the sub-object is raw arithmetic `(char *)m_owner + 12ch` whose null
// test reuses the ADD's flags, and the fallback is a __stdcall taking the same
// buffer.
// Tried: naming each copied field in its own local (same 9).
// Lone ecx/edx scratch flip.
struct BfmeVec3KX
{
	int m_bfmeXKX;
	int m_bfmeYKX;
	int m_bfmeZKX;
};

class BfmeSubKX
{
public:
	unsigned char m_bfmeHeadKX[0x5c];
	int m_bfmeAKX;
	int m_bfmeBKX;
	int m_bfmeCKX;
	char m_bfmeOkKX;
};

void __stdcall bfmeZeroKX(BfmeVec3KX *out);

class BfmeOwnerKX
{
public:
	BfmeVec3KX *bfmeGetKX(BfmeVec3KX *out);

	int m_bfmeSpareKX;
	void *m_bfmeOwnerKX;
};

BfmeVec3KX *BfmeOwnerKX::bfmeGetKX(BfmeVec3KX *out)
{
	BfmeSubKX *sub = (BfmeSubKX *)((char *)m_bfmeOwnerKX + 0x12c);

	if (sub != 0 && sub->m_bfmeOkKX != 0)
	{
		out->m_bfmeXKX = sub->m_bfmeAKX;
		out->m_bfmeYKX = sub->m_bfmeBKX;
		out->m_bfmeZKX = sub->m_bfmeCKX;

		return out;
	}

	bfmeZeroKX(out);

	return out;
}
