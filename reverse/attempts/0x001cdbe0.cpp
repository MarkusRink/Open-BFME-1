// ?bfmeReadyBW@BfmeOwnBW@@QAEDXZ (identity unknown)
// partial score=0.7 date=2026-09-06
// 48 bytes from MSVC against retail's 56. The structure is certain: a null
// check on TheBfmeGameLogic kept in a callee-saved register across the call,
// a busy predicate called with 0x25, and an unsigned frame-versus-due
// comparison.
// Residue: retail BRANCHES on the last comparison (two full epilogues, one
// `mov eax,1` and one `xor eax,eax`) while MSVC folds it branchlessly into
// `sbb al,al` / `inc al`, eight bytes shorter. Tried: the guard both
// polarities, char and int return types, a `2 - 1` true value, a named self
// local, and the flags /G7 /Ob1 /Ot /Oy-. Also note esi/edi are swapped
// relative to retail (this in esi there, the logic local in esi here).
class GameLogic
{
public:
	unsigned char m_bfmeHeadBW[0x3c];
	unsigned int m_bfmeFrameBW;
};

extern GameLogic *TheBfmeGameLogic;

class BfmeOwnBW
{
public:
	char bfmeReadyBW(void);
	char bfmeBusyBW(int kind);

	unsigned char m_bfmeHeadBW[0x334];
	unsigned int m_bfmeDueBW;
};

char BfmeOwnBW::bfmeReadyBW(void)
{
	GameLogic *logic = TheBfmeGameLogic;

	if (logic == 0)
		return 0;

	if (bfmeBusyBW(0x25))
		return 0;

	if (logic->m_bfmeFrameBW < m_bfmeDueBW)
		return 0;

	return 1;
}
