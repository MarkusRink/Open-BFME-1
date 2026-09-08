// ?bfmeHeightZC@BfmeHostZC@@QAEMXZ
// partial score=0.97 date=2026-09-08
// pins needed (CRLF):
//   ?bfmeWalkZC@BfmeOverZC@@QAEPAV1@XZ,0x000022BB
//   ?bfmeGeomZC@BfmeObjZC@@QAEPAVGeometryInfo@@XZ,0x000293E8
//   ?bfmePosZC@BfmeObjZC@@QAEPAUCoord3D@@XZ,0x0003EE55
struct Coord3D
{
	float x;
	float y;
	float z;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class BfmeOverZC
{
public:
	BfmeOverZC *bfmeWalkZC();

	unsigned char m_bfmeHeadZC[4];
	BfmeOverZC *m_bfme04ZC;
	unsigned char m_bfmeMidZC[0xc0];
	unsigned char m_bfmeC8ZC;
	unsigned char m_bfmeMid2ZC[0x3b9];
	unsigned short m_bfme482ZC;
};

class BfmeSubZC
{
public:
	unsigned char m_bfmeHeadZC[4];
	BfmeOverZC *m_bfme04ZC;
};

class BfmeObjZC
{
public:
	GeometryInfo *bfmeGeomZC();
	Coord3D *bfmePosZC();

	unsigned char m_bfmeHeadZC[4];
	BfmeOverZC *m_bfme04ZC;
	unsigned char m_bfmeMidZC[0xf4];
	BfmeSubZC *m_bfmeFCZC;
};

struct Rva003FD060TerrainLogic
{
	virtual void bfmeV0ZC() = 0;
	virtual void bfmeV1ZC() = 0;
	virtual void bfmeV2ZC() = 0;
	virtual void bfmeV3ZC() = 0;
	virtual void bfmeV4ZC() = 0;
	virtual void bfmeV5ZC() = 0;
	virtual float bfmeGroundZC(float x, float y, void *info) = 0;
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern const float g_bfmeK1266B;
extern const float BfmeZeroRange;

static __forceinline BfmeOverZC *bfmeFinalZC(BfmeOverZC *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04ZC == 0)
		return p;

	return p->m_bfme04ZC->bfmeWalkZC();
}

class BfmeHostZC
{
public:
	float bfmeHeightZC();

	unsigned char m_bfmeHeadZC[8];
	BfmeObjZC *m_bfme08ZC;
	unsigned char m_bfmeGapZC[0x22];
	char m_bfme2EZC;
};

float BfmeHostZC::bfmeHeightZC()
{
	BfmeObjZC *o = m_bfme08ZC;
	BfmeOverZC *ov1 = bfmeFinalZC(o->m_bfme04ZC);
	BfmeSubZC *s = o->m_bfmeFCZC;

	if (s != 0 && (bfmeFinalZC(s->m_bfme04ZC)->m_bfmeC8ZC & 0x40) != 0)
		return o->bfmeGeomZC()->getMaxHeightAbovePosition() * g_bfmeK1266B;

	if ((ov1->m_bfme482ZC & 0x386) == 0)
		return BfmeZeroRange;

	if (m_bfme2EZC == 0)
		return BfmeZeroRange;

	float d;
	Coord3D *p = o->bfmePosZC();
	float px = p->x;
	float py = p->y;
	float pz = p->z;

	d = pz - TheTerrainLogic->bfmeGroundZC(px, py, 0);

	return (m_bfme08ZC->bfmeGeomZC()->getMaxHeightAbovePosition() + d) * 2.0f;
}
