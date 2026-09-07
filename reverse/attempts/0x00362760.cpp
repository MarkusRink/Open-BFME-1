// ?d_00362760@@YAXXZ
// partial score=0.9 date=2026-09-08
class BfmeElemEAP
{
public:
	void bfmeDoEAP(void *arg);

	unsigned char m_bfmeBodyEAP[0x58];
};

class BfmeVecEAP
{
public:
	void bfmeApplyEAP(int index, void *arg);

	unsigned char m_bfmeHeadEAP[0x18];
	BfmeElemEAP *m_bfmeBeginEAP;
	BfmeElemEAP *m_bfmeEndEAP;
};

void BfmeVecEAP::bfmeApplyEAP(int index, void *arg)
{
	if (index < 0 ||
		(unsigned int)index >= (unsigned int)(m_bfmeEndEAP - m_bfmeBeginEAP))
		return;

	m_bfmeBeginEAP[index].bfmeDoEAP(arg);
}
