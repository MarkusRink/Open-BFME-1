// ?bfmeAtBX@BfmeOwnBX@@QAEXHPAX@Z (identity unknown)
// partial score=0.8 date=2026-09-06
// 59 bytes from MSVC against retail's 62. The whole magic-division block is
// byte-exact -- `m_end - m_begin` on an 0x58-byte element type produces
// retail's 0x2e8ba2e9 / sar 4 / shr 31 / add sequence for free, and the
// `jae` needs the unsigned cast on both sides of the bound check.
// Residue: retail saves esi at entry and keeps `this` there; MSVC shrink-wraps
// the push past the first guard and puts `this` in eax. Tried an early-return
// pair, a single && chain (signed and unsigned), a named self local and a
// named begin local; the push always shrink-wraps.
class BfmeElemBX
{
public:
	void bfmeApplyBX(void *value);

	unsigned char m_bfmeHeadBX[0x58];
};

class BfmeOwnBX
{
public:
	void bfmeAtBX(int index, void *value);

	unsigned char m_bfmeHeadBX[0x18];
	BfmeElemBX *m_bfmeBeginBX;
	BfmeElemBX *m_bfmeEndBX;
};

void BfmeOwnBX::bfmeAtBX(int index, void *value)
{
	if (index < 0)
		return;

	if ((unsigned int)index >= (unsigned int)(m_bfmeEndBX - m_bfmeBeginBX))
		return;

	m_bfmeBeginBX[index].bfmeApplyBX(value);
}
