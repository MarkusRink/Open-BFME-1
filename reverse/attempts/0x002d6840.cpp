// ?bfmeTickJE@BfmeSelfJE@@QAEXXZ
// partial score=0.6 date=2026-09-08
class BfmeBlobJE
{
public:
	BfmeBlobJE()
	{
		m_bfmeF0JE = 0;
		m_bfmeF1JE = 0;
		m_bfmeF2JE = 0;
		m_bfmeF3JE = 0;
		m_bfmeF4JE = 0;
		m_bfmeF5JE = 0;
		m_bfmeF6JE = 0;
		m_bfmeF7JE = 0;
		m_bfmeF8JE = 0;
		m_bfmeF9JE = 0;
	}

	int m_bfmeF0JE;
	int m_bfmeF1JE;
	int m_bfmeF2JE;
	int m_bfmeF3JE;
	int m_bfmeF4JE;
	int m_bfmeF5JE;
	int m_bfmeF6JE;
	int m_bfmeF7JE;
	int m_bfmeF8JE;
	int m_bfmeF9JE;
};

class BfmeHostJE
{
public:
	void bfmeRunJE(void *a, void *b);
};

class BfmeDataJE
{
public:
	unsigned char m_bfmeHeadJE[0x70];
	int m_bfmeArrBJE[10];
	int m_bfmeArrAJE[10];
};

class BfmeSelfJE
{
public:
	void bfmeTickJE();
};

void BfmeSelfJE::bfmeTickJE()
{
	BfmeDataJE *d = *(BfmeDataJE **)((char *)this - 0xc);
	BfmeHostJE *h = *(BfmeHostJE **)((char *)this - 8);

	{
		int *a = d->m_bfmeArrAJE;
		unsigned int i = 0;
		int *p = a;

		for (;;)
		{
			if (*(volatile int *)p != 0)
			{
				BfmeBlobJE b;

				h->bfmeRunJE(a, &b);
				break;
			}

			++i;
			++p;

			if (i >= 10)
				break;
		}
	}

	{
		int *a = d->m_bfmeArrBJE;
		unsigned int i = 0;
		int *p = a;

		for (;;)
		{
			if (*(volatile int *)p != 0)
			{
				BfmeBlobJE b;

				h->bfmeRunJE(&b, a);
				break;
			}

			++i;
			++p;

			if (i >= 10)
				break;
		}
	}
}
