// ?bfmeConsiderEZ@BfmeHostEZ@@QAEXPAVBfmeNodeEZ@@PBVBfmeVec2EZ@@@Z
// partial score=0.95 date=2026-09-08
struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmePathEZ
{
public:
	char bfmeCheckAEZ(void *obj, const Coord3D *from, const Coord3D *to, int flags);
	char bfmeCheckBEZ(const Coord3D *from, const Coord3D *to);
};

class AI
{
public:
	unsigned char m_bfmeHeadEZ[0xc];
	BfmePathEZ *m_bfmePathEZ;
};

extern AI *TheAI;

class BfmeObjEZ
{
public:
	unsigned char m_bfmeHeadEZ[0x38];
	Coord3D m_bfmePosEZ;
};

class BfmeNodeEZ
{
public:
	Coord3D m_bfmePosEZ;
	int m_bfmeTagEZ;
};

class BfmeVec2EZ
{
public:
	float x;
	float y;
};

class BfmeHostEZ
{
public:
	void bfmeConsiderEZ(BfmeNodeEZ *n, const BfmeVec2EZ *p);

	Coord3D m_bfmePosEZ;
	int m_bfmeTagEZ;
	float m_bfmeBestEZ;
	BfmeNodeEZ *m_bfmeNodeEZ;
	BfmeObjEZ *m_bfmeObjEZ;
};

void BfmeHostEZ::bfmeConsiderEZ(BfmeNodeEZ *n, const BfmeVec2EZ *p)
{
	float py = *(const volatile float *)&p->y;
	float px = *(const volatile float *)&p->x;
	volatile float dx = px - n->m_bfmePosEZ.x;
	float dy = py - n->m_bfmePosEZ.y;
	float d2 = dy * dy + dx * dx;

	if (m_bfmeTagEZ != 0 && d2 >= m_bfmeBestEZ)
		return;

	BfmeObjEZ *o = m_bfmeObjEZ;

	if (!TheAI->m_bfmePathEZ->bfmeCheckAEZ(o, &o->m_bfmePosEZ, &n->m_bfmePosEZ, 0))
		return;

	if (!TheAI->m_bfmePathEZ->bfmeCheckBEZ(&m_bfmeObjEZ->m_bfmePosEZ, &n->m_bfmePosEZ))
		return;

	m_bfmeTagEZ = n->m_bfmeTagEZ;
	m_bfmePosEZ = n->m_bfmePosEZ;
	m_bfmeBestEZ = d2;
	m_bfmeNodeEZ = n;
}
