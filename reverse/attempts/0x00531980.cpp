// ?bfmeRunYD@@YAXPAUBfmeVecYD@@00HHHPAX@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 95/93. Everything is identified: a 12-byte struct assignment `*out = *begin`
// (the redundant `mov eax,esi` before it is the struct-copy tell), an
// argument-area temporary built through the esp marker
// ([[construct-temp-in-argument-area]]), the `end - begin` pointer difference
// for a 12-byte element compiled as imul 0x2aaaaaab / sar 1 / sign fixup, and a
// cdecl callee taking (begin, 0, count, struct-by-value, extra) cleaned with
// add esp,0x1c.
// The 2 excess bytes are one push edi / pop edi: MSVC hoists the `extra`
// parameter read ABOVE the struct-copy statement, so it needs a callee-saved
// register, where retail loads it into ecx after the copy and pushes it at once.
// Reading it as *(void *volatile *)&extra ([[volatile-cast-pins-parameter]])
// moves the push later and reshapes the fill but does not remove it -- VC7.1
// volatile does not fence the copy's NON-volatile stores, so the read still
// floats above them. Making the third ctor argument volatile as well moves its
// read the wrong way (earlier, not later). To finish this the struct copy's
// stores would have to be volatile too, which changes the copy codegen.
struct BfmeVecYD
{
	BfmeVecYD(int a, int b, int c)
	{
		m_bfmeAYD = a;
		m_bfmeBYD = b;
		m_bfmeCYD = c;
	}

	int m_bfmeAYD;
	int m_bfmeBYD;
	int m_bfmeCYD;
};

void __cdecl bfmeCallYD(BfmeVecYD *begin, int zero, int count, BfmeVecYD value, void *extra);

void __cdecl bfmeRunYD(BfmeVecYD *begin, BfmeVecYD *end, BfmeVecYD *out,
                       int a, int b, int c, void *extra)
{
	*out = *begin;

	bfmeCallYD(begin, 0, end - begin, BfmeVecYD(a, b, c), *(void *volatile *)&extra);
}
