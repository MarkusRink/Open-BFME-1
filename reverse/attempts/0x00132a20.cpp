// ?bfmeAnyFE@BfmeFlagsFE@@QBEDABV1@@Z
// partial score=0.93 date=2026-09-08
class BfmeFlagsFE
{
public:
	char bfmeAnyFE(const BfmeFlagsFE &other) const;

	unsigned int m_bfmeBitsFE[6];
};

char BfmeFlagsFE::bfmeAnyFE(const BfmeFlagsFE &other) const
{
	unsigned int t[6];

	t[0] = other.m_bfmeBitsFE[0] & m_bfmeBitsFE[0];
	t[1] = other.m_bfmeBitsFE[1] & m_bfmeBitsFE[1];
	t[2] = other.m_bfmeBitsFE[2] & m_bfmeBitsFE[2];
	t[3] = other.m_bfmeBitsFE[3] & m_bfmeBitsFE[3];
	t[4] = other.m_bfmeBitsFE[4] & m_bfmeBitsFE[4];
	t[5] = other.m_bfmeBitsFE[5] & m_bfmeBitsFE[5];

	for (unsigned int i = 0; i < 6; ++i)
	{
		if (t[i] != 0)
			return 1;
	}

	return 0;
}
