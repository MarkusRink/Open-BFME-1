// ?bfmeGetNameXX@BfmeHolderXX@@QAE?AVBFMERetailAsciiString@@H@Z
// partial score=0.9 date=2026-09-08
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() { m_data = 0; }
	BFMERetailAsciiString(const char *s);
	~BFMERetailAsciiString();

private:
	void *m_data;
};

class BfmeItemXX
{
public:
	virtual void bfmeVt0XX();
	virtual void bfmeVt1XX();
	virtual const char *bfmeNameXX();
};

class BfmeElemXX
{
public:
	BfmeItemXX *m_bfmeItemXX;
	unsigned char m_bfmeGapXX[0x18];
};

class BfmeOwnerXX
{
public:
	void bfmeRefreshXX();
};

extern int g_Va012F8064;

class BfmeHolderXX
{
public:
	BFMERetailAsciiString bfmeGetNameXX(int i);

	unsigned char m_bfmeGapXX[0x90];
	int m_bfmeStampXX;
	unsigned char m_bfmeGap2XX[0x3c];
	BfmeElemXX m_bfmeArrXX[3];
};

BFMERetailAsciiString BfmeHolderXX::bfmeGetNameXX(int i)
{
	BfmeOwnerXX *owner = (BfmeOwnerXX *)((char *)this - 0xc);

	if (g_Va012F8064 != m_bfmeStampXX)
		owner->bfmeRefreshXX();

	if (i >= 0 && i < 3)
	{
		if (m_bfmeArrXX[i].m_bfmeItemXX != 0)
			return BFMERetailAsciiString(m_bfmeArrXX[i].m_bfmeItemXX->bfmeNameXX());
	}

	return BFMERetailAsciiString();
}
