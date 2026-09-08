// ?bfmeLookupAAL@@YADPAUBfmeHostAAL@@PAX@Z
// partial score=0.78 date=2026-09-08
class BfmeCheckAAL
{
public:
	int bfmeCheckAAL(void *key);
};

class BfmeVecAAL
{
public:
	int bfmeFindAAL(void *key);

	int *m_bfmeBeginAAL;
	int *m_bfmeEndAAL;
	unsigned char m_bfmeGapAAL[4];
};

struct BfmeHostAAL
{
	unsigned char m_bfmeHeadAAL[0x2c];
	BfmeVecAAL m_bfme2CAAL;
	char *m_bfme38AAL;
};

char bfmeLookupAAL(BfmeHostAAL *host, void *key);

char bfmeLookupAAL(BfmeHostAAL *host, void *key)
{
	BfmeVecAAL *v = &host->m_bfme2CAAL;
	int idx = v->bfmeFindAAL(key);

	if ((unsigned int)idx >= (unsigned int)(v->m_bfmeEndAAL - v->m_bfmeBeginAAL))
		return 1;

	int rec = v->m_bfmeBeginAAL[idx];
	char *recs = *(char **)((char *)v + 0xc);
	int off = rec * 20;

	if (((BfmeCheckAAL *)(recs + off + 8))->bfmeCheckAAL(key) != 0)
		return 1;

	if (rec == -1)
		return 1;

	return host->m_bfme38AAL[off + 0xc];
}
