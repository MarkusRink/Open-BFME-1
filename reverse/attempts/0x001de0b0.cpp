// ?bfmeComparePD@@YAMPAVBfmeHolderPD@@0@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 81/89 bytes. The two resolve blocks, the movzx pair, the subtract, the
// parameter-slot reuse as the int->float buffer and the trailing fild all
// match; the whole 8-byte gap is two sites where retail reads the entry member
// as `add eax,4` + `mov eax,[eax]` and MSVC folds it to `mov eax,[eax+4]`.
//
// PROGRESS ON THAT SPLIT (it recurs across the whole 0x000022BB family, e.g.
// 0x0015A5B0): it is a derived-to-base pointer adjustment. Modelling the entry
// as `class Entry : public Head, public Slot` and binding
// `Slot &s = *holder->m_entry;` DOES emit the unfolded `add eax,4` +
// `mov eax,[eax]` -- but MSVC also inserts a null check (`test eax,eax; je;
// ... xor eax,eax`), which retail does not have, giving 101 bytes. Binding the
// reference as the DERIVED type folds it back (81); going through an
// intermediate derived reference first keeps the check. What is still missing
// is the spelling where the base adjust is unconditional.
class BfmeThingPD;

class BfmeInnerPD
{
public:
	BfmeThingPD *bfmeResolvePD(void);
};

class BfmeThingPD
{
public:
	int m_bfmeSparePD;
	BfmeInnerPD *m_bfmeInnerPD;
	unsigned char m_bfmeGapPD[0x472];
	unsigned short m_bfmeKeyPD;
};

class BfmeEntryPD
{
public:
	int m_bfmeSparePD;
	BfmeThingPD *m_bfmeThingPD;
};

class BfmeHolderPD
{
public:
	unsigned char m_bfmeHeadPD[8];
	BfmeEntryPD *m_bfmeEntryPD;
};

float __cdecl bfmeComparePD(BfmeHolderPD *first, BfmeHolderPD *second)
{
	BfmeThingPD *firstThing = first->m_bfmeEntryPD->m_bfmeThingPD;

	if (firstThing && firstThing->m_bfmeInnerPD)
		firstThing = firstThing->m_bfmeInnerPD->bfmeResolvePD();

	BfmeThingPD *secondThing = second->m_bfmeEntryPD->m_bfmeThingPD;

	if (secondThing && secondThing->m_bfmeInnerPD)
		secondThing = secondThing->m_bfmeInnerPD->bfmeResolvePD();

	return (float)(firstThing->m_bfmeKeyPD - secondThing->m_bfmeKeyPD);
}
