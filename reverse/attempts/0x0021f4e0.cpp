// ?bfmeReadyAP@BfmeAgentAP@@QAEDPAX0@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 97/97. Every instruction matches; the only difference is that retail lays the
// `return 0` exit block at +0x55 and `return 1` at +0x5b, MSVC the other way
// round, so the four branch bytes differ (three displacements and the polarity
// of the last test).
// Two things WERE recovered here and are worth reusing:
//   * `test ah,41h / jnp` is the x87 form of `a <= b` used as the jump-to-false
//     -- spelling it `a > b` gives `jne` instead. Write the comparison the way
//     retail branches on it, negating with ! if the source needs the other arm.
//   * every guard that reaches the same exit must be one && / || chain, or MSVC
//     duplicates the 6-byte epilogue inline (that cost 5 bytes here).
// Three arrangements (nested if + two returns, && tail, || head) give identical
// bytes, so the exit-block order is not source-controllable.
extern const float BfmeZeroRange;

class BfmeRangeAP
{
public:
	virtual void bfmeSlot0AP();
	virtual void bfmeSlot1AP();
	virtual void bfmeSlot2AP();
	virtual void bfmeSlot3AP();
	virtual float bfmeRangeAP();
	virtual void bfmeSlot5AP();
	virtual void bfmeSlot6AP();
	virtual void bfmeSlot7AP();
	virtual int bfmeModeAP();
};

class BfmeOwnerAP
{
public:
	char bfmeHasAP(int what);

	unsigned char m_bfmeHeadAP[0x200];
	BfmeRangeAP *m_bfmeRangeAP;
};

class BfmeSubAP
{
public:
	char bfmeTestAP(void *first, void *second);
};

class BfmeAgentAP
{
public:
	char bfmeReadyAP(void *a, void *b);

	unsigned char m_bfmeHeadAP[8];
	BfmeOwnerAP *m_bfmeOwnerAP;
	unsigned char m_bfmeMidAP[0x14];
	BfmeSubAP m_bfmeSubAP;
};

char BfmeAgentAP::bfmeReadyAP(void *a, void *b)
{
	if (m_bfmeSubAP.bfmeTestAP(a, b) == 0 ||
	    m_bfmeOwnerAP->m_bfmeRangeAP->bfmeRangeAP() <= BfmeZeroRange)
		return 0;

	if (m_bfmeOwnerAP->m_bfmeRangeAP->bfmeModeAP() == 2 &&
	    m_bfmeOwnerAP->bfmeHasAP(0x4e) == 0)
		return 0;

	return 1;
}
