// ?bfmeStopPT@BfmeOwnerPT@@QAEHXZ (identity unknown)
// partial score=0.95 date=2026-09-07
// 72/72 bytes; 9 of 20 instructions differ, purely from where the
// `mode == 1 || mode == 5` block lands. Retail places it right after the two
// compares (`cmp eax,1; je A; cmp eax,5; jne rest; A: call; mov eax,1; ret`)
// and the mode==2 path after it; MSVC sinks the A block past everything and
// jumps forward to it.
// Settled: the guard byte is cleared before reading the mode, both callees are
// thiscall with no arguments, every exit returns 1 (the early guard shares the
// same `mov eax,1`), and the mode==2 write is a byte store.
// Tried: a `switch` with `case 1: case 5:` (68 bytes -- worse).
struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadPT[0x10c];
	int m_bfmeModePT;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerPT
{
public:
	int bfmeStopPT(void);
	void bfmeCallAPT(void);
	void bfmeCallBPT(void);

	unsigned char m_bfmeHeadPT[0x259];
	char m_bfmeFlagPT;
	char m_bfmeActivePT;
};

int BfmeOwnerPT::bfmeStopPT(void)
{
	if (m_bfmeActivePT)
	{
		m_bfmeActivePT = 0;

		int mode = TheBfmeGameLogic->m_bfmeModePT;

		if (mode == 1 || mode == 5)
		{
			bfmeCallAPT();
			return 1;
		}

		if (mode == 2)
			m_bfmeFlagPT = 1;

		bfmeCallBPT();
	}

	return 1;
}
