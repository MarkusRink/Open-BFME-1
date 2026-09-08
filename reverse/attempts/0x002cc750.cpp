// ?bfmeMarkGB@BfmeHostGB@@QAEXPAVBfmeObjGB@@@Z
// partial score=0.95 date=2026-09-08
class BfmeObjGB
{
public:
	void bfmeNotifyGB();

	unsigned char m_bfmeHeadGB[0x118];
	volatile unsigned int m_bfmeFlagsGB;
};

__forceinline void bfmeApplyGB(BfmeObjGB *o)
{
	unsigned int f = o->m_bfmeFlagsGB;

	if ((f & 0x20000) != 0 || (f & 0x40000) == 0)
	{
		unsigned int a = o->m_bfmeFlagsGB & 0xfffdffff;
		unsigned int b = a | 0x40000;

		o->m_bfmeFlagsGB = a;
		o->m_bfmeFlagsGB = b;

		o->bfmeNotifyGB();
	}
}

class BfmeHostGB
{
public:
	void bfmeMarkGB(BfmeObjGB *other);
};

void BfmeHostGB::bfmeMarkGB(BfmeObjGB *other)
{
	bfmeApplyGB(*(BfmeObjGB **)((char *)this - 0x18));
	bfmeApplyGB(other);
}
