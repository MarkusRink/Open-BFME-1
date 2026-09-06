extern "C" int _bfmeVftVE[];
extern "C" int _bfmeVftXB[];

class BfmeInnerCN
{
public:
	void bfmeCloseCN(void *value);

	int m_bfmeDataCN;
};

class BfmeBaseVE
{
public:
	~BfmeBaseVE()
	{
		m_bfmeVfVE = _bfmeVftVE;

		m_bfmeInnerVE->bfmeCloseCN(m_bfmeArgVE);
	}

	int *volatile m_bfmeVfVE;
	BfmeInnerCN *m_bfmeInnerVE;
	void *m_bfmeArgVE;
	int m_bfmePadVE[2];
};

class BfmeItemCP
{
public:
	virtual void bfmeReleaseCP(int flag);
};

class BfmeOwnCP : public BfmeBaseVE
{
public:
	~BfmeOwnCP(void);

	int m_bfmePad2CP;
	BfmeItemCP *m_bfmeItemsCP[32];
	volatile int m_bfmeCountCP;
};

BfmeOwnCP::~BfmeOwnCP(void)
{
	m_bfmeVfVE = _bfmeVftXB;

	for (int index = 0; index < m_bfmeCountCP; ++index)
	{
		BfmeItemCP *item = m_bfmeItemsCP[index];

		if (item)
			item->bfmeReleaseCP(1);
	}
}
