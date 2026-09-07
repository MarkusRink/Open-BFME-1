// ?bfmeHandleDR@BfmeHostDR@@QAEXPAVBfmeSrcDR@@PAX@Z (identity unknown)
// partial score=0.98 date=2026-09-07
// 139/139 at exact size, ONE instruction left: retail forms the &name argument
// with `lea eax,[esp+0x1c] / push eax`, MSVC with `lea ecx,... / push ecx`.
// The string is a NAMED local copy-constructed from src->info->name and living
// in the dead arg1 home slot, so this is not the temporary-in-argument-area
// shape and carries no esp marker.
// Hoisting arguments into locals fixed the OTHER register diff -- `void *e =
// extra;` before the four-argument apply call turned `mov edx,[esp+0x20]` into
// retail's `mov ecx,...` (see [[ecx-edx-flip-is-systematic]]'s correction and
// [[name-both-call-arguments]]). The remaining one does not move: tried
// hoisting the other argument (`BfmeThingDR *t = thing;`) and re-binding the
// name to a second const reference.
class BfmeSrcDR;
class BfmeThingDR;
class BfmeItemDR;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &other);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufDR;

private:
	void releaseBuffer();
};

class BfmeInfoDR
{
public:
	unsigned char m_bfmeHeadDR[8];
	BFMERetailAsciiString m_bfmeNameDR;
};

class BfmeSrcDR
{
public:
	unsigned char m_bfmeHeadDR[0x210];
	BfmeInfoDR *m_bfmeInfoDR;
};

extern "C" BfmeThingDR *__stdcall bfmeLookupDR(BfmeSrcDR *src);

class BfmeHostDR
{
public:
	void bfmeHandleDR(BfmeSrcDR *src, void *extra);

	BfmeItemDR *bfmeFindDR(BfmeThingDR *thing, const BFMERetailAsciiString &name);
	void bfmeApplyDR(BfmeItemDR *item, BfmeSrcDR *src, void *extra, int mode);
};

void BfmeHostDR::bfmeHandleDR(BfmeSrcDR *src, void *extra)
{
	BfmeThingDR *thing = bfmeLookupDR(src);

	if (thing == 0)
		return;

	BFMERetailAsciiString name = src->m_bfmeInfoDR->m_bfmeNameDR;

	BfmeThingDR *t = thing;

	BfmeItemDR *item = bfmeFindDR(t, name);

	if (item != 0)
	{
		void *e = extra;

		bfmeApplyDR(item, src, e, 0);
	}
}
