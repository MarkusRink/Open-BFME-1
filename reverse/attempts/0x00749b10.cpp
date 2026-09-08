// ?bfmeSetBitAAP@BfmeBitmapAAP@@QAEXHH_N@Z
// partial score=0.92 date=2026-09-08
class BfmeBitmapAAP
{
public:
	void bfmeSetBitAAP(int x, int y, bool on);

	unsigned char m_bfmeHeadAAP[8];
	int m_bfmeWidthAAP;
	int m_bfmeHeightAAP;
	unsigned char m_bfmeGapAAP[0x34 - 0x10];
	int m_bfmeStrideAAP;
	unsigned char m_bfmeGapBAAP[0x68 - 0x38];
	unsigned char *m_bfmeBeginAAP;
	unsigned char *m_bfmeEndAAP;
};

void BfmeBitmapAAP::bfmeSetBitAAP(int x, int y, bool on)
{
	if (x < 0)
		return;

	if (y < 0)
		return;

	if (y >= m_bfmeHeightAAP)
		return;

	if (x >= m_bfmeWidthAAP)
		return;

	int idx = m_bfmeStrideAAP * y + (x >> 3);

	if ((unsigned int)idx >= (unsigned int)(m_bfmeEndAAP - m_bfmeBeginAAP))
		return;

	unsigned char *p = m_bfmeBeginAAP + idx;
	unsigned char mask = (unsigned char)(1 << (x & 7));
	unsigned char v = *p;

	if (on)
		*p = (unsigned char)(v | mask);
	else
		*p = (unsigned char)(v & ~mask);
}
