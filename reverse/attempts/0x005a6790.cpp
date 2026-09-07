// ?bfmeSetCursorCE@BfmeHostCE@@QAEPAXPAX@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 60/60 at exact size. Only the two scratch registers in the final virtual call
// are swapped: retail holds the argument in edx and the vftable in eax, MSVC the
// reverse (4 modrm bytes). Hoisting the argument into a local and hoisting the
// receiver global into a local both leave it unchanged -- same wall as
// [[chain-middle-link-flip]].
struct Rva00579160Manager
{
	char bfmeCheckCE();
};

extern Rva00579160Manager *Rva00579160TheManager;

struct Rva005A63D0Mouse
{
	virtual void bfmeSlot00CE();
	virtual void bfmeSlot01CE();
	virtual void bfmeSlot02CE();
	virtual void bfmeSlot03CE();
	virtual void bfmeSlot04CE();
	virtual void bfmeSlot05CE();
	virtual void bfmeSlot06CE();
	virtual void bfmeSlot07CE();
	virtual void bfmeSlot08CE();
	virtual void bfmeSlot09CE();
	virtual void bfmeSlot10CE();
	virtual void bfmeSlot11CE();
	virtual void bfmeSlot12CE();
	virtual void bfmeSlot13CE();
	virtual void bfmeApplyCE(void *cursor);
};

extern Rva005A63D0Mouse *TheMouse;

class BfmeHostCE
{
public:
	void *bfmeSetCursorCE(void *cursor);

	unsigned char m_bfmeHeadCE[0x1ec];
	void *m_bfmeCursorCE;
};

void *BfmeHostCE::bfmeSetCursorCE(void *cursor)
{
	void *old = m_bfmeCursorCE;

	m_bfmeCursorCE = cursor;

	if (Rva00579160TheManager->bfmeCheckCE() != 0)
		TheMouse->bfmeApplyCE(m_bfmeCursorCE);

	return old;
}
