// ?bfmeCountXL@BfmeHostXL@@QAEHPAVBfmeCheckFH@@@Z
// partial score=0.97 date=2026-09-08
class BfmeCheckFH
{
public:
	char bfmeCheckFH(void *p);
};

struct BfmeNodeXL
{
	unsigned char m_bfmeHeadXL[4];
	int m_bfme04XL;
	void *m_bfme08XL;
};

class BfmeHostXL
{
public:
	int bfmeCountXL(BfmeCheckFH *chk);

	virtual void bfmeVH0() = 0;
	virtual void bfmeVH1() = 0;
	virtual void bfmeVH2() = 0;
	virtual void bfmeVH3() = 0;
	virtual void bfmeVH4() = 0;
	virtual void bfmeVH5() = 0;
	virtual void bfmeVH6() = 0;
	virtual void bfmeVH7() = 0;
	virtual void bfmeVH8() = 0;
	virtual void bfmeVH9() = 0;
	virtual void bfmeVH10() = 0;
	virtual void bfmeVH11() = 0;
	virtual void bfmeVH12() = 0;
	virtual void bfmeVH13() = 0;
	virtual void bfmeVH14() = 0;
	virtual void bfmeVH15() = 0;
	virtual void bfmeVH16() = 0;
	virtual void bfmeVH17() = 0;
	virtual BfmeNodeXL *bfmeFirstXL() = 0;
	virtual BfmeNodeXL *bfmeNextXL(BfmeNodeXL *p) = 0;
};

int BfmeHostXL::bfmeCountXL(BfmeCheckFH *chk)
{
	int n = 0;
	BfmeNodeXL *p = bfmeFirstXL();

	while (p)
	{
		if (p->m_bfme04XL == 1 && chk->bfmeCheckFH(p->m_bfme08XL))
			n++;

		p = bfmeNextXL(p);
	}

	return n;
}
