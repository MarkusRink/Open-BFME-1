// ?bfmeApplyXW@BfmeOwnerXW@@QAEXPAUBfmeVec3XW@@HH@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 66/68 bytes. Frame, both calls and all six float operations match; the two
// missing bytes are the `fxch st(2)`.
// Settled: 16 bytes of locals (a scalar plus a 12-byte vec), the scalar from a
// thiscall on the embedded member at this+1ch, the vec filled by a __cdecl
// taking its address (cleaned at the end, hence `add esp,14h`), and three
// stores through the first of THREE stack parameters (the other two are
// unused, so declare them).
// Residue: retail computes all three products onto the x87 stack and then
// stores them (fld/fmul x3, fxch st(2), fstp x3); MSVC interleaves
// compute-store because `vec` had its address taken and so may alias `out`.
// Naming the three products in float locals first does not change it.
struct BfmeVec3XW
{
	float m_bfmeXXW;
	float m_bfmeYXW;
	float m_bfmeZXW;
};

void __cdecl bfmeFillXW(BfmeVec3XW *out);

class BfmeSubXW
{
public:
	float bfmeScaleXW(void);
};

class BfmeOwnerXW
{
public:
	void bfmeApplyXW(BfmeVec3XW *out, int first, int second);

	unsigned char m_bfmeHeadXW[0x1c];
	BfmeSubXW m_bfmeSubXW;
};

void BfmeOwnerXW::bfmeApplyXW(BfmeVec3XW *out, int first, int second)
{
	float scale = m_bfmeSubXW.bfmeScaleXW();
	BfmeVec3XW vec;

	bfmeFillXW(&vec);

	float x = vec.m_bfmeXXW * scale;
	float y = vec.m_bfmeYXW * scale;
	float z = vec.m_bfmeZXW * scale;

	out->m_bfmeXXW = x;
	out->m_bfmeYXW = y;
	out->m_bfmeZXW = z;
}
