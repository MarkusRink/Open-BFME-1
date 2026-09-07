// ?bfmeTryBY@BfmeHostBY@@QAEDPAX@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 120/122. The shape is right -- two 0x18-byte boxes zeroed on the stack, a
// slot-10 virtual handed both addresses, a thiscall test on the first box, and
// the two-guard tail that clears the byte member and returns 1.
// The residue is entirely in the zero fill:
//   retail  xor eax,eax / xor ecx,ecx, then twelve stores ALTERNATING
//           first.field[i] via eax, second.field[i] via ecx, and the two
//           lea/push of the argument addresses come AFTER the fill.
//   MSVC    hoists the two lea/push FIRST, which leaves eax/ecx busy, so it
//           falls back to ebx (a callee-saved register, costing push/pop) and
//           emits the twelve stores sequentially -- second in full, then first.
// Tried: aggregate `= {0,0,0,0,0,0}` init on both, and a default constructor
// that assigns the six fields. Identical output both ways.
// The alternating a[i]/b[i] order is the tell: it is what you get when the two
// fills are scheduled together, not two independent memsets. Next lever would
// be a source form that zeroes the pair field-by-field (a macro over both), or
// anything that stops the argument addresses being computed before the fill.
struct BfmeBoxBY
{
	int m_bfmeABY;
	int m_bfmeBBY;
	int m_bfmeCBY;
	int m_bfmeDBY;
	int m_bfmeEBY;
	int m_bfmeFBY;

	BfmeBoxBY()
	{
		m_bfmeABY = 0;
		m_bfmeBBY = 0;
		m_bfmeCBY = 0;
		m_bfmeDBY = 0;
		m_bfmeEBY = 0;
		m_bfmeFBY = 0;
	}

	char bfmeTestBY(void *arg);
};

class BfmeHostBY
{
public:
	virtual void bfmeSlot00BY();
	virtual void bfmeSlot01BY();
	virtual void bfmeSlot02BY();
	virtual void bfmeSlot03BY();
	virtual void bfmeSlot04BY();
	virtual void bfmeSlot05BY();
	virtual void bfmeSlot06BY();
	virtual void bfmeSlot07BY();
	virtual void bfmeSlot08BY();
	virtual void bfmeSlot09BY();
	virtual void bfmeFillBY(BfmeBoxBY *first, BfmeBoxBY *second);

	char bfmeTryBY(void *arg);

	unsigned char m_bfmeHeadBY[4];
	unsigned char m_bfmeFlagBY;
};

char BfmeHostBY::bfmeTryBY(void *arg)
{
	BfmeBoxBY second;
	BfmeBoxBY first;

	bfmeFillBY(&first, &second);

	if (first.bfmeTestBY(arg) == 0)
		return 0;

	if (m_bfmeFlagBY == 0)
		return 0;

	m_bfmeFlagBY = 0;

	return 1;
}
