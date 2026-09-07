// ?d_00467510@@YAXXZ
// partial score=0.97 date=2026-09-07
class BfmeStrECT
{
public:
	BfmeStrECT(const char *text);
	BfmeStrECT(const BfmeStrECT &other) { m_bfmeDataECT = other.m_bfmeDataECT; }
	~BfmeStrECT();

	void *m_bfmeDataECT;
};

class BfmeHostECT
{
public:
	virtual void bfmeSlot00ECT();
	virtual void bfmeSlot01ECT();
	virtual void bfmeSlot02ECT();
	virtual void bfmeSlot03ECT();
	virtual void bfmeSlot04ECT();
	virtual void bfmeSlot05ECT();
	virtual void bfmeSlot06ECT();
	virtual void bfmeSlot07ECT();
	virtual void bfmeSlot08ECT();
	virtual void bfmeSlot09ECT();
	virtual void bfmeSlot10ECT();
	virtual void bfmeSlot11ECT();
	virtual void bfmeSlot12ECT();
	virtual void bfmeSlot13ECT();
	virtual void bfmeSlot14ECT();
	virtual void *bfmeLoadECT(BfmeStrECT dir, BfmeStrECT file, int a, int b, int c);

	void bfmeInitECT();

	unsigned char m_bfmeHeadECT[0x1bc];
	void *m_bfmeResultECT;
};

void BfmeHostECT::bfmeInitECT()
{
	m_bfmeResultECT = bfmeLoadECT(BfmeStrECT("Apt\\"), BfmeStrECT("Background.apt"), 1, 0, -1);
}
