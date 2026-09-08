// ?bfmeSyncJN@BfmeSelfJN@@QAEXXZ
// partial score=0.98 date=2026-09-08
class BfmeLinkJN
{
public:
	BfmeLinkJN *m_bfmeNextJN;
};

class BfmeOwnJN
{
public:
	void bfmeNotifyJN();

	unsigned char m_bfmeHeadJN[0x110];
	int m_bfmeFlagsJN;
};

class BfmeEntryJN
{
public:
	void *m_bfme00JN;
	int m_bfme04JN;
	int m_bfme08JN;
	int m_bfme0cJN;
	int m_bfme10JN;
};

class BfmeSelfJN
{
public:
	virtual void bfmeVt00JN();
	virtual void bfmeVt01JN();
	virtual void bfmeVt02JN();
	virtual void bfmeVt03JN();
	virtual void bfmeVt04JN();
	virtual void bfmeVt05JN();
	virtual void bfmeVt06JN();
	virtual void bfmeVt07JN();
	virtual void bfmeVt08JN();
	virtual void bfmeVt09JN();
	virtual void bfmeVt10JN();
	virtual void bfmeVt11JN();
	virtual void bfmeVt12JN();
	virtual void bfmeVt13JN();
	virtual void bfmeVt14JN();
	virtual void bfmeVt15JN();
	virtual void bfmeVt16JN();
	virtual void bfmeVt17JN();
	virtual void bfmeVt18JN();
	virtual void bfmeVt19JN();
	virtual void bfmeVt20JN();
	virtual void bfmeVt21JN();
	virtual void bfmeVt22JN();
	virtual void bfmeVt23JN();
	virtual void bfmeVt24JN();
	virtual void bfmeVt25JN();
	virtual int bfmeMapJN(void *p);

	void bfmeSyncJN();
	void bfmeAJN();
	void bfmeBJN();

	unsigned char m_bfmeHeadJN[4];
	BfmeOwnJN *m_bfme08JN;
	unsigned char m_bfmeGap1JN[0x2c];
	BfmeLinkJN *m_bfme38JN;
	unsigned char m_bfmeGap2JN[0x9c];
	BfmeEntryJN m_bfmeEntriesJN[40];
};

void BfmeSelfJN::bfmeSyncJN()
{
	BfmeLinkJN *h = m_bfme38JN;
	BfmeLinkJN *p = h->m_bfmeNextJN;
	unsigned int n = 0;

	if (p != h)
	{
		do
		{
			p = p->m_bfmeNextJN;
			++n;
		}
		while (p != h);

		if (n > 0)
		{
			BfmeOwnJN *o = m_bfme08JN;
			int mask = 0x400;

			int fl = o->m_bfmeFlagsJN;

			if ((fl & mask) == 0)
			{
				fl |= mask;
				o->m_bfmeFlagsJN = fl;
				o->bfmeNotifyJN();
			}
		}
	}

	BfmeEntryJN tmp[40];

	for (int i = 0; i < 40; i++)
		tmp[i] = m_bfmeEntriesJN[i];

	bfmeAJN();
	bfmeBJN();

	for (int j = 0; j < 40; j++)
	{
		if (tmp[j].m_bfme00JN != 0)
		{
			int k = bfmeMapJN(tmp[j].m_bfme00JN);

			if (k != -1)
				m_bfmeEntriesJN[k].m_bfme08JN = tmp[j].m_bfme08JN;
		}
	}
}
