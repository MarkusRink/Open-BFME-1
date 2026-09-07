// ?bfmeGetPX@@YGPAXPAVBfmeUnitPX@@@Z (identity unknown)
// partial score=0.99 date=2026-09-07
// 107/108 bytes; ONE instruction differs out of 34.
// Everything is settled: early returns (not nesting) so the shared `xor eax,eax`
// sits between the guards and the second resolve, and the second resolve
// written with its tail DUPLICATED and the null arm first.
// Residue: in that null arm MSVC propagates again==0 and emits
// `mov eax,[4b4h]` (5 bytes, absolute) where retail keeps
// `mov eax,[eax+4b4h]` (6 bytes). Identical to the blocker on 0x001B57E0.
// Ruled out: the plain `if (t && t->m_inner)` form shares the tail (98 bytes),
// and /Ot /Og /G7 /Oy /Op do not make MSVC duplicate it late instead.
class BfmeThingPX;

class BfmeInnerPX
{
public:
	BfmeThingPX *bfmeResolvePX(void);
};

class BfmeThingPX
{
public:
	int m_bfmeSparePX;
	BfmeInnerPX *m_bfmeInnerPX;
	unsigned char m_bfmeGapPX[0xc0];
	unsigned char m_bfmeFlagsPX;
	unsigned char m_bfmeTailPX[0x3eb];
	void *m_bfmeValuePX;
};

class BfmeUnitPX
{
public:
	char bfmeCanPX(int what);

	int m_bfmeSparePX;
	BfmeThingPX *m_bfmeThingPX;
};

void * __stdcall bfmeGetPX(BfmeUnitPX *unit)
{
	if (!unit)
		return 0;

	BfmeThingPX *thing = unit->m_bfmeThingPX;

	if (thing && thing->m_bfmeInnerPX)
		thing = thing->m_bfmeInnerPX->bfmeResolvePX();

	if ((thing->m_bfmeFlagsPX & 2) == 0)
		return 0;

	if (unit->bfmeCanPX(7))
		return 0;

	if (unit->bfmeCanPX(0x6c))
		return 0;

	BfmeThingPX *again = unit->m_bfmeThingPX;

	if (again == 0)
		return again->m_bfmeValuePX;

	if (again->m_bfmeInnerPX)
		again = again->m_bfmeInnerPX->bfmeResolvePX();

	return again->m_bfmeValuePX;
}
