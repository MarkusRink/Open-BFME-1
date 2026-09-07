// ?bfmePickYP@BfmeOwnerYP@@QAEDHMPAX0@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 95/95, identical instruction sequence, ONE register choice left:
//   retail  mov edx,[esp+8] / shl edx,6 / fcomp [edx+ecx] / add edx,ecx
//   MSVC    mov eax,[esp+8] / shl eax,6 / fcomp [ecx+eax] / add ecx,eax
// Retail keeps `this` in ecx and carries the element pointer in edx across the
// second `fnstsw ax`; MSVC consumes eax into ecx before the fnstsw. Same size,
// same count -- [[argument-shuttle-register]].
// Two levers WERE needed to get here and both generalise:
//   * null-init shared exit: `BfmeThingYP *thing = 0;` before the first guard,
//     then one `if (thing == 0) return 0;` -- otherwise MSVC emits the zero
//     return twice and pushes esi only inside the guarded block (100 bytes).
//     [[null-init-moves-shared-exit]]
//   * `test ah,1 / jne` is the `>=` form with the ELSE at the branch target;
//     writing the comparison as `<` with the arms swapped gives
//     `test ah,5 / jp` instead. Read the mask to pick the operator: mask 1 is
//     C0 only (>=), mask 5 is C0|C2 (the NaN-safe <).
extern const float g_bfmeZeroYP;

class BfmeThingYP
{
public:
	char bfmeReadyYP();
	void bfmeApplyYP(void *a, void *b);
};

struct BfmeSlotYP
{
	float m_bfmeLimitYP;
	BfmeThingYP *m_bfmeHighYP;
	BfmeThingYP *m_bfmeLowYP;
	unsigned char m_bfmePadYP[0x34];
};

class BfmeOwnerYP
{
public:
	char bfmePickYP(int index, float value, void *a3, void *a4);

	BfmeSlotYP m_bfmeSlotsYP[1];
};

char BfmeOwnerYP::bfmePickYP(int index, float value, void *a3, void *a4)
{
	BfmeThingYP *thing = 0;

	if (value != g_bfmeZeroYP)
	{
		if (value >= m_bfmeSlotsYP[index].m_bfmeLimitYP)
			thing = m_bfmeSlotsYP[index].m_bfmeHighYP;
		else
			thing = m_bfmeSlotsYP[index].m_bfmeLowYP;
	}

	if (thing == 0)
		return 0;

	if (thing->bfmeReadyYP() == 0)
		thing->bfmeApplyYP(a4, a3);

	return 1;
}
