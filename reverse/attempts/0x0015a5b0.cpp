// ?bfmeSumKZ@BfmeOwnerKZ@@QAEHXZ (identity unknown)
// partial score=0.9 date=2026-09-07
// 55/57 bytes. Loop shape, guards, the resolve call and the accumulate all
// match. Caching the count in a local is required (reading m_count in the loop
// condition costs a reload every iteration and a separate index register).
// Two residues:
//  1. Retail reads the entry member as `add eax,4` + `mov eax,[eax]`; every
//     spelling tried folds it to `mov eax,[eax+4]` -- a raw char* cast, a
//     `BfmeThingKZ **slot = &...` local, and a secondary-base model (that one
//     is worse: a derived-to-base conversion of a possibly-null pointer adds
//     the test/lea null check, 65 bytes).
//  2. Accumulator and array pointer swap callee-saved registers: retail has
//     the total in edi and the walker in esi, MSVC the other way round.
//     Reordering the local declarations does not flip them.
class BfmeThingKZ;

class BfmeInnerKZ
{
public:
	BfmeThingKZ *bfmeResolveKZ(void);
};

class BfmeThingKZ
{
public:
	int m_bfmeSpareKZ;
	BfmeInnerKZ *m_bfmeInnerKZ;
	unsigned char m_bfmeGapKZ[0x438];
	int m_bfmeValueKZ;
};

class BfmeEntryKZ
{
public:
	int m_bfmeSpareKZ;
	BfmeThingKZ *m_bfmeThingKZ;
};

class BfmeOwnerKZ
{
public:
	int bfmeSumKZ(void);

	int m_bfmeCountKZ;
	BfmeEntryKZ *m_bfmeItemsKZ[1];
};

int BfmeOwnerKZ::bfmeSumKZ(void)
{
	int count = m_bfmeCountKZ;
	int index;
	int total = 0;

	for (index = 0; index < count; index++)
	{
		BfmeThingKZ *thing = *(BfmeThingKZ **)((char *)m_bfmeItemsKZ[index] + 4);

		if (thing && thing->m_bfmeInnerKZ)
			thing = thing->m_bfmeInnerKZ->bfmeResolveKZ();

		total += thing->m_bfmeValueKZ;
	}

	return total;
}
