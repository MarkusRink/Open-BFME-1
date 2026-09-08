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

struct BfmeThingEEB
{
	void bfmeGoEEBa(void *a);
	void bfmeGoEEBb(void *a);
	unsigned char m_bfmeHead[0x80];
	void (__cdecl *m_bfmeFn)(void *a, void *ctx, int flag);
	void *m_bfmeCtx;
};

void BfmeThingEEB::bfmeGoEEBa(void *a)
{
	void (__cdecl *fn)(void *, void *, int) = m_bfmeFn;
	if (fn)
	{
		void *ctx = m_bfmeCtx;
		if (ctx)
			fn(a, ctx, 1);
	}
}

void BfmeThingEEB::bfmeGoEEBb(void *a)
{
	void (__cdecl *fn)(void *, void *, int) = m_bfmeFn;
	if (fn)
	{
		void *ctx = m_bfmeCtx;
		if (ctx)
			fn(a, ctx, 0);
	}
}
