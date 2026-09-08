// ?d_007510d0@@YAXXZ
// partial score=0.88 date=2026-09-08
extern "C" void *bfmeVft1TJ[];
extern "C" void *bfmeVftTJ[];

class BfmeItemTJ
{
public:
	virtual void bfmeDestroyTJ();

	int m_bfmeRefTJ;
};

class BfmeGlobPB
{
public:
	virtual void bfmeSlot00TJ();
	virtual void bfmeSlot01TJ();
	virtual void bfmeSlot02TJ();
	virtual void bfmeDetachTJ(BfmeItemTJ *item);
};

class BfmeGlobQE;

extern BfmeGlobQE *g_bfmeGlobQE;
extern BfmeGlobPB *g_bfmeGlobPB;

void __stdcall bfmeReleaseTJ(void *item);

class BfmeBase2TJ
{
public:
	~BfmeBase2TJ();

	void *volatile m_bfmeVftTJ;
	unsigned char m_bfmeHeadTJ[8];
};

class BfmeBase1TJ : public BfmeBase2TJ
{
public:
	__forceinline ~BfmeBase1TJ() { m_bfmeVftTJ = bfmeVftTJ; }
};

class BfmeHostTJ : public BfmeBase1TJ
{
public:
	~BfmeHostTJ();

	BfmeItemTJ *m_bfmeItemTJ;
	void *m_bfmeOtherTJ;
};

BfmeHostTJ::~BfmeHostTJ()
{
	m_bfmeVftTJ = bfmeVft1TJ;

	if (g_bfmeGlobQE != 0 && m_bfmeOtherTJ != 0)
	{
		bfmeReleaseTJ(m_bfmeOtherTJ);

		m_bfmeOtherTJ = 0;
	}

	if (m_bfmeItemTJ != 0)
	{
		g_bfmeGlobPB->bfmeDetachTJ(m_bfmeItemTJ);

		if (m_bfmeItemTJ != 0)
		{
			if (--m_bfmeItemTJ->m_bfmeRefTJ == 0)
				m_bfmeItemTJ->bfmeDestroyTJ();
		}

		m_bfmeItemTJ = 0;
	}
}
