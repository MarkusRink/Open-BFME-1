// cl: /Od
extern "C" void *bfmeVftGL[];
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *d, const char *s, unsigned int n);

int rva0082C160Deref(int *p);

class BfmeBaseGL
{
public:
	__declspec(dllimport) BfmeBaseGL();
	~BfmeBaseGL();

	void *m_bfmeVftGL;
	unsigned char m_bfmeBaseGapGL[8];
};

class BfmeHolderGL : public BfmeBaseGL
{
public:
	BfmeHolderGL(int *p);

	char m_bfmeBufGL[0x100];
};

BfmeHolderGL::BfmeHolderGL(int *p)
{
	m_bfmeVftGL = bfmeVftGL;

	strncpy(m_bfmeBufGL, (const char *)rva0082C160Deref(p), 0x100);

	m_bfmeBufGL[0xff] = 0;
}
