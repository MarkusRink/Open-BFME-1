// ?bfmeTestYN@BfmeOwnerYN@@QAEDPAUBfmeMaskYN@@@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 96/98. Structure fully recovered: guard polarity is `if (match) return 0;`
// (the je jumps FORWARD to the body, so the zero return is the fallthrough --
// writing it as `if (!match) return 0;` inverts the branch AND lets MSVC drop
// the explicit `xor al,al`), a three-dword mask AND into a stack temporary,
// then `return mask.bfmeAnyYN(&masked) == 0;` -- the neg/sbb/inc trio is the
// 8-bit `!x`, and the receiver is `&this->m_bfmeMaskYN` (lea ecx,[esi+4]).
// The 2 missing bytes are `push ebx` / `pop ebx`: retail loads all three of
// `other`'s fields up front, so three values are live at once and it needs a
// fourth callee-saved register; MSVC computes them one at a time and never
// needs ebx. Naming the three reads in locals does not stop the coalescing.
// Reading them through `*(int volatile *)&` DOES pin the loads to the top and
// frees `other`'s register, but overshoots to 100 bytes and swaps the AND
// destination (retail `and eax,ebx`, MSVC `and ebx,eax`).
struct BfmeSubYN
{
	unsigned char m_bfmeBytesYN[4];
};

struct BfmeMaskYN
{
	char bfmeMatchYN(BfmeSubYN *sub);
	char bfmeAnyYN(BfmeMaskYN *other);

	int m_bfmeAYN;
	int m_bfmeBYN;
	int m_bfmeCYN;
};

class BfmeOwnerYN
{
public:
	char bfmeTestYN(BfmeMaskYN *other);

	unsigned char m_bfmeHeadYN[4];
	BfmeMaskYN m_bfmeMaskYN;
	BfmeSubYN m_bfmeSubYN;
};

char BfmeOwnerYN::bfmeTestYN(BfmeMaskYN *other)
{
	if (other->bfmeMatchYN(&m_bfmeSubYN) != 0)
		return 0;

	BfmeMaskYN masked;

	int a = other->m_bfmeAYN;
	int b = other->m_bfmeBYN;
	int c = other->m_bfmeCYN;

	masked.m_bfmeAYN = a & m_bfmeMaskYN.m_bfmeAYN;
	masked.m_bfmeBYN = b & m_bfmeMaskYN.m_bfmeBYN;
	masked.m_bfmeCYN = c & m_bfmeMaskYN.m_bfmeCYN;

	return m_bfmeMaskYN.bfmeAnyYN(&masked) == 0;
}
