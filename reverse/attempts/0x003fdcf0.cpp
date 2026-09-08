// ?bfmeResolveFY@BfmeHostFY@@QAEXPAVBfmeVec3FY@@@Z
// partial score=0.93 date=2026-09-08
class BfmeVec3FY
{
public:
	float x;
	float y;
	float z;
};

class BfmeNodeFY
{
public:
	unsigned char m_bfmeHeadFY[8];
	BfmeNodeFY *m_bfmeNextFY;
	BfmeVec3FY m_bfmePosFY;
	unsigned char m_bfmeGapFY[8];
	int m_bfmeKeyFY;
};

class BfmeHostFY
{
public:
	void bfmeResolveFY(BfmeVec3FY *out);

	unsigned char m_bfmeHeadFY[0x10];
	BfmeNodeFY *m_bfmeNodeFY;
	float m_bfmeXFY;
	float m_bfmeYFY;
	float m_bfmeZFY;
};

void BfmeHostFY::bfmeResolveFY(BfmeVec3FY *out)
{
	BfmeVec3FY p;

	p.x = m_bfmeXFY;
	p.y = m_bfmeYFY;
	p.z = m_bfmeZFY;

	BfmeNodeFY *n = m_bfmeNodeFY;

	if (n != 0)
	{
		BfmeNodeFY *a = n->m_bfmeNextFY;

		if (a != 0)
		{
			p = a->m_bfmePosFY;

			BfmeNodeFY *b = a->m_bfmeNextFY;

			if (b != 0)
			{
				p = b->m_bfmePosFY;

				BfmeNodeFY *c = b->m_bfmeNextFY;

				if (c != 0 && c->m_bfmeKeyFY != 0x7fffffff)
					p = c->m_bfmePosFY;
			}
		}
	}

	*out = p;
}
