// ?bfmeComparePE@@YAMPAVBfmeHolderPE@@0@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 81/89 bytes. Exact twin of 0x001DE0B0 with the two parameters swapped: this
// one reads arg2 first and subtracts arg1's key from it (a reversed
// comparator). Same source, same 8-byte residue -- two sites of the
// `add eax,4` + `mov eax,[eax]` base adjust that MSVC folds to
// `mov eax,[eax+4]`. See reverse/attempts/0x001de0b0.cpp for what has been
// ruled out; solving it there lands both bodies.
class BfmeThingPE;

class BfmeInnerPE
{
public:
	BfmeThingPE *bfmeResolvePE(void);
};

class BfmeThingPE
{
public:
	int m_bfmeSparePE;
	BfmeInnerPE *m_bfmeInnerPE;
	unsigned char m_bfmeGapPE[0x472];
	unsigned short m_bfmeKeyPE;
};

class BfmeEntryPE
{
public:
	int m_bfmeSparePE;
	BfmeThingPE *m_bfmeThingPE;
};

class BfmeHolderPE
{
public:
	unsigned char m_bfmeHeadPE[8];
	BfmeEntryPE *m_bfmeEntryPE;
};

float __cdecl bfmeComparePE(BfmeHolderPE *second, BfmeHolderPE *first)
{
	BfmeThingPE *firstThing = first->m_bfmeEntryPE->m_bfmeThingPE;

	if (firstThing && firstThing->m_bfmeInnerPE)
		firstThing = firstThing->m_bfmeInnerPE->bfmeResolvePE();

	BfmeThingPE *secondThing = second->m_bfmeEntryPE->m_bfmeThingPE;

	if (secondThing && secondThing->m_bfmeInnerPE)
		secondThing = secondThing->m_bfmeInnerPE->bfmeResolvePE();

	return (float)(firstThing->m_bfmeKeyPE - secondThing->m_bfmeKeyPE);
}
