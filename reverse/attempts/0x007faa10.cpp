// ?bfmeAllocABD@BfmeHostABD@@QAEHPBDPAX11@Z
// partial score=0.88 date=2026-09-08
void *Rva00807920(const char *name, int cap);

class Rva00803080;

class Rva007EAServiceList
{
public:
	void add(Rva00803080 *entry);
};

class BfmeRegABD
{
public:
	virtual void bfmeSlot0ABD();
	virtual void bfmeSlot1ABD();
	virtual void bfmeSlot2ABD();
	virtual void bfmeRegisterABD(const char *a, const char *b, int c);
};

BfmeRegABD *bfmeRegistryABD(void);

extern const char g_bfmeNameABD[];
extern const char g_bfmeKindABD[];

struct BfmeSlotABD
{
	void *m_bfme00ABD;
	void *m_bfme04ABD;
	void *m_bfme08ABD;
	void *m_bfme0CABD;
};

class BfmeHostABD
{
public:
	int bfmeAllocABD(const char *name, void *a, void *b, void *c);

	unsigned char m_bfmeHeadABD[4];
	Rva00803080 *m_bfme04ABD;
	BfmeSlotABD m_bfmeSlotsABD[4];
	int m_bfme48ABD;
	Rva007EAServiceList *m_bfme4CABD;
};

int BfmeHostABD::bfmeAllocABD(const char *name, void *a, void *b, void *c)
{
	if (m_bfme48ABD < 4)
	{
		int idx = -1;

		for (int i = 0; i < 4; ++i)
		{
			if (m_bfmeSlotsABD[i].m_bfme00ABD == 0)
			{
				idx = i;
				break;
			}
		}

		if (idx == -1)
			bfmeRegistryABD()->bfmeRegisterABD(g_bfmeNameABD, g_bfmeKindABD, 0x60);

		BfmeSlotABD *s = &m_bfmeSlotsABD[idx];

		s->m_bfme00ABD = b;
		s->m_bfme04ABD = c;
		s->m_bfme08ABD = a;
		s->m_bfme0CABD = Rva00807920(name, 0x2710);

		++m_bfme48ABD;

		m_bfme4CABD->add(m_bfme04ABD);

		return 0;
	}

	return -1;
}
