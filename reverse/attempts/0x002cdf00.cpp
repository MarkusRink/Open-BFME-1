// ?bfmeGoBN@BfmeHostBN@@QAEXPAVBfmeThingBN@@@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 86/85. Everything from +0x26 on is identical, including the negative-offset
// secondary-base read `mov ecx,[edi-0x18]` (a plain cast, per
// [[negative-this-is-raw-arithmetic]]), the two slot-10 calls, the shared
// and-chain exit, and the tail `jmp` that reuses the argument slot after
// zeroing it ([[tail-jmp-needs-matching-cleanup]]).
// The single extra byte is in the flag block. Retail materialises the bit:
//   mov ecx,[esi+0x130] / mov eax,0x10000 / test eax,ecx / jne / or ecx,eax
// MSVC keeps flags in eax and uses the short immediate forms instead:
//   mov eax,[esi+0x130] / test eax,0x10000 / jne / or eax,0x10000
// which is one byte longer overall. The cause is that `test eax,imm32` is the
// 5-byte a9 encoding, so with flags in EAX the immediate never loses; retail's
// flags sit in ecx (this is saved to edi FIRST), where the immediate test would
// be 6 bytes and the register form wins.
// Tried and did not move it: naming the receiver in a local before the flag
// read, and routing the bit through an inlined function parameter.
// Next lever: find a spelling that keeps eax busy across the flag read so the
// load has to pick ecx.
class BfmeResBN
{
public:
	void bfmeApplyBN(void *arg);
};

class BfmeThingBN
{
public:
	virtual void bfmeSlot00BN();
	virtual void bfmeSlot01BN();
	virtual void bfmeSlot02BN();
	virtual void bfmeSlot03BN();
	virtual void bfmeSlot04BN();
	virtual void bfmeSlot05BN();
	virtual void bfmeSlot06BN();
	virtual void bfmeSlot07BN();
	virtual void bfmeSlot08BN();
	virtual void bfmeSlot09BN();
	virtual BfmeResBN *bfmeGetBN();

	void bfmeNotifyBN();

	unsigned char m_bfmeHeadBN[0x12c];
	int m_bfmeFlagsBN;
};

class BfmeHostBN
{
public:
	void bfmeGoBN(BfmeThingBN *a);
};

void BfmeHostBN::bfmeGoBN(BfmeThingBN *a)
{
	int flags = a->m_bfmeFlagsBN;

	if ((flags & 0x10000) == 0)
	{
		a->m_bfmeFlagsBN = flags | 0x10000;
		a->bfmeNotifyBN();
	}

	BfmeResBN *first = (*(BfmeThingBN **)((char *)this - 0x18))->bfmeGetBN();
	BfmeResBN *second = a->bfmeGetBN();

	if (second != 0 && first != 0)
		second->bfmeApplyBN(0);
}
