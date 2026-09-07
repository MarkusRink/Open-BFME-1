// ?bfmeStopBL@BfmeHostBL@@QAEXPAX@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 47/47. Sibling of 0x002B6390 (same +0x1c/+0x10/+0x204 chain, same class) and
// the SAME two-instruction residue: retail carries the middle link in eax,
// MSVC moves it straight to ecx. Everything else matches, including the
// shrink-wrapped `push esi` inside the guard, the `ret 4` for the unused
// parameter, and `push -1` for the int argument.
// Five spellings tried across the two bodies (locals per link, one local, no
// locals, an inline accessor for the middle link, accessors for BOTH links) --
// all produce the identical ecx form. Treat this chain shape as a known
// 2-instruction residue class and do not re-sweep it.
class BfmeDBL;

class BfmeCBL
{
public:
	virtual void bfmeSlot00C();
	virtual void bfmeSlot01C();
	virtual void bfmeSlot02C();
	virtual void bfmeSlot03C();
	virtual void bfmeSlot04C();
	virtual void bfmeSlot05C();
	virtual void bfmeSlot06C();
	virtual void bfmeSlot07C();
	virtual void bfmeSlot08C();
	virtual void bfmeSlot09C();
	virtual void bfmeSlot10C();
	virtual void bfmeSlot11C();
	virtual void bfmeSlot12C();
	virtual void bfmeSlot13C();
	virtual void bfmeSlot14C();
	virtual void bfmeSlot15C();
	virtual void bfmeSlot16C();
	virtual void bfmeSlot17C();
	virtual void bfmeSlot18C();
	virtual void bfmeSlot19C();
	virtual void bfmeSlot20C();
	virtual void bfmeSlot21C();
	virtual void bfmeSlot22C();
	virtual void bfmeSlot23C();
	virtual void bfmeSlot24C();
	virtual void bfmeSlot25C();
	virtual void bfmeSlot26C();
	virtual void bfmeSlot27C();
	virtual void bfmeSlot28C();
	virtual void bfmeSlot29C();
	virtual void bfmeSlot30C();
	virtual void bfmeSlot31C();
	virtual void bfmeSlot32C();
	virtual void bfmeSlot33C();
	virtual void bfmeSlot34C();
	virtual void bfmeSlot35C();
	virtual void bfmeSlot36C();
	virtual void bfmeSlot37C();
	virtual void bfmeSlot38C();
	virtual void bfmeSlot39C();
	virtual void bfmeSlot40C();
	virtual void bfmeSlot41C();
	virtual void bfmeSlot42C();
	virtual void bfmeSlot43C();
	virtual void bfmeSlot44C();
	virtual void bfmeSlot45C();
	virtual void bfmeSlot46C();
	virtual void bfmeSlot47C();
	virtual void bfmeSlot48C();
	virtual void bfmeSlot49C();
	virtual void bfmeSlot50C();
	virtual void bfmeSlot51C();
	virtual void bfmeSlot52C();
	virtual void bfmeSlot53C();
	virtual void bfmeSlot54C();
	virtual void bfmeSlot55C();
	virtual void bfmeSlot56C();
	virtual void bfmeSlot57C();
	virtual void bfmeSlot58C();
	virtual void bfmeSlot59C();
	virtual void bfmeSlot60C();
	virtual void bfmeSlot61C();
	virtual void bfmeSlot62C();
	virtual void bfmeSlot63C();
	virtual void bfmeSlot64C();
	virtual void bfmeSlot65C();
	virtual void bfmeSlot66C();
	virtual void bfmeSlot67C();
	virtual void bfmeSlot68C();
	virtual void bfmeSlot69C();
	virtual void bfmeSlot70C();
	virtual void bfmeSlot71C();
	virtual void bfmeSlot72C();
	virtual void bfmeSlot73C();
	virtual void bfmeSlot74C();
	virtual void bfmeSlot75C();
	virtual void bfmeSlot76C();
	virtual void bfmeSlot77C();
	virtual void bfmeSlot78C();
	virtual BfmeDBL *bfmeGetBL();
};

class BfmeDBL
{
public:
	virtual void bfmeSlot00D();
	virtual void bfmeSlot01D();
	virtual void bfmeSlot02D();
	virtual void bfmeSlot03D();
	virtual void bfmeSlot04D();
	virtual void bfmeSlot05D();
	virtual void bfmeSlot06D();
	virtual void bfmeSlot07D();
	virtual void bfmeSlot08D();
	virtual void bfmeSlot09D();
	virtual void bfmeSetBL(int value);
	virtual void bfmeSlot11D();
	virtual void bfmeSlot12D();
	virtual void bfmeSlot13D();
	virtual void bfmeSlot14D();
	virtual void bfmeSlot15D();
	virtual void bfmeSlot16D();
	virtual void bfmeSlot17D();
	virtual void bfmeSlot18D();
	virtual void bfmeSlot19D();
	virtual void bfmeSlot20D();
	virtual void bfmeSlot21D();
	virtual void bfmeSlot22D();
	virtual void bfmeSlot23D();
	virtual void bfmeApplyBL();
};

class BfmeBBL
{
public:
	unsigned char m_bfmeHeadBL[0x204];
	BfmeCBL *m_bfmeCBL;
};

class BfmeABL
{
public:
	BfmeBBL *bfmeGetBBL() { return m_bfmeBBL; }

	unsigned char m_bfmeHeadBL[0x10];
	BfmeBBL *m_bfmeBBL;
};

class BfmeHostBL
{
public:
	void bfmeStopBL(void *unused);

	unsigned char m_bfmeHeadBL[0x1c];
	BfmeABL *m_bfmeABL;
};

void BfmeHostBL::bfmeStopBL(void *unused)
{
	BfmeCBL *c = m_bfmeABL->bfmeGetBBL()->m_bfmeCBL;

	if (c != 0)
	{
		BfmeDBL *d = c->bfmeGetBL();

		d->bfmeSetBL(-1);
		d->bfmeApplyBL();
	}
}
