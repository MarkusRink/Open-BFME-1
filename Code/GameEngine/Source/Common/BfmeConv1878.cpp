struct BfmeNodeZK
{
	BfmeNodeZK *m_bfmeNextZK;
	int m_bfmeIdZK;
	int m_bfmeKindZK;
};

struct BfmeEntryZK
{
	unsigned char m_bfmeHeadZK[0xe];
	short m_bfmeShortZK;
	unsigned char m_bfmeTailZK[4];
};

class BfmeFinderZK
{
public:
	int bfmeFindZK(void *key, int id);

	int m_bfmeSlotZK;
};

class BfmeKeyZK
{
public:
	unsigned char m_bfmeHeadZK[0x2c];
	unsigned char m_bfmeAtZK[4];
};

class BfmeOwnerZK
{
public:
	void bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to);

	unsigned char m_bfmeHeadZK[0x2c];
	BfmeFinderZK m_bfmeFinderZK;
	unsigned char m_bfmeMidZK[8];
	BfmeEntryZK *m_bfmeTableZK;
};

void BfmeOwnerZK::bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to)
{
	int id = (*from)->m_bfmeIdZK;
	int index = m_bfmeFinderZK.bfmeFindZK(key->m_bfmeAtZK, id);

	if (index == -1)
		return;

	(*from)->m_bfmeIdZK = index;
	(*from)->m_bfmeKindZK = m_bfmeTableZK[index].m_bfmeShortZK;

	BfmeNodeZK *next = (*from)->m_bfmeNextZK;

	(*from)->m_bfmeNextZK = *to;
	*to = *from;
	*from = next;
}
