// ?bfmeFillAAM@@YAPAUBfmeEntryAAM@@PAU1@IABU1@@Z
// partial score=0.85 date=2026-09-08
inline void *operator new(unsigned int, void *p)
{
	return p;
}

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &o);

	void *m_bfmeDataAAM;
};

struct BfmeEntryAAM
{
	int m_bfme00AAM;
	int m_bfme04AAM;
	int m_bfme08AAM;
	int m_bfme0CAAM;
	int m_bfme10AAM;
	int m_bfme14AAM;
	int m_bfme18AAM;
	GameSpyGroupRoom m_bfme1CAAM;
	char m_bfme20AAM;
};

BfmeEntryAAM *bfmeFillAAM(BfmeEntryAAM *dst, unsigned int count, const BfmeEntryAAM &src);

BfmeEntryAAM *bfmeFillAAM(BfmeEntryAAM *dst, unsigned int count, const BfmeEntryAAM &src)
{
	for (unsigned int n = count; n != 0; --n)
	{
		new (dst) BfmeEntryAAM(src);
		++dst;
	}

	return dst;
}
