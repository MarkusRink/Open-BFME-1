// ?bfmeUpdateHP@BfmeFadeHP@@QAEXXZ
// partial score=0.93 date=2026-09-08
extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;
extern float g_bfmeScaleB3;

class BfmeSubHP
{
public:
	void bfmeApplyHP(void *o, int k, unsigned int c);

	int m_bfmeA0HP;
	int m_bfmeA1HP;
	int m_bfmeA2HP;
	int m_bfmeA3HP;
	int m_bfmeA4HP;
	int m_bfmeA5HP;
};

class BfmeFadeHP
{
public:
	void bfmeUpdateHP();

	unsigned char m_bfmeHeadHP[0x10c];
	volatile int m_bfme10cHP;
	unsigned char m_bfmeGapHP[8];
	float m_bfme118HP;
	float m_bfme11cHP;
	BfmeSubHP m_bfmeSubHP;
};

void BfmeFadeHP::bfmeUpdateHP()
{
	unsigned int c = 0xffffff;

	if (m_bfme11cHP > BfmeZeroRange)
	{
		int v = m_bfme10cHP;

		if (v != 0)
		{
			v = v - 1;
			m_bfme10cHP = v;
			v = (v < 0) ? 0 : v;
			m_bfme10cHP = v;

			if (v > 0x2d)
			{
				v = 0x2d;
				m_bfme10cHP = v;
			}

			c = 0xffffffff;
			m_bfme11cHP = 1.0f;
		}
		else if (m_bfme11cHP > BfmeZeroRange)
		{
			m_bfme11cHP = m_bfme11cHP - m_bfme118HP;

			if (m_bfme11cHP <= BfmeZeroRange)
			{
				m_bfme11cHP = 0;
				m_bfmeSubHP.m_bfmeA0HP = 0;
				m_bfmeSubHP.m_bfmeA1HP = 0;
				m_bfmeSubHP.m_bfmeA2HP = 0;
				m_bfmeSubHP.m_bfmeA3HP = 0;
				m_bfmeSubHP.m_bfmeA4HP = 0;
				m_bfmeSubHP.m_bfmeA5HP = 0;
			}

			float x = (g_bfmeDefaultBU < m_bfme11cHP) ? g_bfmeDefaultBU : m_bfme11cHP;

			m_bfme11cHP = x;

			c = ((unsigned int)(int)(x * g_bfmeScaleB3) << 24) | 0xffffff;
		}

		if (c & 0xff000000)
			m_bfmeSubHP.bfmeApplyHP(this, 1, c);
	}
}
