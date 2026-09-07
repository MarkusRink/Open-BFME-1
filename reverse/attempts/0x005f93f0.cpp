// ?bfmeScaleYM@@YGXPAUBfmeVec3YM@@PAUBfmeVec2YM@@MH@Z (identity unknown)
// partial score=0.8 date=2026-09-07
// 83/95. Every x87 instruction matches -- the length, the fucompp against
// ?BfmeZeroRange@@3MB (RVA 0x00C75350), the fdivr by the float at RVA
// 0x00C75334, the two fmulp of the unit vector and the tail stores. Two things
// were needed to get this far and are worth keeping:
//   * the third argument is an INT, not a float: retail copies it with
//     `mov ecx,[esp+0x1c]` / `mov [eax+8],ecx`. Declared float, MSVC uses
//     `fld`/`fstp` and the whole FPU stack shape shifts.
//   * `__stdcall`, 4 stack args, out-pointer first (ret 0x10).
// The 12-byte gap is exactly `sub esp,0xc` + `fstp [esp]` + `fld [esp]` +
// `add esp,0xc`: retail SPILLS x*scale to the stack, multiplies y, reloads x
// and only then stores out->x and out->y. MSVC stores out->x immediately and
// never needs the slot. Tried and rejected: computing both products into named
// float locals first (still no spill, 83); `volatile float rx` (does produce a
// spill and 91 bytes, but reloads through an INTEGER move `mov edx,[esp+8]` /
// `mov [eax],edx` instead of retail's fld/fstp, and uses [esp+8] not [esp]);
// the per-file /Op float-consistency flag (161 bytes, sqrt stops being an
// intrinsic). The spill looks like an FPU register-allocator decision with no
// source handle found yet.
extern "C" double __cdecl sqrt(double x);

extern const float g_bfmeZeroYM;
extern float g_bfmeUnitYM;

struct BfmeVec2YM
{
	float m_bfmeXYM;
	float m_bfmeYYM;
};

struct BfmeVec3YM
{
	float m_bfmeXYM;
	float m_bfmeYYM;
	int m_bfmeZYM;
};

void __stdcall bfmeScaleYM(BfmeVec3YM *out, BfmeVec2YM *in, float scale, int z)
{
	float x = in->m_bfmeXYM;
	float y = in->m_bfmeYYM;
	float len = (float)sqrt(y * y + x * x);

	if (len != g_bfmeZeroYM)
	{
		float k = g_bfmeUnitYM / len;

		x = x * k;
		y = y * k;
	}

	float rx = x * scale;
	float ry = y * scale;

	out->m_bfmeZYM = z;
	out->m_bfmeXYM = rx;
	out->m_bfmeYYM = ry;
}
