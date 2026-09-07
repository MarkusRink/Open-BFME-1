class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBufferCS(); }

	void releaseBufferCS();

	void *m_bfmeBufCS;
};

class BfmeSinkCS
{
public:
	void bfmeWriteCS(void *first, const BFMERetailAsciiString &text, void *third);
};

class BfmeHostCS
{
public:
	void bfmeSendCS(void *first, BFMERetailAsciiString text, void *third);

	unsigned char m_bfmeHeadCS[0x30a4];
	BfmeSinkCS *m_bfmeSinkCS;
};

void BfmeHostCS::bfmeSendCS(void *first, BFMERetailAsciiString text, void *third)
{
	BfmeSinkCS *s = m_bfmeSinkCS;

	if (s != 0)
		s->bfmeWriteCS(first, text, third);
}
