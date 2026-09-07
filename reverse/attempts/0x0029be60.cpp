// ?d_0029be60@@YAXXZ
// partial score=0.97 date=2026-09-08
class BfmeNodeEVP
{
public:
	int m_bfmeHeadEVP;
	int m_bfmeKindEVP;
	void *m_bfmeKeyEVP;
	int m_bfmePadAEVP;
	void *m_bfmeDataEVP;
	unsigned char m_bfmePadBEVP[0x28];
	BfmeNodeEVP *m_bfmeNextEVP;
};

class BfmeFilterEVP
{
public:
	char bfmeAcceptEVP(void *key);
};

class BfmeHostEVP
{
public:
	virtual void bfmeSlot00EVP();
	virtual void bfmeSlot01EVP();
	virtual void bfmeSlot02EVP();
	virtual void bfmeSlot03EVP();
	virtual void bfmeSlot04EVP();
	virtual void bfmeSlot05EVP();
	virtual void bfmeSlot06EVP();
	virtual void bfmeSlot07EVP();
	virtual void bfmeHandleEVP(void *data);

	void bfmeSweepEVP(BfmeFilterEVP *filter);

	int m_bfmePadEVP;
	BfmeNodeEVP *m_bfmeListEVP;
};

void BfmeHostEVP::bfmeSweepEVP(BfmeFilterEVP *filter)
{
	BfmeNodeEVP *node = m_bfmeListEVP;

	while (node != 0)
	{
		if (node->m_bfmeKindEVP == 1 && filter->bfmeAcceptEVP(node->m_bfmeKeyEVP))
		{
			BfmeNodeEVP *next = node->m_bfmeNextEVP;

			bfmeHandleEVP(node->m_bfmeDataEVP);

			node = next;
		}
		else
		{
			node = node->m_bfmeNextEVP;
		}
	}
}
