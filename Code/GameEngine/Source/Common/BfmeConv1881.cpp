extern "C" char g_bfmeNameZO[];

class BfmeChunkZO
{
public:
	void bfmeOpenZO(char *name, unsigned short version);
	void bfmeCloseZO();
};

class BfmeItemZO
{
public:
	void bfmeWriteZO(BfmeChunkZO *out);

	unsigned char m_bfmeBytesZO[0x14];
};

class BfmeOwnerZO
{
public:
	void bfmeSaveZO(BfmeChunkZO *out);

	BfmeItemZO m_bfmeItemsZO[8];
};

void BfmeOwnerZO::bfmeSaveZO(BfmeChunkZO *out)
{
	out->bfmeOpenZO(g_bfmeNameZO, 0);

	for (int i = 0; i < 8; i++)
		m_bfmeItemsZO[i].bfmeWriteZO(out);

	out->bfmeCloseZO();
}
