// ?bfmeSameZD@BfmeHostZD@@QAE_NPAVDrawable@@@Z
// partial score=0.98 date=2026-09-08
// pins needed (CRLF):
//   ?bfmeFindZD@Rva00367E30Logic@@QAEPAVDrawable@@PAX@Z,0x0001F253
//   ?bfmeTeamOfZD@@YAPAVBfmeTeamZD@@PAVDrawable@@@Z,0x00042424
class Drawable
{
public:
	bool isKindOf(int kind) const;
};

class BfmeTeamZD
{
public:
	virtual void bfmeT0ZD() = 0;
	virtual void *bfmeOwnerZD() = 0;
};

struct Rva00367E30Logic
{
	Drawable *bfmeFindZD(void *id);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

BfmeTeamZD *bfmeTeamOfZD(Drawable *d);

class BfmeHostZD
{
public:
	bool bfmeSameZD(Drawable *other);

	virtual void bfmeV0() = 0;
	virtual void bfmeV1() = 0;
	virtual void bfmeV2() = 0;
	virtual void bfmeV3() = 0;
	virtual void bfmeV4() = 0;
	virtual void bfmeV5() = 0;
	virtual void bfmeV6() = 0;
	virtual void bfmeV7() = 0;
	virtual void bfmeV8() = 0;
	virtual int bfmeModeZD() = 0;

	unsigned char m_bfmeHeadZD[0x10];
	void *m_bfme14ZD;
};

bool BfmeHostZD::bfmeSameZD(Drawable *other)
{
	if (other == 0)
		return false;
	else if (bfmeModeZD() != 1)
		return true;

	Drawable *o = TheBfmeGameLogic->bfmeFindZD(m_bfme14ZD);

	if (o == 0)
		return true;
	else if (o == other)
		return false;
	else if (!o->isKindOf(0x18))
		return true;
	else if (!other->isKindOf(0x18))
		return true;

	BfmeTeamZD *t1 = bfmeTeamOfZD(o);
	BfmeTeamZD *t2 = bfmeTeamOfZD(other);

	if (t1 == 0 || t2 == 0 || t1->bfmeOwnerZD() == t2->bfmeOwnerZD())
		return false;

	return true;
}
