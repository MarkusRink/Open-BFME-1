// ?bfmeSendCH@BfmeHostCH@@QAEXPAVBfmeSrcCH@@PAX@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 66/66 at exact size. Every instruction matches; only two are transposed.
// Retail schedules   mov eax,[ecx] (vftable) / mov byte [esp+8],0 / call
// MSVC schedules     mov byte [esp+8],0 / mov eax,[ecx] / call
// Moving the call into a named local first (`void *made = t->bfmeMakeCH();`)
// fixes the vftable position but then pushes the byte store PAST the call, so
// the two orderings are the only ones reachable: the byte store sits either
// before the vftable load or after the call, never between.
// The 0x10-byte request block, its field order (D, C, B, then A from the call
// result) and the two-argument dispatch all match exactly.
class BfmeThingCH
{
public:
	virtual void bfmeSlot00CH();
	virtual void bfmeSlot01CH();
	virtual void bfmeSlot02CH();
	virtual void bfmeSlot03CH();
	virtual void bfmeSlot04CH();
	virtual void bfmeSlot05CH();
	virtual void bfmeSlot06CH();
	virtual void bfmeSlot07CH();
	virtual void bfmeSlot08CH();
	virtual void bfmeSlot09CH();
	virtual void bfmeSlot10CH();
	virtual void bfmeSlot11CH();
	virtual void bfmeSlot12CH();
	virtual void bfmeSlot13CH();
	virtual void bfmeSlot14CH();
	virtual void bfmeSlot15CH();
	virtual void bfmeSlot16CH();
	virtual void bfmeSlot17CH();
	virtual void bfmeSlot18CH();
	virtual void bfmeSlot19CH();
	virtual void bfmeSlot20CH();
	virtual void bfmeSlot21CH();
	virtual void bfmeSlot22CH();
	virtual void bfmeSlot23CH();
	virtual void bfmeSlot24CH();
	virtual void bfmeSlot25CH();
	virtual void bfmeSlot26CH();
	virtual void bfmeSlot27CH();
	virtual void bfmeSlot28CH();
	virtual void bfmeSlot29CH();
	virtual void bfmeSlot30CH();
	virtual void bfmeSlot31CH();
	virtual void bfmeSlot32CH();
	virtual void bfmeSlot33CH();
	virtual void bfmeSlot34CH();
	virtual void bfmeSlot35CH();
	virtual void bfmeSlot36CH();
	virtual void bfmeSlot37CH();
	virtual void bfmeSlot38CH();
	virtual void bfmeSlot39CH();
	virtual void bfmeSlot40CH();
	virtual void bfmeSlot41CH();
	virtual void bfmeSlot42CH();
	virtual void bfmeSlot43CH();
	virtual void bfmeSlot44CH();
	virtual void bfmeSlot45CH();
	virtual void bfmeSlot46CH();
	virtual void bfmeSlot47CH();
	virtual void bfmeSlot48CH();
	virtual void bfmeSlot49CH();
	virtual void bfmeSlot50CH();
	virtual void bfmeSlot51CH();
	virtual void bfmeSlot52CH();
	virtual void bfmeSlot53CH();
	virtual void bfmeSlot54CH();
	virtual void bfmeSlot55CH();
	virtual void bfmeSlot56CH();
	virtual void bfmeSlot57CH();
	virtual void bfmeSlot58CH();
	virtual void bfmeSlot59CH();
	virtual void bfmeSlot60CH();
	virtual void bfmeSlot61CH();
	virtual void bfmeSlot62CH();
	virtual void bfmeSlot63CH();
	virtual void bfmeSlot64CH();
	virtual void bfmeSlot65CH();
	virtual void bfmeSlot66CH();
	virtual void bfmeSlot67CH();
	virtual void bfmeSlot68CH();
	virtual void bfmeSlot69CH();
	virtual void bfmeSlot70CH();
	virtual void bfmeSlot71CH();
	virtual void bfmeSlot72CH();
	virtual void bfmeSlot73CH();
	virtual void bfmeSlot74CH();
	virtual void bfmeSlot75CH();
	virtual void bfmeSlot76CH();
	virtual void bfmeSlot77CH();
	virtual void bfmeSlot78CH();
	virtual void bfmeSlot79CH();
	virtual void bfmeSlot80CH();
	virtual void *bfmeMakeCH();
};

class BfmeSrcCH
{
public:
	unsigned char m_bfmeHeadCH[0x1fc];
	BfmeThingCH *m_bfmeTargetCH;
};

struct BfmeReqCH
{
	void *m_bfmeACH;
	unsigned char m_bfmeBCH;
	unsigned char m_bfmePadCH[3];
	BfmeSrcCH *m_bfmeCCH;
	BfmeSrcCH *m_bfmeDCH;
};

class BfmeHostCH
{
public:
	void bfmeSendCH(BfmeSrcCH *src, void *unused);
	void bfmeDispatchCH(BfmeReqCH *req, int mode);
};

void BfmeHostCH::bfmeSendCH(BfmeSrcCH *src, void *unused)
{
	BfmeThingCH *t = src->m_bfmeTargetCH;

	if (t == 0)
		return;

	BfmeReqCH req;

	req.m_bfmeDCH = src;
	req.m_bfmeCCH = src;
	req.m_bfmeBCH = 0;
	req.m_bfmeACH = t->bfmeMakeCH();

	bfmeDispatchCH(&req, 0);
}
