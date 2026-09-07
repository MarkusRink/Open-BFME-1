// ?bfmeReadyAdjustedLT@BfmeOwnerLT@@QAEHXZ (identity unknown)
// partial score=0.95 date=2026-09-06
// Candidate twin of the banked 0x0018E410 readiness check. Retail adds this+0x24
// to the first holder value before calling the pinned ALT predicate, then calls
// the pinned BLT predicate with the second holder value and returns -1 only when
// both predicates succeed.
class BfmeValuesLT
{
public:
	unsigned char m_bfmeHeadLT[8];
	float m_bfmeFirstLT;
	float m_bfmeSecondLT;
};

class BfmeHolderLT
{
public:
	char bfmeCheckALT(float value, float ratio, int flag);
	char bfmeCheckBLT(float value, float ratio);

	unsigned char m_bfmeHeadLT[8];
	BfmeValuesLT *m_bfmeValuesLT;
};

class BfmeStageLT
{
public:
	unsigned char m_bfmeHeadLT[0x44];
	BfmeHolderLT *m_bfmeHolderLT;
};

class BfmeOwnerLT
{
public:
	int bfmeReadyAdjustedLT(void);

	unsigned char m_bfmeHeadLT[0x1c];
	BfmeStageLT *m_bfmeStageLT;
	int m_bfmePad20LT;
	float m_bfmeAdjustLT;
};

int BfmeOwnerLT::bfmeReadyAdjustedLT(void)
{
	char first = m_bfmeStageLT->m_bfmeHolderLT->bfmeCheckALT(
		m_bfmeStageLT->m_bfmeHolderLT->m_bfmeValuesLT->m_bfmeFirstLT + m_bfmeAdjustLT,
		0.5f,
		0);
	volatile float scratch;
	BfmeValuesLT *values = m_bfmeStageLT->m_bfmeHolderLT->m_bfmeValuesLT;
	scratch = values->m_bfmeSecondLT;
	char second = m_bfmeStageLT->m_bfmeHolderLT->bfmeCheckBLT(
		values->m_bfmeSecondLT,
		0.5f);

	if (first && second)
		return -1;
	return 0;
}
