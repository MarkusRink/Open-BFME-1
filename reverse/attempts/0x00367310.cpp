// ?bfmeStartRT@BfmeOwnerRT@@QAEXXZ (identity unknown)
// partial score=0.95 date=2026-09-07
// 25/25 bytes; 4 instructions differ, all from one scheduling choice.
// retail  push 0 / lea eax,[ecx+3ch] / push eax / mov [ecx+20h],4 / call
// ours    mov [ecx+20h],4 / push 0 / add ecx,3ch / push ecx / call
// MSVC emits the state store first (source order) and, `this` being dead
// afterwards, computes the argument with `add ecx` instead of `lea eax`.
// Retail keeps `this` live because its store comes after the address.
// Tried: hoisting the argument address into a local before the store (MSVC
// sinks the lea back past it).
struct BfmeDataRT
{
	unsigned char m_bfmeRawRT[4];
};

void __stdcall bfmeBeginRT(BfmeDataRT *data, int flag);

class BfmeOwnerRT
{
public:
	void bfmeStartRT(void);

	unsigned char m_bfmeHeadRT[0x20];
	int m_bfmeStateRT;
	unsigned char m_bfmeGapRT[0x18];
	BfmeDataRT m_bfmeDataRT;
};

void BfmeOwnerRT::bfmeStartRT(void)
{
	if (m_bfmeStateRT == 3)
	{
		BfmeDataRT *data = &m_bfmeDataRT;

		m_bfmeStateRT = 4;
		bfmeBeginRT(data, 0);
	}
}
