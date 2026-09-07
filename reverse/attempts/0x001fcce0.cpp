// ?bfmeCheckNS@BfmeOwnerNS@@QAEDPAVBfmeHolderNS@@@Z (identity unknown)
// partial score=0.93 date=2026-09-07
// 72/72 bytes; 5 of 26 instructions differ and all five come from one decision:
// which of the two exit blocks is the fall-through. Retail puts `xor al,al`
// (return 0) right after `cmp eax,1` and `mov al,1` last, reached by `je`.
// MSVC swaps them -- and because it then knows eax==1 on the fall-through it
// writes the return-1 as the no-op `mov al,al` (8a c0) instead of `mov al,1`.
// That value-tracking peephole is what blocks this: any spelling that makes
// return-1 the branch target keeps it dominated by the `== 1` compare.
// Tried: `!= 1` with and without an explicit else (both fold the whole thing to
// dec/neg/sbb/inc), a `bool` return with true/false, an enum-typed query
// compared against an enumerator, hoisting the query result into a local, and
// /Ot /G7 (no change) plus /Os /Oy- (much worse).
class BfmeThingNS;

class BfmeInnerNS
{
public:
	BfmeThingNS *bfmeResolveNS(void);
};

class BfmeThingNS
{
public:
	int m_bfmeSpareNS;
	BfmeInnerNS *m_bfmeInnerNS;
	unsigned char m_bfmeGapNS[0xc0];
	unsigned char m_bfmeFlagsNS;
};

class BfmeHolderNS
{
public:
	int bfmeQueryNS(void);

	int m_bfmeSpareNS;
	BfmeThingNS *m_bfmeThingNS;
};

class BfmeOwnerNS
{
public:
	char bfmeCheckNS(BfmeHolderNS *holder);

	unsigned char m_bfmeHeadNS[0x2c];
	int m_bfmeStateNS;
};

char BfmeOwnerNS::bfmeCheckNS(BfmeHolderNS *holder)
{
	if (m_bfmeStateNS != 1)
		return 0;

	if (holder)
	{
		BfmeThingNS *thing = holder->m_bfmeThingNS;

		if (thing && thing->m_bfmeInnerNS)
			thing = thing->m_bfmeInnerNS->bfmeResolveNS();

		if ((thing->m_bfmeFlagsNS & 4) == 0)
		{
			if (holder->bfmeQueryNS() == 1)
				return 1;
		}
	}

	return 0;
}
