// ?d_004186e0@@YAXXZ
// partial score=0.9 date=2026-09-08
struct BfmeQueryD
{
	int m_bfmeAD;
	int m_bfmeBD;
	int m_bfmeCD;
	int m_bfmeDD;
	int m_bfmeED;
	int m_bfmeFD;
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadD[0x114];
	char m_bfmeFlagD;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

char __stdcall bfmeTestD(BfmeQueryD *query);

class BfmeDrawableD
{
public:
	void bfmeSetIndicatorD(unsigned int color);
	void bfmeApplyD(bool flag);

	unsigned char m_bfmeHeadD[0xfc];
	void *m_bfmeThingD;
	unsigned char m_bfmePadD[0x2c0];
	unsigned int m_bfmeColorD;
};

void BfmeDrawableD::bfmeSetIndicatorD(unsigned int color)
{
	m_bfmeColorD = color;

	bool flag;

	if (TheBfmeGameLogic->m_bfmeFlagD != 0)
	{
		flag = true;
	}
	else if (m_bfmeThingD == 0)
	{
		flag = false;
	}
	else
	{
		BfmeQueryD query;

		query.m_bfmeAD = 0;
		query.m_bfmeBD = 0;
		query.m_bfmeCD = 0;
		query.m_bfmeDD = 0x800000;
		query.m_bfmeED = 0;
		query.m_bfmeFD = 0x80000;

		flag = bfmeTestD(&query) != 0;
	}

	bfmeApplyD(flag);
}
