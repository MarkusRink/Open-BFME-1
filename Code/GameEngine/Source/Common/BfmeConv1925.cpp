class BfmeSubCN
{
public:
	virtual void bfmeSlot00CN();
	virtual void bfmeSlot01CN();
	virtual void bfmeSlot02CN();
	virtual void bfmeSlot03CN();
	virtual void bfmeSlot04CN();
	virtual void bfmeSlot05CN();
	virtual void bfmeSlot06CN();
	virtual void bfmeSlot07CN();
	virtual void bfmeSlot08CN();
	virtual void bfmeSlot09CN();
	virtual void bfmeSlot10CN();
	virtual void bfmeSlot11CN();
	virtual void bfmeSlot12CN();
	virtual void bfmeSlot13CN();
	virtual void bfmeSlot14CN();
	virtual void bfmeSlot15CN();
	virtual void bfmeSlot16CN();
	virtual void bfmeSlot17CN();
	virtual void bfmeSlot18CN();
	virtual void bfmeSlot19CN();
	virtual void bfmeSlot20CN();
	virtual void bfmeSlot21CN();
	virtual void bfmeSlot22CN();
	virtual void bfmeSlot23CN();
	virtual void bfmeSlot24CN();
	virtual void bfmeSlot25CN();
	virtual void bfmeSlot26CN();
	virtual void bfmeSlot27CN();
	virtual void bfmeSlot28CN();
	virtual void bfmeSlot29CN();
	virtual void bfmeSlot30CN();
	virtual void bfmeSlot31CN();
	virtual void bfmeSlot32CN();
	virtual void bfmeSlot33CN();
	virtual void bfmeSlot34CN();
	virtual void bfmeSlot35CN();
	virtual void bfmeSlot36CN();
	virtual void bfmeSlot37CN();
	virtual void bfmeSlot38CN();
	virtual void bfmeSlot39CN();
	virtual void bfmeSlot40CN();
	virtual void bfmeSlot41CN();
	virtual void bfmeSlot42CN();
	virtual void bfmeSlot43CN();
	virtual void bfmeSlot44CN();
	virtual void bfmeSlot45CN();
	virtual void bfmeSlot46CN();
	virtual void bfmeSlot47CN();
	virtual void bfmeSlot48CN();
	virtual void bfmeSlot49CN();
	virtual void bfmeSlot50CN();
	virtual void bfmeSlot51CN();
	virtual void bfmeSlot52CN();
	virtual void bfmeSlot53CN();
	virtual void bfmeSlot54CN();
	virtual void bfmeSlot55CN();
	virtual void bfmeSlot56CN();
	virtual void bfmeStopCN();
};

class BfmeUnitCN
{
public:
	void bfmeDoneCN();

	unsigned char m_bfmeHeadCN[0x1fc];
	BfmeSubCN *m_bfmeSubCN;
};

class BfmeOwnerCN
{
public:
	unsigned char m_bfmeHeadCN[0x10];
	BfmeUnitCN *m_bfmeUnitCN;
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadCN[0x3c];
	unsigned int m_bfmeFrameCN;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeHostCN
{
public:
	int bfmeTickCN();
	void bfmeBeginCN(BfmeUnitCN *u);

	unsigned char m_bfmeHeadCN[0x1c];
	BfmeOwnerCN *m_bfmeOwnerCN;
	unsigned char m_bfmePadCN[8];
	unsigned int m_bfmeSecondCN;
	unsigned int m_bfmeFirstCN;
};

int BfmeHostCN::bfmeTickCN()
{
	BfmeUnitCN *u = m_bfmeOwnerCN->m_bfmeUnitCN;

	if (u == 0)
		return -2;

	bfmeBeginCN(u);

	if (m_bfmeFirstCN <= TheBfmeGameLogic->m_bfmeFrameCN)
	{
		BfmeSubCN *s = u->m_bfmeSubCN;

		if (s != 0)
			s->bfmeStopCN();

		m_bfmeFirstCN = 0xffffffff;
	}

	if (m_bfmeSecondCN <= TheBfmeGameLogic->m_bfmeFrameCN)
	{
		u->bfmeDoneCN();

		return -1;
	}

	return 0;
}
