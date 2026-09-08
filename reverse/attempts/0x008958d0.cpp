// ?bfmeFindFH@BfmeHostFH@@QAEXPAPAVBfmeObjFH@@PAPAVBfmeStrFH@@@Z
// partial score=0.94 date=2026-09-08
extern "C" int memcmp(const void *a, const void *b, unsigned int n);

#pragma intrinsic(memcmp)

class BfmeStrFH
{
public:
	unsigned char m_bfmeHeadFH[2];
	unsigned short m_bfmeLenFH;
	unsigned char m_bfmeGapFH[4];
	char m_bfmeDataFH[1];
};

class BfmeObjFH
{
public:
	int m_bfmeRefFH;
	BfmeStrFH *m_bfmeKeyFH;
};

class BfmeNodeFH
{
public:
	BfmeObjFH *m_bfmeObjFH;
	BfmeNodeFH *m_bfmeNextFH;
};

__forceinline BfmeStrFH *bfmeLoadFH(BfmeStrFH *volatile *pp)
{
	return *pp;
}

class BfmeHostFH
{
public:
	void bfmeFindFH(BfmeObjFH **out, BfmeStrFH **key);

	BfmeNodeFH *m_bfmeHeadFH;
};

void BfmeHostFH::bfmeFindFH(BfmeObjFH **out, BfmeStrFH **key)
{
	BfmeNodeFH *n = m_bfmeHeadFH;
	volatile int r = 0;

	if (n != 0)
	{
		BfmeStrFH *k = *key;
		int len = k->m_bfmeLenFH;

		do
		{
			BfmeStrFH *s = bfmeLoadFH(&n->m_bfmeObjFH->m_bfmeKeyFH);

			if (len == s->m_bfmeLenFH)
			{
				if (k == s || memcmp(k->m_bfmeDataFH, s->m_bfmeDataFH, len) == 0)
				{
					BfmeObjFH *o = n->m_bfmeObjFH;

					*out = o;

					if (o != 0)
						++o->m_bfmeRefFH;

					return;
				}
			}

			n = n->m_bfmeNextFH;
		}
		while (n != 0);
	}

	*out = 0;
}
