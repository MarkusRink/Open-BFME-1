// ?bfmeLookupAO@@YGHPAPAVBfmeObjAO@@@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 95/95 -- same size, same instructions, same operands. The ONLY difference is
// where MSVC puts the shared `return 0` block: retail emits it inline right
// after the first guard (jne over it, and the second guard jumps BACKWARD to
// it with je 0x612919), MSVC sinks it past the body and branches forward.
// Four source shapes give byte-identical output with the sunk block:
//   if (key == 0) return 0; ... if (it == end) return 0; return v;
//   if (key == 0) return 0; ... if (it != end) return v; return 0;
//   if (key != 0) { ... if (it != end) return v; } return 0;
//   an explicit goto to a `fail: return 0;` label placed between the two
// so the placement is not source-controllable here. Everything else is exact,
// including the reuse of the arg1 home slot for the key and the single load of
// g_bfmeGameCW kept in esi across the call.
extern "C" char *g_bfmeGameCW;

class NameKeyGenerator
{
public:
	int bfmeKeyAO(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeNodeAO
{
public:
	unsigned char m_bfmeHeadAO[0x14];
	int m_bfmeValueAO;
};

class BfmeMapAO
{
public:
	void bfmeFindAO(BfmeNodeAO **out, int *key);

	BfmeNodeAO *m_bfmeEndAO;
};

class BfmeObjAO
{
public:
	unsigned char m_bfmeHeadAO[8];
	char m_bfmeNameAO[1];
};

int __stdcall bfmeLookupAO(BfmeObjAO **holder)
{
	BfmeObjAO *o = *holder;
	int key = TheNameKeyGenerator->bfmeKeyAO(o != 0 ? (const char *)o->m_bfmeNameAO : "");

	if (key == 0)
		return 0;

	BfmeMapAO *m = (BfmeMapAO *)(g_bfmeGameCW + 0x27c);
	BfmeNodeAO *it;

	m->bfmeFindAO(&it, &key);

	if (it != m->m_bfmeEndAO)
		return it->m_bfmeValueAO;

	return 0;
}
