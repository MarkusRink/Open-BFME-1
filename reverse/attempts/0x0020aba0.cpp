// ?bfmeConsiderEP@@YAHPAVBfmeThingEP@@PAVBfmeCtxEP@@@Z
// partial score=0.95 date=2026-09-08
class BfmeTmplEP
{
public:
	const BfmeTmplEP *bfmeFinalEP() const;

	void *m_bfmeVfEP;
	BfmeTmplEP *m_bfmeOverEP;
};

class BfmeCtxEP;

class BfmeMatchEP
{
public:
	char bfmeMatchEP(void *key);
};

class BfmePosEP
{
public:
	float m_bfmeXEP;
	float m_bfmeYEP;
};

class BfmeThingEP
{
public:
	void *m_bfmeHeadEP;
	BfmeTmplEP *m_bfmeTmplEP;
	unsigned char m_bfmePad0EP[0x30];
	BfmePosEP m_bfmePosEP;
	unsigned char m_bfmePad1EP[0x38];
	int m_bfmeFlagEP;
};

class BfmeCtxEP
{
public:
	void *m_bfmeKeyEP;
	BfmeThingEP *m_bfmeRefEP;
	BfmeThingEP *m_bfmeBestEP;
	float m_bfmeDistEP;
};

__forceinline const BfmeTmplEP *bfmeResolveEP(BfmeTmplEP *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfmeOverEP != 0)
		return p->m_bfmeOverEP->bfmeFinalEP();

	return p;
}

int bfmeConsiderEP(BfmeThingEP *thing, BfmeCtxEP *ctx)
{
	if (((BfmeMatchEP *)bfmeResolveEP(thing->m_bfmeTmplEP))->bfmeMatchEP(ctx->m_bfmeKeyEP) && thing->m_bfmeFlagEP == 0)
	{
		BfmeThingEP *best = ctx->m_bfmeRefEP;

		BfmePosEP &bp = best->m_bfmePosEP;

		float dx = thing->m_bfmePosEP.m_bfmeXEP - bp.m_bfmeXEP;
		float dy = thing->m_bfmePosEP.m_bfmeYEP - bp.m_bfmeYEP;
		float d2 = dx * dx + dy * dy;

		if (d2 < ctx->m_bfmeDistEP)
		{
			ctx->m_bfmeBestEP = thing;
			ctx->m_bfmeDistEP = d2;
		}
	}

	return 1;
}
