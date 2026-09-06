// ?bfmeSweepKQ@@YGXPAVBfmeWrapKQ@@@Z (identity unknown)
// partial score=0.92 date=2026-09-07
// 81/81 bytes. Shape is settled and both copies of the inlined next() line up:
// the first next() must be PEELED (`thing = next(); while (thing) { ...; thing
// = next(); }`) -- a `while ((thing = next()))` collapses the two copies into
// one rotated loop at 54 bytes -- and the advance must be a post-increment in
// the return statement (`return (m_cur++)->m_thing;`), which is what makes the
// size exact.
// Residue: a whole-body register mirror. Retail keeps *wrap in ecx, so the
// cursor lands in eax and needs `mov edx,eax` before the load; MSVC keeps *wrap
// in edx, puts the cursor in ecx and skips the copy, spending the saved bytes
// on `jmp` + padding where retail has a 3-byte `lea ecx,[ecx]` align nop.
// 15 of 30 instructions differ, all by register name only. /G7, /Oy and /Ob1
// change nothing. ecx/edx-flip class.
class BfmeSubKQ
{
public:
	void bfmeDoKQ(int first, int second, int third);
};

class BfmeThingKQ
{
public:
	unsigned char m_bfmeHeadKQ[0x210];
	BfmeSubKQ *m_bfmeSubKQ;
};

struct BfmeSlotKQ
{
	BfmeThingKQ *m_bfmeThingKQ;
	int m_bfmeSpareKQ;
};

class BfmeCursorKQ
{
public:
	BfmeThingKQ *bfmeNextKQ(void)
	{
		if (m_bfmeCurKQ == m_bfmeEndKQ)
			return 0;

		return (m_bfmeCurKQ++)->m_bfmeThingKQ;
	}

	int m_bfmeHeadKQ;
	BfmeSlotKQ *m_bfmeEndKQ;
	int m_bfmeSpareKQ;
	BfmeSlotKQ *m_bfmeCurKQ;
};

class BfmeWrapKQ
{
public:
	BfmeCursorKQ *m_bfmeCursorKQ;
};

void __stdcall bfmeSweepKQ(BfmeWrapKQ *wrap)
{
	BfmeThingKQ *thing = wrap->m_bfmeCursorKQ->bfmeNextKQ();

	while (thing)
	{
		if (thing->m_bfmeSubKQ)
			thing->m_bfmeSubKQ->bfmeDoKQ(1, 1, 0);

		thing = wrap->m_bfmeCursorKQ->bfmeNextKQ();
	}
}
