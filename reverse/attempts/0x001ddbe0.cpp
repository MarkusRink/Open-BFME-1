// ?bfmePushYK@BfmeHostYK@@QAE_NPAVDrawable@@@Z
// partial score=0.93 date=2026-09-08
// pin needed: ?bfmeOverflowYK@BfmeVecYK@@QAEXPAHABHABUBfmeTagYK@@I_N@Z,0x00010B8B
struct BfmeTagYK
{
};

class Drawable
{
public:
	unsigned char m_bfmeHeadYK[0x74];
	int m_bfme74YK;
};

class BfmeVecYK
{
public:
	void bfmeOverflowYK(int *pos, const int &x, const BfmeTagYK &tag, unsigned int n, bool atEnd);

	int *m_bfme00YK;
	int *m_bfme04YK;
	int *m_bfme08YK;
};

class BfmeHostYK
{
public:
	bool bfmePushYK(Drawable *d);

	unsigned char m_bfmeHeadYK[8];
	BfmeVecYK m_bfmeVecYK;
};

bool BfmeHostYK::bfmePushYK(Drawable *d)
{
	int v = d->m_bfme74YK;
	int *fin = m_bfmeVecYK.m_bfme04YK;
	BfmeVecYK *vec = &m_bfmeVecYK;

	if (fin == vec->m_bfme08YK)
	{
		BfmeTagYK tag;

		vec->bfmeOverflowYK(fin, v, tag, 1, true);
	}
	else
	{
		if (fin != 0)
			*fin = v;

		vec->m_bfme04YK = fin + 1;
	}

	return true;
}
