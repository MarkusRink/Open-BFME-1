// ?bfmeSetZN@BfmeHostZN@@QAEXI@Z
// partial score=0.93 date=2026-09-08
class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

class BfmeHostZN : public BfmeOwnerVNI
{
public:
	void bfmeSetZN(unsigned int bit);

	unsigned char m_bfmeHeadZN[0x110];
	unsigned int m_bfmeBitsZN[8];
};

void BfmeHostZN::bfmeSetZN(unsigned int bit)
{
	unsigned int i = bit >> 5;
	unsigned int m = 1 << (bit & 0x1f);
	unsigned int c = m_bfmeBitsZN[i];

	if (m & c)
		return;

	m_bfmeBitsZN[i] = c | m;
	bfmeApply1VNI();
}
