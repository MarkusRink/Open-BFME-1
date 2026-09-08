// ?bfmeClearZK@BfmeHostZK@@QAEXI@Z
// partial score=0.96 date=2026-09-08
class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

class BfmeHostZK : public BfmeOwnerVNI
{
public:
	void bfmeClearZK(unsigned int bit);

	unsigned char m_bfmeHeadZK[0x110];
	unsigned int m_bfmeBitsZK[8];
};

void BfmeHostZK::bfmeClearZK(unsigned int bit)
{
	unsigned int m = 1 << (bit & 0x1f);
	unsigned int *w = &m_bfmeBitsZK[bit >> 5];

	unsigned int c = *w;

	if (!(m & c))
		return;

	c &= ~m;
	*w = c;
	bfmeApply1VNI();
}
