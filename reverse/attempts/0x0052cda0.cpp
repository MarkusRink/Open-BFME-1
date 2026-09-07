// ?d_0052cda0@@YAXXZ
// partial score=0.97 date=2026-09-08
struct Rva00579160Manager { void fire(void* target, const char* name, int a, int b, int c, int d, int e, int f); };
extern Rva00579160Manager* Rva00579160TheManager;
extern char g_bfmeFmt1057[];
extern char g_bfmeEscAI[];

class BfmeOwnerEAG
{
public:
	unsigned char m_bfmeHeadEAG[0x250];
	void *m_bfmeTargetEAG;
};

class BfmeHostEAG
{
public:
	int bfmeKeyEAG(int unused, int code, unsigned char kind, unsigned char flags);
	void bfmeCloseEAG(int mode);

	unsigned char m_bfmeHeadEAG[0x34];
	BfmeOwnerEAG *m_bfmeOwnerEAG;
	unsigned char m_bfmePadEAG[0x70];
	int m_bfmeStateEAG;
};

int BfmeHostEAG::bfmeKeyEAG(int unused, int code, unsigned char kind, unsigned char flags)
{
	if (code == 0x15 && kind - 1 == 0 && (flags & 1) != 0 && m_bfmeStateEAG != 4)
	{
		Rva00579160TheManager->fire(m_bfmeOwnerEAG->m_bfmeTargetEAG,
			g_bfmeFmt1057, 1, (int)g_bfmeEscAI, 0, 0, 0, 0);

		bfmeCloseEAG(0);

		return 1;
	}

	return 0;
}
