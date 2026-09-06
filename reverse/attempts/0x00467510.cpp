// ?bfmeInitCT@BfmeOwnCT@@QAEXXZ (identity unknown)
// partial score=0.95 date=2026-09-07
// 106/112 at exact size. Two AsciiString temporaries built IN PLACE in the
// outgoing argument area (the recipe from 0x00522DD0: real ctor, inline copy
// ctor, destructor declared but not defined), three integer arguments -1/0/1
// pushed ahead of them, a virtual at slot 15 and the result stored at +0x1c0.
// Residue: BOTH esp markers land one instruction late -- retail writes
// `mov [esp+N],esp` BEFORE `mov ecx,esp`, MSVC after. Same two-instruction
// swap as 0x0034C710 and 0x006F9A30; dropping the inline copy ctor, declaring
// it instead, and throw() on the destructor all leave it unchanged.
extern "C" char _bfmeLit1CT[];
extern "C" char _bfmeLit2CT[];

class BfmeStrCT
{
public:
	BfmeStrCT(const char *text);
	BfmeStrCT(const BfmeStrCT &other) throw() { m_bfmeDataCT = other.m_bfmeDataCT; }
	~BfmeStrCT();

	int m_bfmeDataCT;
};

class BfmeOwnCT
{
public:
	virtual void bfmeSlot00CT(void);
	virtual void bfmeSlot01CT(void);
	virtual void bfmeSlot02CT(void);
	virtual void bfmeSlot03CT(void);
	virtual void bfmeSlot04CT(void);
	virtual void bfmeSlot05CT(void);
	virtual void bfmeSlot06CT(void);
	virtual void bfmeSlot07CT(void);
	virtual void bfmeSlot08CT(void);
	virtual void bfmeSlot09CT(void);
	virtual void bfmeSlot10CT(void);
	virtual void bfmeSlot11CT(void);
	virtual void bfmeSlot12CT(void);
	virtual void bfmeSlot13CT(void);
	virtual void bfmeSlot14CT(void);
	virtual void *bfmeRunCT(class BfmeStrCT first, class BfmeStrCT second, int a, int b, int c);

	void bfmeInitCT(void);

	unsigned char m_bfmeHeadCT[0x1bc];
	void *m_bfmeResultCT;
};

void BfmeOwnCT::bfmeInitCT(void)
{
	m_bfmeResultCT = bfmeRunCT(BfmeStrCT(_bfmeLit2CT), BfmeStrCT(_bfmeLit1CT), 1, 0, -1);
}
