// ?getCollapseHeight@StructureCollapseRetailLayout@@QAEMXZ
// partial score=0.98 date=2026-09-08
class BfmeGeomTH
{
public:
	float bfmeMaxHeightTH() const;
};

class BfmeTmplTH
{
public:
	const BfmeTmplTH *bfmeFinalTH() const;

	const BfmeTmplTH *bfmeResolveTH() const
	{
		if (this == 0)
			return 0;

		if (m_bfmeOverTH == 0)
			return this;

		return m_bfmeOverTH->bfmeFinalTH();
	}

	void *m_bfmeVfTH;
	BfmeTmplTH *m_bfmeOverTH;
	unsigned char m_bfmePadTH[0x58];
	BfmeGeomTH m_bfmeGeomTH;
};

class BfmeOwnerTH
{
public:
	void *m_bfmeHeadTH;
	BfmeTmplTH *m_bfmeTmplTH;
};

class BfmeObjTH
{
public:
	unsigned char m_bfmeHeadTH[0xf4];
	float m_bfmeHeightTH;
};

class BfmeHolderTH
{
public:
	float bfmeCollapseHeightTH() const;

	void *m_bfmeVfTH;
	BfmeObjTH *m_bfmeObjTH;
	BfmeOwnerTH *m_bfmeOwnerTH;
};

__forceinline const BfmeTmplTH *bfmeResolveTH(BfmeTmplTH *volatile *pp)
{
	BfmeTmplTH *o = *pp;

	if (o == 0)
		return 0;

	if (o->m_bfmeOverTH == 0)
		return o;

	return o->m_bfmeOverTH->bfmeFinalTH();
}

float BfmeHolderTH::bfmeCollapseHeightTH() const
{
	BfmeObjTH *o = m_bfmeObjTH;

	if (bfmeResolveTH((BfmeTmplTH *volatile *)&m_bfmeOwnerTH->m_bfmeTmplTH)->m_bfmeGeomTH.bfmeMaxHeightTH() < o->m_bfmeHeightTH)
		return m_bfmeObjTH->m_bfmeHeightTH;

	return bfmeResolveTH((BfmeTmplTH *volatile *)&m_bfmeOwnerTH->m_bfmeTmplTH)->m_bfmeGeomTH.bfmeMaxHeightTH();
}
