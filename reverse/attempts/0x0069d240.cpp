// ?bfmeNameAAG@BfmeHostAAG@@QBE?AVBFMERetailAsciiString@@XZ
// partial score=0.94 date=2026-09-08
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *s);
	BFMERetailAsciiString(const BFMERetailAsciiString &o);
	~BFMERetailAsciiString();

	void *m_bfmeDataAAG;
};

struct Rva006A16B0Entry
{
	const char *m_bfmeNameAAG;
	int m_bfmeIdAAG;
};

extern Rva006A16B0Entry Rva006A16B0Table[];

extern int (__stdcall *g_bfmeFnAAG)(void *slot);

struct BfmeSlotAAG
{
	void *m_bfmeAAAG;
	void *m_bfmeBAAG;
	void *m_bfmeCAAG;
};

class BfmeHostAAG
{
public:
	BFMERetailAsciiString bfmeNameAAG() const;

	unsigned char m_bfmeHeadAAG[0x658];
	BfmeSlotAAG m_bfme658AAG[64];
	int m_bfme958AAG;
};

BFMERetailAsciiString BfmeHostAAG::bfmeNameAAG() const
{
	int r = g_bfmeFnAAG(m_bfme658AAG[m_bfme958AAG].m_bfmeAAAG);

	for (unsigned int i = 0; i < 26; ++i)
		if (r == Rva006A16B0Table[i].m_bfmeIdAAG)
			return BFMERetailAsciiString(Rva006A16B0Table[i].m_bfmeNameAAG);

	return BFMERetailAsciiString("<Unknown>");
}
