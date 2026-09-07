// ?bfmeLimitAdjusted@Gen_003BDD60@@QAEHXZ
// partial score=0.72 date=2026-09-06
// ?bfmeLimitAdjusted@Gen_003BDD60@@QAEHXZ
// cl: /O2 /DNDEBUG /MD /EHsc

class BfmeSwitchDR
{
public:
	char m_bfmeHead[0x1C];
	bool m_bfmeUseHigh;
};

class BfmeBaseDS
{
public:
	char m_bfmeHead[0xE70];
	int m_bfmeLow;
	int m_bfmeHigh;
	char m_bfmeGap[0x40];
	int m_bfmeLowLarge;
	int m_bfmeHighLarge;
};

class Gen_003BDD60Child
{
public:
	char m_bfmeHead[0x38];
	int m_bfmeValue;
};

class Gen_003BDD60
{
public:
	int bfmeLimitAdjusted(void);

private:
	char m_bfmeHead[0x28];
	Gen_003BDD60Child *m_bfmeChild;
};

extern BfmeSwitchDR *g_bfmeSwitchDR;
extern BfmeBaseDS *g_bfmeBaseDS;

int Gen_003BDD60::bfmeLimitAdjusted(void)
{
	Gen_003BDD60Child *child = m_bfmeChild;
	if (child == 0)
		return 0;

	BfmeSwitchDR *state = g_bfmeSwitchDR;
	int high = state != 0 ? state->m_bfmeUseHigh : 0;
	int limit;
	int offset;
	BfmeBaseDS *base;
	if (state != 0 && high != 0)
	{
		base = g_bfmeBaseDS;
		limit = base->m_bfmeHighLarge;
		offset = base->m_bfmeHigh;
	}
	else
	{
		base = g_bfmeBaseDS;
		limit = base->m_bfmeLowLarge;
		offset = base->m_bfmeLow;
	}
	if (state == 0)
		return 0;

	int difference = limit - offset;
	int value = child->m_bfmeValue;
	*(volatile int *)&difference = difference;
	*(volatile int *)&value = value;
	int *result = &value;
	if (value < difference)
		result = &difference;
	return *result;
}
