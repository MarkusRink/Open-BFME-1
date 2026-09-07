// ?bfmeSetGN@BfmeOwnerGN@@QAEXD@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 93/97 bytes. The two flat ifs with their re-test of the same byte, the shared
// zero register (xor edx,edx driving every cmp and store) and the whole call
// all reproduce.
// Two things were needed to get here: the flat `if (a && !b) {...; return;}
// if (!a && b) {...}` pair rather than if/else, and the resolve written as an
// explicit THREE-WAY (`if (t == 0) r = 0; else if (t->m_inner == 0) r = t;
// else r = t->m_inner->resolve();`) -- that is what produces retail's
// `xor eax,eax; jmp` for the null arm. The two-line `if (t && t->m_inner)`
// form is 4 bytes shorter and has no explicit zero.
// Residues: (1) retail stores m_10/m_14 before loading m_4, MSVC after;
// (2) retail computes the tag argument into edx before the three pushes, MSVC
// after them (hoisting it into a local first does not move it); (3) the
// 4-byte `mov [esp+18h],eax` dead store of the value into the parameter home
// slot is not reproduced -- that is the whole size gap.
class BfmeThingGN;

class BfmeInnerGN
{
public:
	BfmeThingGN *bfmeResolveGN(void);
};

class BfmeThingGN
{
public:
	int m_bfmeSpareGN;
	BfmeInnerGN *m_bfmeInnerGN;
	unsigned char m_bfmeGapGN[8];
	void *m_bfmeValueGN;
};

class BfmeSourceGN
{
public:
	unsigned char m_bfmeHeadGN[8];
	void *m_bfmeTagGN;
};

void __cdecl bfmeReportGN(void *tag, void *first, void *second, void *third);

class BfmeOwnerGN
{
public:
	void bfmeSetGN(char active);

	int m_bfmeSpareGN;
	BfmeThingGN *m_bfmeThingGN;
	int m_bfmePadGN;
	BfmeSourceGN *m_bfmeSourceGN;
	char m_bfmeActiveGN;
	unsigned char m_bfmeGapGN[3];
	int m_bfmeStampGN;
};

void BfmeOwnerGN::bfmeSetGN(char active)
{
	if (m_bfmeActiveGN != 0 && active == 0)
	{
		m_bfmeActiveGN = 0;
		m_bfmeStampGN = 0;

		BfmeThingGN *thing = m_bfmeThingGN;
		BfmeThingGN *resolved;

		if (thing == 0)
			resolved = 0;
		else if (thing->m_bfmeInnerGN == 0)
			resolved = thing;
		else
			resolved = thing->m_bfmeInnerGN->bfmeResolveGN();

		void *value = resolved->m_bfmeValueGN;

		void *tag = m_bfmeSourceGN->m_bfmeTagGN;

		bfmeReportGN(tag, value, value, value);
		return;
	}

	if (m_bfmeActiveGN == 0 && active != 0)
	{
		m_bfmeActiveGN = 1;
		m_bfmeStampGN = 0;
	}
}
