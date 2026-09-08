// ?bfmeSetupJY@@YAXPAVBfmeCodecJY@@PBI@Z
// partial score=0.85 date=2026-09-08
extern "C" void *__cdecl memcpy(void *d, const void *s, unsigned int n);

class BfmeCodecJY
{
public:
	unsigned char m_bfmeHeadJY[0x40];
	unsigned int m_bfme40JY;
	unsigned int m_bfme44JY;
	unsigned int m_bfme48JY;
	unsigned int m_bfme4cJY;
	unsigned int m_bfmeRestJY[10];
	unsigned int m_bfme78JY;
	unsigned int m_bfme7cJY;
	unsigned int m_bfme80JY;
	unsigned int m_bfme84JY;
	unsigned int m_bfme88JY;
	unsigned int m_bfme8cJY;
	unsigned int m_bfme90JY;
	unsigned int m_bfme94JY;
	unsigned int m_bfme98JY;
	unsigned int m_bfme9cJY;
	unsigned char m_bfmeGapJY[0x14];
	unsigned int m_bfmeB4JY;
};

void bfmeSetupJY(BfmeCodecJY *p, const unsigned int *src)
{
	memcpy(&p->m_bfme40JY, src, 14 * 4);

	unsigned int a = p->m_bfme40JY;
	unsigned int m44 = p->m_bfme44JY;
	unsigned int m48 = p->m_bfme48JY;

	a = a >> 3;

	unsigned int b = m44 >> 3;

	p->m_bfme94JY = b;

	unsigned int ab = b * a;

	p->m_bfme84JY = ab;

	unsigned int c = p->m_bfme4cJY;
	unsigned int q = ab >> 2;

	p->m_bfme8cJY = ab + q * 2;
	p->m_bfme90JY = a;

	unsigned int d = (m48 - a * 8) >> 1;

	p->m_bfme78JY = (m48 + 1) * d;

	unsigned int e = (m44 + d * 2) * m48;

	p->m_bfme98JY = m48;

	unsigned int h = d >> 1;

	p->m_bfmeB4JY = d;
	p->m_bfme88JY = q;
	p->m_bfme7cJY = (c + 1) * h + e;
	p->m_bfme9cJY = c;
	p->m_bfme80JY = h * c + (((m44 >> 1) + d) * c + h) + e;
}
