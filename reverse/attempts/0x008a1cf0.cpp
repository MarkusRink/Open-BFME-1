// ?bfmeLookupFJ@BfmeHostFJ@@QAEHH@Z
// partial score=0.92 date=2026-09-08
extern "C" int strcmp(const char *a, const char *b);

#pragma intrinsic(strcmp)

class BfmeItemFJ
{
public:
	const char *m_bfmeNameFJ;
	int m_bfmeValueFJ;
};

class BfmeGroupFJ
{
public:
	unsigned char m_bfmeHeadFJ[0x30];
	int m_bfmeCountFJ;
	BfmeItemFJ *m_bfmeItemsFJ;
};

class BfmeOwnerFJ
{
public:
	unsigned char m_bfmeHeadFJ[0x10];
	BfmeGroupFJ *m_bfmeGroupFJ;
};

class BfmeSlotFJ
{
public:
	void *m_bfmeHeadFJ;
	const char *m_bfmeNameFJ;
	unsigned char m_bfmeGapFJ[4];
	BfmeOwnerFJ *m_bfmeOwnerFJ;
};

class BfmeHostFJ
{
public:
	int bfmeLookupFJ(int idx);

	unsigned char m_bfmeHeadFJ[0x24];
	BfmeSlotFJ *m_bfmeTableFJ;
};

int BfmeHostFJ::bfmeLookupFJ(int idx)
{
	BfmeSlotFJ *s = &m_bfmeTableFJ[idx];
	BfmeGroupFJ *g = s->m_bfmeOwnerFJ->m_bfmeGroupFJ;
	int n = g->m_bfmeCountFJ;

	if (n > 0)
	{
		BfmeItemFJ *items = g->m_bfmeItemsFJ;
		const char *name = s->m_bfmeNameFJ;
		int i = 0;

		do
		{
			if (strcmp(name, items[i].m_bfmeNameFJ) == 0)
				return items[i].m_bfmeValueFJ;

			++i;
		}
		while (i < n);
	}

	return -1;
}
