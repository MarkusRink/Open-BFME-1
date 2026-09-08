// ?bfmeWalkGE@@YAXXZ
// partial score=0.72 date=2026-09-08
extern char *g_bfmeTwoSJA;

class BfmeNodeGE
{
public:
	BfmeNodeGE *volatile m_bfmeNextGE;
	int m_bfmeKeyGE;
	unsigned char m_bfmeGapGE[0x24];
	volatile char m_bfmeFlagGE;
};

class BfmeVecGE
{
public:
	int bfmeIndexGE(int *key, int n);

	unsigned char m_bfmeHeadGE[4];
	int m_bfmeBeginGE;
	int m_bfmeEndGE;
};

class BfmePairGE
{
public:
	BfmeNodeGE *m_bfmeNodeGE;
	BfmeVecGE *m_bfmeVecGE;
};

class BfmeSrcGE
{
public:
	BfmePairGE bfmeFirstGE();
};

void bfmeWalkGE()
{
	BfmePairGE it = ((BfmeSrcGE *)&g_bfmeTwoSJA)->bfmeFirstGE();
	BfmeNodeGE *p = it.m_bfmeNodeGE;

	if (p != 0)
	{
		BfmeVecGE *v = it.m_bfmeVecGE;

		do
		{
			p->m_bfmeFlagGE = 0;

			BfmeNodeGE *q = p->m_bfmeNextGE;

			if (q != 0)
			{
				p = q;
				continue;
			}

			int n = (v->m_bfmeEndGE - v->m_bfmeBeginGE) >> 2;
			int *key = &p->m_bfmeKeyGE;
			int i = v->bfmeIndexGE(key, n);
			int m = (v->m_bfmeEndGE - v->m_bfmeBeginGE) >> 2;

			p = 0;

			while ((unsigned int)++i < (unsigned int)m && (p = ((BfmeNodeGE **)*(volatile int *)&v->m_bfmeBeginGE)[i]) == 0)
				;
		}
		while (p != 0);
	}
}
