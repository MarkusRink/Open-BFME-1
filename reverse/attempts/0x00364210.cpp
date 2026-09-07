// ?bfmeApplyRB@BfmeOwnerRB@@QAEXH@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 60/65 bytes. The magic-divide size computation (0b60b60b7h / imul / add /
// sar 7 / shr 1fh / add), the signed lower-bound test, the unsigned upper-bound
// test, the `imul index,0b4h` element offset and the __stdcall forward all
// match.
// Residue is register allocation. Retail keeps the INDEX in a callee-saved
// register (edi, pushed at entry) and `begin` in edx, which the one-operand
// `imul` clobbers -- so it re-reads `mov edx,[ecx]` after the bounds test, and
// it materialises the vector address once with `add ecx,30h` and uses [ecx] /
// [ecx+4]. MSVC keeps `begin` in edi instead (no re-read) and addresses the
// members as [ecx+30h] / [ecx+34h].
// Tried: a pointer local for the vector, and naming the count in its own local
// after an early `if (index < 0) return;`. Both fold back to the same 60 bytes.
struct BfmeElemRB
{
	unsigned char m_bfmeRawRB[0xb4];
};

struct BfmeVecRB
{
	BfmeElemRB *m_bfmeBeginRB;
	BfmeElemRB *m_bfmeEndRB;
};

void __stdcall bfmeUseRB(BfmeElemRB *item);

class BfmeOwnerRB
{
public:
	void bfmeApplyRB(int index);

	unsigned char m_bfmeHeadRB[0x30];
	BfmeVecRB m_bfmeListRB;
};

void BfmeOwnerRB::bfmeApplyRB(int index)
{
	BfmeVecRB *list = &m_bfmeListRB;

	if (index >= 0 && (unsigned int)index < (unsigned int)(list->m_bfmeEndRB - list->m_bfmeBeginRB))
		bfmeUseRB(&list->m_bfmeBeginRB[index]);
}
