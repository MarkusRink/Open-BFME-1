// ?bfmeApplyESP@@YAXPBD0@Z
// partial score=0.74 date=2026-09-08

struct BfmeHdrESP
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPoolESP
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPoolESP *g_bfmeStringPool1284;
extern unsigned char g_bfmeFlagESP;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text);

	void bfmeSetVKI(const char *text);
	BfmeStrVKI *operator&()
	{
		return this;
	}

	~BfmeStrVKI()
	{
		BfmeHdrESP *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeHdrESP *m_data;
};

class Rva00896AF0Tracker
{
public:
	void rva00896AF0(BfmeStrVKI *input, BfmeStrVKI text);
};

extern Rva00896AF0Tracker *g_bfmeTracker4310;

void bfmeApplyESP(const char *first, const char *second)
{
	g_bfmeTracker4310->rva00896AF0(
		&(g_bfmeFlagESP = 0, BfmeStrVKI(first)), BfmeStrVKI(second));
}
