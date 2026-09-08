// ?bfmeLessZQ@BfmeKeyZQ@@QBEDPBV1@@Z
// partial score=0.93 date=2026-09-08
class AsciiString
{
public:
	int compareNoCase(const AsciiString &o) const;

	void *m_bfmeStrZQ;
};

class BfmeKeyZQ
{
public:
	char bfmeLessZQ(const BfmeKeyZQ *b) const;

	char m_bfmeFlagZQ;
	unsigned char m_bfmePadZQ[3];
	AsciiString m_bfmeNameZQ;
};

char BfmeKeyZQ::bfmeLessZQ(const BfmeKeyZQ *b) const
{
	char c = m_bfmeFlagZQ;

	if ((b->m_bfmeFlagZQ == 0) ^ (c == 0))
		return c;

	int lt = m_bfmeNameZQ.compareNoCase(b->m_bfmeNameZQ) < 0;

	return (char)lt;
}
