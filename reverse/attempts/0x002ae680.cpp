// ?d_002ae680@@YAXXZ
// partial score=0.8 date=2026-09-08
class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;

	unsigned char m_bfmeBodySC[0x10];
};

class BfmeSubSC;
class BfmeThingSC;

BfmeThingSC *__fastcall bfmeResolveSC(BfmeSubSC *sub);

class BfmeThingSC
{
public:
	int m_bfmeHeadSC;
	BfmeSubSC *m_bfmeSubSC;
	unsigned char m_bfmePadSC[0x58];
	GeometryInfo m_bfmeGeomSC;
};

class BfmeListSC
{
public:
	int m_bfmeHeadSC;
	BfmeThingSC *m_bfmeThingSC;
};

class BfmeOwnerSC
{
public:
	unsigned char m_bfmeHeadSC[0xf4];
	float m_bfmeHeightSC;
};

class BfmeHostSC
{
public:
	float bfmeCollapseHeightSC();

	int m_bfmeHeadSC;
	BfmeOwnerSC *m_bfmeOwnerSC;
	BfmeListSC *m_bfmeListSC;
};

__forceinline float bfmeGeomHeightSC(BfmeListSC *list)
{
	BfmeThingSC *t = list->m_bfmeThingSC;

	if (t != 0 && t->m_bfmeSubSC != 0)
		t = bfmeResolveSC(t->m_bfmeSubSC);

	return t->m_bfmeGeomSC.getMaxHeightAbovePosition();
}

float BfmeHostSC::bfmeCollapseHeightSC()
{
	if (bfmeGeomHeightSC(m_bfmeListSC) < m_bfmeOwnerSC->m_bfmeHeightSC)
		return m_bfmeOwnerSC->m_bfmeHeightSC;

	return bfmeGeomHeightSC(m_bfmeListSC);
}
