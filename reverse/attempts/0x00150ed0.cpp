// ?bfmeNotifyYF@BfmeHostYF@@QAEXHH@Z
// partial score=0.98 date=2026-09-08
struct RvaC4390Interface
{
	virtual void bfmeDoYF(int a, int b) = 0;
};

class RvaC4390First
{
public:
	RvaC4390Interface *getInterface();
};

struct BfmeNodeYF
{
	BfmeNodeYF *m_bfmeNextYF;
	unsigned char m_bfmePadYF[4];
	RvaC4390First *m_bfme08YF;
};

class BfmeHostYF
{
public:
	void bfmeNotifyYF(int a, int b);

	unsigned char m_bfmeHeadYF[4];
	BfmeNodeYF *m_bfme04YF;
};

void BfmeHostYF::bfmeNotifyYF(int a, int b)
{
	if (m_bfme04YF->m_bfmeNextYF == m_bfme04YF)
		return;

	RvaC4390Interface *iface = m_bfme04YF->m_bfmeNextYF->m_bfme08YF->getInterface();

	if (iface == 0)
		return;

	iface->bfmeDoYF(a, b);
}
