// ?bfmeTestEL@BfmeHostEL@@QBEDPBVBfmeMtxEL@@@Z
// partial score=0.92 date=2026-09-08
extern const float BfmeZeroRange;

class BfmeMtxEL
{
public:
	unsigned char m_bfmeHeadEL[8];
	float m_bfmeAEL;
	unsigned char m_bfmePad0EL[0xc];
	float m_bfmeBEL;
	unsigned char m_bfmePad1EL[0xc];
	float m_bfmeCEL;
	unsigned char m_bfmePad2EL[0xc];
	float m_bfmeXEL;
	float m_bfmeYEL;
	float m_bfmeZEL;
};

class BfmeInfoEL
{
public:
	unsigned char m_bfmeHeadEL[0x138];
	float m_bfmeRangeEL;
};

class BfmeOtherEL
{
public:
	unsigned char m_bfmeHeadEL[0x38];
	float m_bfmeXEL;
	float m_bfmeYEL;
	float m_bfmeZEL;
};

class BfmeBaseEL
{
public:
	BfmeInfoEL *m_bfmeInfoEL;
	BfmeOtherEL *m_bfmeOtherEL;
};

class BfmeHostEL
{
public:
	char bfmeTestEL(const BfmeMtxEL *m) const;
};

char BfmeHostEL::bfmeTestEL(const BfmeMtxEL *m) const
{
	if (m == 0)
		return 0;

	const BfmeBaseEL *base = (const BfmeBaseEL *)((const char *)this - 0x1c);
	BfmeInfoEL *info = base->m_bfmeInfoEL;

	if (info->m_bfmeRangeEL < BfmeZeroRange)
		return 0;

	BfmeOtherEL *o = base->m_bfmeOtherEL;

	if (m->m_bfmeZEL - o->m_bfmeZEL > info->m_bfmeRangeEL)
		return 0;

	float a = m->m_bfmeAEL;
	float b = m->m_bfmeBEL;
	float c = m->m_bfmeCEL;
	volatile float e = o->m_bfmeXEL - m->m_bfmeXEL;
	float d = o->m_bfmeYEL - m->m_bfmeYEL;

	if (a * e + b * d + c * BfmeZeroRange < BfmeZeroRange)
		return 0;

	return 1;
}
