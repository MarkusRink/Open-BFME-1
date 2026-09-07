class BfmeLexEAN
{
public:
	int bfmeScanEAN();
	char bfmeExpandEAN(char *out);
	int bfmeFailEAN(int code);

	char *m_bfmePosEAN;
	unsigned char m_bfmeHeadEAN[0x10];
	char *m_bfmeBufEAN;
	int m_bfmeLimitEAN;
	char *m_bfmeTailEAN;
};

int BfmeLexEAN::bfmeScanEAN()
{
	int n = 0;

	for (;;)
	{
		char c = *m_bfmePosEAN;

		if (c == 0x26)
		{
			if (!bfmeExpandEAN(m_bfmeBufEAN + n))
				return bfmeFailEAN(-1);
		}
		else
		{
			m_bfmeBufEAN[n] = c;
		}

		c = *m_bfmePosEAN;

		if (c == 0x3c || c == 0)
			break;

		m_bfmePosEAN++;

		if (*m_bfmePosEAN == 0)
			return bfmeFailEAN(-1);

		if (n <= m_bfmeLimitEAN)
			n++;
	}

	m_bfmeBufEAN[n] = 0;

	m_bfmeTailEAN = m_bfmeBufEAN;

	return 3;
}
