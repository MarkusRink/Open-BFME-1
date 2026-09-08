// ?bfmeXferYT@BfmeHostYT@@QAEXPAVXfer@@@Z
// partial score=0.96 date=2026-09-08
struct BfmeVerYT
{
	unsigned char m_bfmeAYT;
	unsigned char m_bfmeBYT;
};

class GameClientRandomVariable
{
public:
	unsigned char m_bfmeHeadYT[0xc];
};

class Xfer
{
public:
	virtual void bfmeVA0() = 0;
	virtual void bfmeVA1() = 0;
	virtual void bfmeVA2() = 0;
	virtual void bfmeVA3() = 0;
	virtual void bfmeVA4() = 0;
	virtual void bfmeVA5() = 0;
	virtual void bfmeVA6() = 0;
	virtual void bfmeVA7() = 0;
	virtual void bfmeVA8() = 0;
	virtual void bfmeVA9() = 0;
	virtual void bfmeVersionYT(BfmeVerYT *v) = 0;
	virtual void bfmeVB11() = 0;
	virtual void bfmeVB12() = 0;
	virtual void bfmeVB13() = 0;
	virtual void bfmeVB14() = 0;
	virtual void bfmeVB15() = 0;
	virtual void bfmeVB16() = 0;
	virtual void bfmeVB17() = 0;
	virtual void bfmeVB18() = 0;
	virtual void bfmeVB19() = 0;
	virtual void bfmeVB20() = 0;
	virtual void bfmeVB21() = 0;
	virtual void bfmeVB22() = 0;
	virtual void bfmeVB23() = 0;
	virtual void bfmeVB24() = 0;
	virtual void bfmeVB25() = 0;
	virtual void bfmeXfer24YT(int *p) = 0;
	virtual void bfmeVC27() = 0;
	virtual void bfmeVC28() = 0;
	virtual void bfmeXfer3CYT(int *p) = 0;
	virtual void bfmeVD30() = 0;
	virtual void bfmeVD31() = 0;
	virtual void bfmeVD32() = 0;
	virtual void bfmeVD33() = 0;
	virtual void bfmeVD34() = 0;
	virtual void bfmeXferByteYT(unsigned char *p) = 0;
};

void xferRandomVariable(Xfer &x, GameClientRandomVariable &v);

class BfmeHostYT
{
public:
	void bfmeXferYT(Xfer *x);

	unsigned char m_bfmeHeadYT[0x1c];
	unsigned char m_bfme1CYT;
	unsigned char m_bfme1DYT;
	unsigned char m_bfmeGap1YT[6];
	int m_bfme24YT;
	GameClientRandomVariable m_bfme28YT;
	unsigned char m_bfme34YT;
	unsigned char m_bfmeGap2YT[7];
	int m_bfme3CYT;
	unsigned char m_bfme40YT;
};

void BfmeHostYT::bfmeXferYT(Xfer *x)
{
	BfmeVerYT v1;

	v1.m_bfmeAYT = 1;
	v1.m_bfmeBYT = 1;
	x->bfmeVersionYT(&v1);

	BfmeVerYT v2;

	v2.m_bfmeAYT = 1;
	v2.m_bfmeBYT = 1;
	x->bfmeVersionYT(&v2);

	xferRandomVariable(*x, m_bfme28YT);

	x->bfmeXfer24YT(&m_bfme24YT);
	x->bfmeXferByteYT(&m_bfme34YT);
	x->bfmeXferByteYT(&m_bfme1CYT);
	x->bfmeXferByteYT(&m_bfme1DYT);
	x->bfmeXferByteYT(&m_bfme34YT);
	x->bfmeXferByteYT(&m_bfme40YT);
	x->bfmeXfer3CYT(&m_bfme3CYT);
}
