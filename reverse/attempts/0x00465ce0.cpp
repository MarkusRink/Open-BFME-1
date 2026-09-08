// ?bfmeLookupGD@@YAHPAVBfmeWindowGD@@@Z
// partial score=0.7 date=2026-09-08
class BfmeResultGD
{
public:
	unsigned char m_bfmeHeadGD[0x250];
	int m_bfmeValueGD;
};

class BfmeWindowGD
{
public:
	BfmeWindowGD *bfmeParentGD();
};

class GameWindowManager
{
public:
	virtual void bfmeVtGD00();
	virtual void bfmeVtGD01();
	virtual void bfmeVtGD02();
	virtual void bfmeVtGD03();
	virtual void bfmeVtGD04();
	virtual void bfmeVtGD05();
	virtual void bfmeVtGD06();
	virtual void bfmeVtGD07();
	virtual void bfmeVtGD08();
	virtual void bfmeVtGD09();
	virtual void bfmeVtGD10();
	virtual void bfmeVtGD11();
	virtual void bfmeVtGD12();
	virtual void bfmeVtGD13();
	virtual void bfmeVtGD14();
	virtual void bfmeVtGD15();
	virtual void bfmeVtGD16();
	virtual void bfmeVtGD17();
	virtual void bfmeVtGD18();
	virtual void bfmeVtGD19();
	virtual void bfmeVtGD20();
	virtual void bfmeVtGD21();
	virtual void bfmeVtGD22();
	virtual void bfmeVtGD23();
	virtual void bfmeVtGD24();
	virtual void bfmeVtGD25();
	virtual void bfmeVtGD26();
	virtual void bfmeVtGD27();
	virtual void bfmeVtGD28();
	virtual void bfmeVtGD29();
	virtual void bfmeVtGD30();
	virtual void bfmeVtGD31();
	virtual void bfmeVtGD32();
	virtual void bfmeVtGD33();
	virtual void bfmeVtGD34();
	virtual void bfmeVtGD35();
	virtual void bfmeVtGD36();
	virtual void bfmeVtGD37();
	virtual void bfmeVtGD38();
	virtual void bfmeVtGD39();
	virtual void bfmeVtGD40();
	virtual void bfmeVtGD41();
	virtual void bfmeVtGD42();
	virtual void bfmeVtGD43();
	virtual void bfmeVtGD44();
	virtual void bfmeVtGD45();
	virtual void bfmeVtGD46();
	virtual void bfmeVtGD47();
	virtual void bfmeVtGD48();
	virtual void bfmeVtGD49();
	virtual void bfmeVtGD50();
	virtual void bfmeVtGD51();
	virtual void bfmeVtGD52();
	virtual void bfmeFindGD(BfmeWindowGD *w, int a, int b, BfmeResultGD **out);
};

extern GameWindowManager *TheWindowManager;

int __cdecl bfmeLookupGD(BfmeWindowGD *w)
{
	if (w == 0)
	{
		return -1;
	}
	else
	{
		BfmeResultGD *out = 0;

		while (w != 0 && out == 0)
		{
			TheWindowManager->bfmeFindGD(w, 0x1d, 0x7d0, &out);

			w = w->bfmeParentGD();
		}

		if (out != 0)
			return out->m_bfmeValueGD;

		return 0xc;
	}
}
