// ??0BfmeThingIB@@QAE@XZ
// partial score=0.75 date=2026-09-08
extern "C" void *bfmeVftIB[];

class BfmeSixIB
{
public:
	void bfmeClearIB()
	{
		m_bfmeA0IB = 0;
		m_bfmeA1IB = 0;
		m_bfmeA2IB = 0;
		m_bfmeA3IB = 0;
		m_bfmeA4IB = 0;
		m_bfmeA5IB = 0;
	}

	int m_bfmeA0IB;
	int m_bfmeA1IB;
	int m_bfmeA2IB;
	int m_bfmeA3IB;
	int m_bfmeA4IB;
	int m_bfmeA5IB;
};

class BfmeBaseIB
{
public:
	BfmeBaseIB();

	void *volatile m_bfmeVftIB;
	unsigned char m_bfmeGapIB[0x54];
};

class BfmeThingIB : public BfmeBaseIB
{
public:
	BfmeThingIB();

	int m_bfme58IB;
	int m_bfme5cIB;
	float m_bfme60IB;
	float m_bfme64IB;
	char m_bfme68IB;
	unsigned char m_bfmePadIB[3];
	int m_bfme6cIB;
	int m_bfme70IB;
	int m_bfme74IB;
	int m_bfme78IB;
	int m_bfme7cIB;
	int m_bfme80IB;
	int m_bfme84IB;
	int m_bfme88IB;
	BfmeSixIB m_bfme8cIB;
};

BfmeThingIB::BfmeThingIB()
{
	m_bfmeVftIB = bfmeVftIB;
	m_bfme7cIB = 0;
	m_bfme80IB = 0;
	m_bfme84IB = 0;

	BfmeSixIB *p = &m_bfme8cIB;
	BfmeSixIB *q = p;

	q->bfmeClearIB();

	m_bfme58IB = 0;
	m_bfme68IB = 1;
	m_bfme5cIB = 0;
	m_bfme60IB = 3.14159274f;
	m_bfme64IB = -1.0f;
	m_bfme6cIB = 0;
	m_bfme70IB = 0x16;
	m_bfme74IB = 0;
	m_bfme78IB = 0xf;
	m_bfme88IB = 0;

	p->bfmeClearIB();
}
