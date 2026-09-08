// ?bfmeNoneFI@BfmeFlagsFI@@QBE_NABV1@@Z
// partial score=0.90 date=2026-09-08
class BfmeFlagsFI
{
public:
	__forceinline bool bfmeAnyFI(const BfmeFlagsFI &other) const
	{
		unsigned int t[6];

		t[0] = m_bfmeBitsFI[0] & other.m_bfmeBitsFI[0];
		t[1] = m_bfmeBitsFI[1] & other.m_bfmeBitsFI[1];
		t[2] = m_bfmeBitsFI[2] & other.m_bfmeBitsFI[2];
		t[3] = m_bfmeBitsFI[3] & other.m_bfmeBitsFI[3];
		t[4] = m_bfmeBitsFI[4] & other.m_bfmeBitsFI[4];
		t[5] = m_bfmeBitsFI[5] & other.m_bfmeBitsFI[5];

		for (unsigned int i = 0; i < 6; ++i)
		{
			if (t[i] != 0)
				return true;
		}

		return false;
	}

	bool bfmeNoneFI(const BfmeFlagsFI &other) const;

	unsigned int m_bfmeBitsFI[6];
};

bool BfmeFlagsFI::bfmeNoneFI(const BfmeFlagsFI &other) const
{
	return bfmeAnyFI(other) == false;
}
