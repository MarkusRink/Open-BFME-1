// ?bfmeHasFK@BfmeHostFK@@QAEDPBVBfmeHolderFK@@@Z
// partial score=0.90 date=2026-09-08
extern "C" int memcmp(const void *a, const void *b, unsigned int n);

#pragma intrinsic(memcmp)

extern char *Rva006A16B0Empty;

class BfmeStrFK
{
public:
	unsigned char m_bfmeHeadFK[4];
	unsigned short m_bfmeLenFK;
	unsigned char m_bfmeGapFK[2];
	char m_bfmeDataFK[1];
};

class BfmeHolderFK
{
public:
	unsigned char m_bfmeHeadFK[0x20];
	BfmeStrFK *m_bfmeStrFK;
};

class BfmeHostFK
{
public:
	char bfmeHasFK(const BfmeHolderFK *h);

	unsigned char m_bfmeHeadFK[0x2d0];
	BfmeStrFK **m_bfmeBeginFK;
	BfmeStrFK **m_bfmeEndFK;
};

char BfmeHostFK::bfmeHasFK(const BfmeHolderFK *h)
{
	BfmeStrFK **p = m_bfmeBeginFK;
	BfmeStrFK **e = m_bfmeEndFK;

	if (p == e)
		return 0;

	while (p != e)
	{
		BfmeStrFK *a = *p;
		int alen = a != 0 ? a->m_bfmeLenFK : 0;
		const char *ad = a != 0 ? a->m_bfmeDataFK : (const char *)&Rva006A16B0Empty;

		BfmeStrFK *b = *(BfmeStrFK *volatile *)&h->m_bfmeStrFK;
		int blen = b != 0 ? b->m_bfmeLenFK : 0;
		const char *bd = b != 0 ? b->m_bfmeDataFK : (const char *)&Rva006A16B0Empty;

		int n = blen < alen ? blen : alen;
		int r = memcmp(bd, ad, n);

		if (r == 0)
			r = blen - alen;

		if (r == 0)
			return 1;

		++p;
	}

	return 0;
}
