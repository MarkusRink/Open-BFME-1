// ?bfmeFmtESJ@BfmeHostESJ@@QAE?AUBfmePairESJ@@PAX0PAVBfmeStreamESJ@@HH@Z
// partial score=0.97 date=2026-09-07
// 107/107 EXACT SIZE, ONE misplaced instruction: retail hoists the inner
// call's sret address above the argument pushes
//   retail  lea edx,[esp+0x18] / push eax / mov eax,[esp+0x30] / push esi ...
//   MSVC    push eax / mov eax,[esp+0x30] / push esi / push eax / push ecx /
//           lea edx,[esp+0x28] / push edx
// Both push edx last; only the lea moves. Ruled out: hoisting the inner
// fmt call into a local (109, and the register allocation drifts); declaring
// result before saved and assigning instead of initialising (104).
//
// SIBLING: 0x008324F0 is BYTE-IDENTICAL except call [edx+0x18] becomes
// call [edx+0x28] -- virtual slot 6 vs slot 10 on stream->m_40. One fix lands
// both, 214 bytes.
//
// Reading notes that made the model fall out:
//  * ret 0x18 with an 8-byte struct returned by value: six dword args, the
//    first (E+4) is the sret pointer, and E+20 is never read -- an unused
//    parameter that still has to be declared.
//  * the first call pops only 4, so the earlier push edx / push eax are not
//    its arguments -- they are the 64-bit last argument of the SECOND call,
//    built by cdq from the int at E+24.
//  * lea edx,[esp+0x18] resolves to the 8-byte local from sub esp,8, which is
//    the inner call's sret buffer; the tail copies it into our own.
struct BfmePairESJ
{
	int m_bfmeLoESJ;
	int m_bfmeHiESJ;
};

class BfmeFmtESJ
{
public:
	virtual void bfmeFmt00ESJ();
	virtual void bfmeFmt01ESJ();
	virtual void bfmeFmt02ESJ();
	virtual void bfmeFmt03ESJ();
	virtual void bfmeFmt04ESJ();
	virtual void bfmeFmt05ESJ();
	virtual void *bfmeFmt06ESJ(int mode);
};

class BfmeStreamESJ
{
public:
	unsigned char m_bfmeHeadESJ[4];
	int m_bfmeFlagsESJ;
	unsigned char m_bfmeMidESJ[0x14];
	int m_bfmePrecESJ;
	unsigned char m_bfmeTailESJ[0x20];
	BfmeFmtESJ *m_bfmeFmtESJ;
};

class BfmeHostESJ
{
public:
	virtual void bfmeSlot00ESJ();
	virtual void bfmeSlot01ESJ();
	virtual BfmePairESJ bfmeSlot02ESJ(void *a, void *b, BfmeStreamESJ *stream,
		void *fmt, __int64 value);

	BfmePairESJ bfmeFmtESJ(void *a, void *b, BfmeStreamESJ *stream, int unused,
		int value);
};

BfmePairESJ BfmeHostESJ::bfmeFmtESJ(void *a, void *b, BfmeStreamESJ *stream,
	int unused, int value)
{
	int saved = stream->m_bfmeFlagsESJ;

	stream->m_bfmeFlagsESJ = (saved & ~0x2b) | 0x214;
	stream->m_bfmePrecESJ = 10;

	BfmePairESJ result = bfmeSlot02ESJ(a, b, stream,
		stream->m_bfmeFmtESJ->bfmeFmt06ESJ(0x30), value);

	stream->m_bfmeFlagsESJ = saved;

	return result;
}
