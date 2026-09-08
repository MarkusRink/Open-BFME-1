// ?bfmeGetXS@BfmeHostXS@@QAEHXZ
// partial score=0.94 date=2026-09-08
// pins needed (CRLF):
//   ?bfmeFindDrawXS@Rva00367E30Logic@@QAEPAVDrawable@@PAX@Z,0x0001F253
//   ?bfmeChainXS@BfmeOverXS@@QAEPAV1@XZ,0x00048C61
class BfmeOverXS
{
public:
	BfmeOverXS *bfmeChainXS();

	unsigned char m_bfmeHeadXS[4];
	BfmeOverXS *m_bfme04XS;
	unsigned char m_bfmeMidXS[0xc];
	int m_bfme14XS;
};

class Drawable
{
public:
	bool isKindOf(int kind) const;
};

struct Rva00367E30Logic
{
	Drawable *bfmeFindDrawXS(void *id);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeSubXS
{
public:
	unsigned char m_bfmeHeadXS[0x1d8];
	BfmeOverXS *m_bfme1D8XS;
	unsigned char m_bfmeMidXS[0x30];
	int m_bfme20CXS;
};

class BfmeHostXS
{
public:
	int bfmeGetXS();

	unsigned char m_bfmeHeadXS[4];
	BfmeSubXS *m_bfme04XS;
	unsigned char m_bfmeMidXS[0xa4];
	void *m_bfmeACXS;
};

int BfmeHostXS::bfmeGetXS()
{
	BfmeSubXS *sub = m_bfme04XS;
	BfmeOverXS *base = sub->m_bfme1D8XS;
	Drawable *obj = TheBfmeGameLogic->bfmeFindDrawXS(m_bfmeACXS);
	BfmeOverXS *q = base->m_bfme04XS;

	if (q != 0)
	{
		if (q->m_bfme04XS != 0)
			q = q->m_bfme04XS->bfmeChainXS();

		base = q;
	}


	if (base->m_bfme14XS != 0x27)
		return sub->m_bfme20CXS;

	if (obj != 0)
	{
		if (obj->isKindOf(6))
			return sub->m_bfme20CXS;

		if (obj->isKindOf(0x62))
			return sub->m_bfme20CXS;

		return 0;
	}

	return sub->m_bfme20CXS;
}
