class BfmeResBX
{
public:
	unsigned char m_bfmeHeadBX[0xb0];
	int m_bfmeValueBX;
};

class BfmeOwnerBX
{
public:
	virtual void bfmeSlot00BX();
	virtual void bfmeSlot01BX();
	virtual void bfmeSlot02BX();
	virtual void bfmeSlot03BX();
	virtual void bfmeSlot04BX();
	virtual void bfmeSlot05BX();
	virtual void bfmeSlot06BX();
	virtual void bfmeSlot07BX();
	virtual void bfmeSlot08BX();
	virtual void bfmeSlot09BX();
	virtual BfmeResBX *bfmeGetBX();

	void bfmeAimBX(void *at);
	void bfmeIdleBX(int mode, int flag);
};

class BfmeObjBX
{
public:
	unsigned char m_bfmeHeadBX[0x38];
	int m_bfmeAtBX;
	unsigned char m_bfmeMidBX[0x308];
	unsigned char m_bfmeFlagsBX;
};

struct Rva00367E30Logic
{
	BfmeObjBX *bfmeFindBX(int id);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeCfgBX
{
public:
	unsigned char m_bfmeHeadBX[0x34];
	unsigned char m_bfmeOnBX;
};

class BfmeSubBX
{
public:
	void bfmeQueryBX(int *first, int *second);
};

class BfmeHostBX
{
public:
	int bfmeStartBX();

	unsigned char m_bfmeHeadBX[0x10];
	int m_bfmeIdBX;
	int m_bfmeAtBX;
	BfmeSubBX m_bfmeSubBX;
};

int BfmeHostBX::bfmeStartBX()
{
	BfmeOwnerBX *owner = *(BfmeOwnerBX **)((char *)this - 8);

	if ((*(BfmeCfgBX **)((char *)this - 0xc))->m_bfmeOnBX != 0)
	{
		BfmeObjBX *o = 0;

		if (m_bfmeIdBX != 0)
			o = TheBfmeGameLogic->bfmeFindBX(m_bfmeIdBX);

		if (o != 0 && (o->m_bfmeFlagsBX & 1) == 0)
			owner->bfmeAimBX(&o->m_bfmeAtBX);
		else
			owner->bfmeIdleBX(8, 0);
	}

	BfmeResBX *r = owner->bfmeGetBX();

	if (r != 0)
	{
		m_bfmeSubBX.bfmeQueryBX(&m_bfmeAtBX, &m_bfmeAtBX);
		r->m_bfmeValueBX = m_bfmeAtBX;
	}

	return 1;
}
