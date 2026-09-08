// ?bfmeResetYU@BfmeHostYU@@QAEXABVUnicodeString@@@Z
// partial score=0.94 date=2026-09-08
// pins needed (CRLF):
//   ?bfmeCommonInitYU@BfmeHostYU@@QAEXXZ,0x0002E68B
//   __imp_?bfmeDecYU@@YGHPAX@Z,0x01358E54
class UnicodeString
{
public:
	void set(const UnicodeString &o);

	void *m_bfmeDataYU;
};

__declspec(dllimport) int __stdcall bfmeDecYU(void *p);

class BfmeThingYU
{
public:
	virtual void bfmeDestroyYU(int flag) = 0;

	int m_bfme04YU;
};

class BfmeHostYU
{
public:
	void bfmeResetYU(const UnicodeString &s);
	void bfmeCommonInitYU();

	unsigned char m_bfmeHeadYU[8];
	BfmeThingYU *m_bfme08YU;
	unsigned char m_bfmeGapYU[8];
	UnicodeString m_bfme14YU;
};

void BfmeHostYU::bfmeResetYU(const UnicodeString &s)
{
	bfmeCommonInitYU();
	m_bfme14YU.set(s);

	BfmeThingYU *t = m_bfme08YU;

	if (t != 0)
	{
		if (bfmeDecYU(&t->m_bfme04YU) <= 0 && t != 0)
			t->bfmeDestroyYU(1);

		m_bfme08YU = 0;
	}
}
