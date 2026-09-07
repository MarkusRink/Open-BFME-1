// ?rva0087F180ParseHeight@@YAXPAVINI@@PAXPAVRva0087F180Owner@@@Z
// partial score=0.85 date=2026-09-06
// ?rva0087F180ParseHeight@@YAXPAVINI@@PAXPAVRva0087F180Owner@@@Z
// Address-derived: an INI-style field parser. If the owner's dynamic array
// (36-byte elements, [m_arrStart, m_arrEnd)) is non-empty, parses a real
// token from the INI reader (arg0) and stores it into the last element's
// offset-4 field (m_arrEnd - 0x20), then calls the already-named callee at
// 0x0087EE60 (thiscall, no args) and bfmeApplyEB on the owner.
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static float scanReal(const char *token);
};

class BfmeObjEB;
extern void bfmeApplyEB(BfmeObjEB *obj);

extern void d_0087ee60();

class Rva0087F180Owner
{
public:
	unsigned char m_pad0[0x2c];
	char *m_arrStart;
	char *m_arrEnd;
};

void rva0087F180ParseHeight(INI *ini, void *store, Rva0087F180Owner *owner)
{
	int count = (int)(owner->m_arrEnd - owner->m_arrStart) / 36;
	if (count != 0)
	{
		const char *token = ini->getNextToken(0);
		float value = INI::scanReal(token);
		*(float *)(owner->m_arrEnd - 0x20) = value;
	}

	typedef void (Rva0087F180Owner::*BoundsFn)();
	union { void (*raw)(); BoundsFn member; } fn;
	fn.raw = d_0087ee60;
	(owner->*fn.member)();

	bfmeApplyEB((BfmeObjEB *)owner);
}
