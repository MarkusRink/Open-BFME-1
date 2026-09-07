// ?bfmeFormatXK@BfmeOwnerXK@@QAEXIPADD@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 85/85 exact size, every instruction aligned, only a clean register
// permutation left ([[argument-shuttle-register]] shuttle-identity shape):
//   retail  out=edx begin=eax end=esi index=eax(reused)
//   MSVC    out=esi begin=edx end=eax index=edx(reused)
// Because MSVC gives the callee-saved esi to `out` (longest live range) it also
// pushes esi in the prologue, where retail pushes it at +0x20; that is a
// consequence of the permutation, NOT the wrong block shape -- every retail
// instruction has a positional twin here.
// The two levers that DID work and must be kept:
//   * `int *volatile m_bfmeBeginXK` -- retail re-reads [ecx+0x258] before the
//     subscript; without volatile MSVC reuses the earlier load and the body is
//     79 bytes, six short.
//   * begin/end in locals for the compare and subtraction, member spelled again
//     for the subscript: that gives exactly retail's two loads of 0x258 and one
//     of 0x25c. Swapping the local declaration order regresses 13 -> 17 diffs.
// Two separate byte stores do NOT merge into `mov word ptr [edx],0x30`; keep the
// unsigned short store.
extern "C" int (__cdecl *__imp__sprintf)(char *, const char *, ...);
extern "C" char g_bfmeFormatXK[];

class BfmeOwnerXK
{
public:
	void bfmeFormatXK(unsigned int index, char *out, char flag);

	unsigned char m_bfmeHeadXK[0x258];
	int *volatile m_bfmeBeginXK;
	int *m_bfmeEndXK;
	void *m_bfmeCapXK;
	int m_bfmeModeXK;
};

void BfmeOwnerXK::bfmeFormatXK(unsigned int index, char *out, char flag)
{
	*(unsigned short *)out = 0x30;

	if (flag != 0)
		return;

	if (m_bfmeModeXK != 1)
		return;

	int *begin = m_bfmeBeginXK;
	int *end = m_bfmeEndXK;

	if (begin == end)
		return;

	if (index >= (unsigned int)(end - begin))
		return;

	(*__imp__sprintf)(out, g_bfmeFormatXK, m_bfmeBeginXK[index]);
}
