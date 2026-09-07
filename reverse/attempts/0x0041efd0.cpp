// ?bfmeFireRC@BfmeOwnerRC@@QAEDPAX0@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 113/117 bytes. The guard chain, the resolve, the two no-arg calls and the
// six-argument forward (including returning the callee's char result directly)
// all match; the return-0 block is correctly last.
// Residue: retail materialises the null arm of `state` --
//   test ebp,ebp / je L0 / mov eax,[ebp+204h] / jmp L1 / L0: xor eax,eax /
//   L1: test eax,eax / je exit
// -- while MSVC threads the jump, seeing that a null unit and a null state
// reach the same exit, and emits a single `test ebp,ebp; je exit`. That is the
// whole 4-byte gap, and it also shifts the callee-saved allocation
// (retail ebx/ebp/edi, ours ebp/esi/edi).
// Tried: explicit if/else into the variable, and the ternary spelling. Both
// thread. Jump-threading residue, same family as the null-arm folding in
// reverse/attempts/0x000c7d10.cpp.
class BfmeThingRC;

class BfmeInnerRC
{
public:
	BfmeThingRC *bfmeResolveRC(void);
};

class BfmeThingRC
{
public:
	unsigned char m_bfmeHeadRC[4];
	BfmeInnerRC *m_bfmeInnerRC;
	unsigned char m_bfmeGapRC[0x68];
	int m_bfmeKindRC;
};

class BfmeHolderRC
{
public:
	int m_bfmeSpareRC;
	BfmeThingRC *m_bfmeThingRC;
};

class BfmeStateRC
{
public:
	unsigned char m_bfmeHeadRC[0x1cc];
	BfmeHolderRC *m_bfmeHolderRC;
};

class BfmeUnitRC
{
public:
	unsigned char m_bfmeHeadRC[0x204];
	BfmeStateRC *m_bfmeStateRC;
};

class BfmeOwnerRC
{
public:
	char bfmeFireRC(void *first, void *second);

	void *bfmeGetARC(void);
	void *bfmeGetBRC(void);
	char bfmeSendRC(BfmeUnitRC *unit, BfmeHolderRC *holder, void *a, void *b, void *first, void *second);

	unsigned char m_bfmeHeadRC[0xfc];
	BfmeUnitRC *m_bfmeUnitRC;
};

char BfmeOwnerRC::bfmeFireRC(void *first, void *second)
{
	BfmeUnitRC *unit = m_bfmeUnitRC;
	BfmeStateRC *state;

	if (unit)
		state = unit->m_bfmeStateRC;
	else
		state = 0;

	if (state)
	{
		BfmeHolderRC *holder = state->m_bfmeHolderRC;

		if (holder)
		{
			BfmeThingRC *thing = holder->m_bfmeThingRC;

			if (thing && thing->m_bfmeInnerRC)
				thing = thing->m_bfmeInnerRC->bfmeResolveRC();

			if (thing->m_bfmeKindRC == 1)
			{
				void *a = bfmeGetARC();
				void *b = bfmeGetBRC();

				return bfmeSendRC(unit, holder, a, b, first, second);
			}
		}
	}

	return 0;
}
