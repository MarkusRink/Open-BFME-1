// ?bfmeTestESF@BfmeHostESF@@QAEDPAVBfmeAESF@@PAVBfmeBESF@@@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 92/104. Model is settled and every instruction of the body matches; the
// 12-byte gap is entirely a DUPLICATED epilogue that MSVC tail-merges.
// Retail has TWO "return 1" exits that cannot merge because they materialise
// the constant differently:
//     +0x35  mov al,1   / pop esi / add esp,8 / ret 8   <- check() true, c==0
//     +0x53  mov eax,1  / pop esi / add esp,8 / ret 8   <- kind not 5/1/2
// and one "return 0" (xor eax,eax) sunk last. MSVC emits mov al,1 for all
// three and folds them into a single block.
// This is the unstable-constant-materialisation class: the 8-bit vs 32-bit
// choice is what keeps retail's blocks distinct, and nothing in the source
// selects it. Ruled out: char / bool / int return types (92, 92, 95).
//
// Shape for whoever picks this up: two out-param dwords filled by the first
// call through a pointer to the first (so an 8-byte struct, not two separate
// out-params), then find(arg2, pair.a, pair.b), then (kind & 7) tested
// against 5, 1, 2 in that order.
// Pins are already in symbols.csv.
struct BfmePairESF
{
	int m_bfmeAESF;
	int m_bfmeBESF;
};

class BfmeAESF;
class BfmeBESF;

class BfmeCESF
{
public:
	unsigned char m_bfmeHeadESF[0xc];
	int m_bfmeKindESF;
};

class BfmeHostESF
{
public:
	char bfmeTestESF(BfmeAESF *a, BfmeBESF *b);
	char bfmeCheckESF(BfmeAESF *a, BfmePairESF *out);
	BfmeCESF *bfmeFindESF(BfmeBESF *b, int first, int second);
};

char BfmeHostESF::bfmeTestESF(BfmeAESF *a, BfmeBESF *b)
{
	BfmePairESF pair;

	if (bfmeCheckESF(a, &pair))
		return 1;

	BfmeCESF *c = bfmeFindESF(b, pair.m_bfmeAESF, pair.m_bfmeBESF);

	if (c == 0)
		return 1;

	int kind = c->m_bfmeKindESF & 7;

	if (kind == 5 || kind == 1 || kind == 2)
		return 0;

	return 1;
}
