// ?bfmeReadyLT@BfmeOwnerLT@@QAEHXZ (identity unknown)
// partial score=0.9 date=2026-09-07
// 82/82 bytes. The body is two guarded predicate calls on this->m_1c->m_44,
// each taking a member float plus the literal 0.5f (retail pushes it as
// `push 3f000000h`), returning -1 only when both are true.
// The four bytes that make the size are a 4-byte stack local (`push ecx`) that
// is written before each call and never read -- a `volatile float scratch;`
// assigned from the same member reproduces both dead stores and the size, but
// MSVC schedules each store immediately after the first push while retail puts
// it last, after `mov ecx,esi`, and the member/copy register pair comes out
// ecx/edx instead of retail's edx/eax.
// Ruled out: a by-value one-float struct argument (no temp materialised, still
// 67 bytes), and the plain no-local spelling (67 bytes, no slot at all).
class BfmeValuesLT
{
public:
	unsigned char m_bfmeHeadLT[8];
	float m_bfmeFirstLT;
	float m_bfmeSecondLT;
};

class BfmeHolderLT
{
public:
	char bfmeCheckALT(float value, float ratio, int flag);
	char bfmeCheckBLT(float value, float ratio);

	unsigned char m_bfmeHeadLT[8];
	BfmeValuesLT *m_bfmeValuesLT;
};

class BfmeStageLT
{
public:
	unsigned char m_bfmeHeadLT[0x44];
	BfmeHolderLT *m_bfmeHolderLT;
};

class BfmeOwnerLT
{
public:
	int bfmeReadyLT(void);

	unsigned char m_bfmeHeadLT[0x1c];
	BfmeStageLT *m_bfmeStageLT;
};

int BfmeOwnerLT::bfmeReadyLT(void)
{
	BfmeHolderLT *holder = m_bfmeStageLT->m_bfmeHolderLT;
	volatile float scratch;

	scratch = holder->m_bfmeValuesLT->m_bfmeFirstLT;

	char first = holder->bfmeCheckALT(holder->m_bfmeValuesLT->m_bfmeFirstLT, 0.5f, 0);

	scratch = holder->m_bfmeValuesLT->m_bfmeSecondLT;

	char second = holder->bfmeCheckBLT(holder->m_bfmeValuesLT->m_bfmeSecondLT, 0.5f);

	if (first && second)
		return -1;

	return 0;
}
