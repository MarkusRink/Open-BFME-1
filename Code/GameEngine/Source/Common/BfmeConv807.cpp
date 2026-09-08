class BfmeSubEEA
{
public:
	void bfmeCallEEA();
};

struct BfmeThingEEA
{
	void bfmeGoEEAa();
	void bfmeGoEEAb();
	void bfmeOneEEA();
	unsigned char m_bfmeHeadA[0x630];
	BfmeSubEEA m_bfmeA;
	unsigned char m_bfmeHeadB[0x1b];
	BfmeSubEEA m_bfmeB;
	unsigned char m_bfmeHeadC[0x1b];
	char m_bfmeFlag;
};

void BfmeThingEEA::bfmeGoEEAa()
{
	bfmeOneEEA();
	m_bfmeA.bfmeCallEEA();
	m_bfmeB.bfmeCallEEA();
	m_bfmeFlag = 1;
}

void BfmeThingEEA::bfmeGoEEAb()
{
	bfmeOneEEA();
	m_bfmeA.bfmeCallEEA();
	m_bfmeB.bfmeCallEEA();
	m_bfmeFlag = 1;
}
