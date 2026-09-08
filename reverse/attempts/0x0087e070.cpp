// ?d_0087e070@@YAXXZ
// partial score=0.97 date=2026-09-08
extern const float BfmeZeroRange;

class BfmeElemGI
{
public:
	void *m_bfmePtrGI;
	int m_bfmePadAGI;
	float m_bfmeHeightGI;
	unsigned char m_bfmePadBGI[0x14];
	char m_bfmeFlagGI;
	unsigned char m_bfmePadCGI[3];
};

__forceinline const float &bfmeMaxGI(const float &a, const float &b)
{
	return a > b ? a : b;
}

class GeometryInfoGI
{
public:
	float bfmeMaxHeightGI() const;

	unsigned char m_bfmeHeadGI[0x2c];
	BfmeElemGI *m_bfmeBeginGI;
	BfmeElemGI *m_bfmeEndGI;
};

float GeometryInfoGI::bfmeMaxHeightGI() const
{
	float best = BfmeZeroRange;

	for (BfmeElemGI *p = m_bfmeBeginGI; p != m_bfmeEndGI; p++)
	{
		if (p->m_bfmeFlagGI)
		{
			float v = p->m_bfmePtrGI != 0 ? BfmeZeroRange : p->m_bfmeHeightGI;

			best = bfmeMaxGI(v, best);
		}
	}

	return best;
}
