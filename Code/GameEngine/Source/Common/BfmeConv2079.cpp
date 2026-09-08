class BfmeThingJT
{
public:
	unsigned char m_bfmeHeadJT[0x264];
	void *m_bfme264JT;
	void *m_bfme268JT;
	int m_bfme26cJT;
	void *m_bfme270JT;
	void *m_bfme274JT;
	int m_bfme278JT;
	void *m_bfme27cJT;
	void *m_bfme280JT;
	void *m_bfme284JT;
	void *m_bfme288JT;
	void *m_bfme28cJT;
	void *m_bfme290JT;
};

void bfmeFreeOneJT(void *q);

void bfmeFreeJT(BfmeThingJT *p)
{
	if (p->m_bfme274JT != 0)
		bfmeFreeOneJT(p->m_bfme274JT);

	if (p->m_bfme28cJT != 0)
		bfmeFreeOneJT(p->m_bfme28cJT);

	if (p->m_bfme288JT != 0)
		bfmeFreeOneJT(p->m_bfme288JT);

	if (p->m_bfme280JT != 0)
		bfmeFreeOneJT(p->m_bfme280JT);

	if (p->m_bfme268JT != 0)
		bfmeFreeOneJT(p->m_bfme268JT);

	p->m_bfme274JT = 0;
	p->m_bfme28cJT = 0;
	p->m_bfme288JT = 0;
	p->m_bfme280JT = 0;
	p->m_bfme268JT = 0;
	p->m_bfme270JT = 0;
	p->m_bfme290JT = 0;
	p->m_bfme284JT = 0;
	p->m_bfme27cJT = 0;
	p->m_bfme264JT = 0;
}
