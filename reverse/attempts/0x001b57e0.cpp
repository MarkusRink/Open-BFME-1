// ?bfmeRangeXR@BfmeOwnerXR@@QAEMPAVBfmeUnitXR@@@Z (identity unknown)
// partial score=0.98 date=2026-09-07
// 94/94 bytes; ONE instruction differs out of 25.
// Getting here needed the tail written TWICE in the source (retail duplicates
// the fld/fmul/fmul/ret block; a single `if (t && t->m_inner)` shares it and
// costs 19 bytes) and the null arm written FIRST as `if (thing == 0) return
// ...;` so it is the fall-through (the `if (thing) {...} return ...;` order
// puts the copies the other way round).
// Residue: in that null arm MSVC propagates thing==0 and emits
// `fmul dword ptr [12ch]` -- an absolute address -- where retail keeps
// `fmul dword ptr [eax+12ch]`. Re-reading the member instead of the local in
// that arm makes MSVC reload the pointer (bigger). Null-propagation residue.
class BfmeThingXR;

class BfmeInnerXR
{
public:
	BfmeThingXR *bfmeResolveXR(void);
};

class BfmeThingXR
{
public:
	int m_bfmeSpareXR;
	BfmeInnerXR *m_bfmeInnerXR;
	unsigned char m_bfmeGapXR[0x124];
	float m_bfmeFactorXR;
};

class BfmeStateXR
{
public:
	unsigned char m_bfmeHeadXR[0x1d4];
	float m_bfmeScaleXR;
};

class BfmeUnitXR
{
public:
	unsigned char m_bfmeHeadXR[0x204];
	BfmeStateXR *m_bfmeStateXR;
};

extern const float BfmeZeroRange;
extern volatile float g_rva001B59ScaleConstant;

class BfmeOwnerXR
{
public:
	float bfmeRangeXR(BfmeUnitXR *unit);

	int m_bfmeSpareXR;
	BfmeThingXR *m_bfmeThingXR;
};

float BfmeOwnerXR::bfmeRangeXR(BfmeUnitXR *unit)
{
	if (!unit)
		return BfmeZeroRange;

	BfmeStateXR *state = unit->m_bfmeStateXR;

	if (!state)
		return BfmeZeroRange;

	float scale = state->m_bfmeScaleXR;
	BfmeThingXR *thing = m_bfmeThingXR;

	if (thing == 0)
		return g_rva001B59ScaleConstant * thing->m_bfmeFactorXR * scale;

	if (thing->m_bfmeInnerXR)
		thing = thing->m_bfmeInnerXR->bfmeResolveXR();

	return g_rva001B59ScaleConstant * thing->m_bfmeFactorXR * scale;
}
