// ?bfmeSortFQ@@YAXPAVBfmeElemFQ@@0PAX@Z
// partial score=0.93 date=2026-09-08
class BfmeElemFQ
{
public:
	unsigned char m_bfmeHeadFQ[12];
};

typedef void *BfmeCmpFQ;

void bfmeIntroFQ(BfmeElemFQ *first, BfmeElemFQ *last, BfmeElemFQ *v, int depth, BfmeCmpFQ cmp);
void bfmeFinalFQ(BfmeElemFQ *first, BfmeElemFQ *last, BfmeCmpFQ cmp);

void bfmeSortFQ(BfmeElemFQ *first, BfmeElemFQ *last, BfmeCmpFQ cmp)
{
	if (first != last)
	{
		int n = (int)(last - first);
		int lg = 0;

		if (n != 1)
		{
			do
			{
				n >>= 1;
				++lg;
			}
			while (n != 1);
		}

		bfmeIntroFQ(first, last, 0, lg + lg, cmp);
		bfmeFinalFQ(first, last, cmp);
	}
}
