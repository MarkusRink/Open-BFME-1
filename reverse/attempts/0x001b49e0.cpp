// ?bfmeSetLV@BfmeOwnerLV@@QAEXPBUBfmeVecLV@@@Z (identity unknown)
// partial score=0.6 date=2026-09-07
// 30/44 bytes. Member offsets and the assignment ORDER are established:
// m_70 = source->x, m_90 = source->w, m_80 = source->y, and the two floats are
// read as float-typed expressions (retail uses fld/fld + fxch + two fstp; a
// struct-copy spelling turns the whole thing into integer moves, 50 bytes).
// What is NOT modelled: retail keeps a 12-byte local frame (`sub esp,0ch` /
// `add esp,0ch`) and one dead store `mov [esp+8],eax` of the third value, plus
// a spare `mov edx,eax`. That is exactly the 14-byte gap. Three separate
// locals (float x, float y, float/int w) are promoted away by MSVC, whether
// the third is int or float. Something forces the frame in the original --
// likely a temporary this model does not capture.
struct BfmeVecLV
{
	float m_bfmeXLV;
	float m_bfmeYLV;
	float m_bfmeWLV;
};

class BfmeOwnerLV
{
public:
	void bfmeSetLV(const BfmeVecLV *source);

	unsigned char m_bfmeHeadLV[0x70];
	float m_bfmeALV;
	unsigned char m_bfmeGapLV[0xc];
	float m_bfmeBLV;
	unsigned char m_bfmeTailLV[0xc];
	float m_bfmeCLV;
};

void BfmeOwnerLV::bfmeSetLV(const BfmeVecLV *source)
{
	float x = source->m_bfmeXLV;
	float y = source->m_bfmeYLV;
	float w = source->m_bfmeWLV;

	m_bfmeALV = x;
	m_bfmeCLV = w;
	m_bfmeBLV = y;
}
