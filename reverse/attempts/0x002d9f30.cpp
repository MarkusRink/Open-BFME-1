// ?d_002d9f30@@YAXXZ
// partial score=0.96 date=2026-09-08
class BfmeTargetEVN
{
public:
	void bfmeNotifyEVN();

	unsigned char m_bfmeHeadEVN[0x110];
	unsigned int m_bfmeBitsEVN[8];
};

class BfmeItemEVN
{
public:
	unsigned char m_bfmeHeadEVN[0x64];
	unsigned int m_bfmeIndexEVN;
};

class BfmeHostEVN
{
public:
	void bfmeMarkEVN();

	int m_bfmeHeadEVN;
	BfmeItemEVN *m_bfmeItemEVN;
	BfmeTargetEVN *m_bfmeTargetEVN;
};

void BfmeHostEVN::bfmeMarkEVN()
{
	BfmeTargetEVN *target = m_bfmeTargetEVN;
	BfmeItemEVN *item = m_bfmeItemEVN;

	if (target == 0 || item == 0)
		return;

	unsigned int index = item->m_bfmeIndexEVN;

	if (index == 0xffffffff)
		return;

	unsigned int mask = 1 << (index & 0x1f);
	unsigned int *slot = &target->m_bfmeBitsEVN[index >> 5];

	if ((*slot & mask) != 0)
		return;

	*slot = *slot | mask;

	target->bfmeNotifyEVN();
}
