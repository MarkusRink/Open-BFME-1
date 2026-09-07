// ?bfmeSetMK@BfmeSliderMK@@QAEXH@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 59/61 bytes. Frame, guard, the span computation into the pushed-ecx local,
// __ftol2, the `+ low` and the virtual call through slot 1 all match.
// Residue: retail loads BOTH ints and then multiplies --
//   fild [span]; fild [value]; fmul [k]; fmulp st(1)
// -- while MSVC folds one into an integer multiply:
//   fld [k]; fimul [value]; ... fimul [span]
// Explicit `(float)` casts on both operands change nothing (they fold away).
// /Op does produce `fild` for the value but pays for it with precision-
// rounding stores (fstp/fmul through memory), 75 bytes. /G7 is 80, /Ot no
// change. fimul-selection residue.
extern volatile float g_01076C24;

class BfmeTargetMK
{
public:
	virtual void bfmeV0MK(void);
	virtual void bfmeApplyMK(int value);
};

class BfmeSliderMK
{
public:
	void bfmeSetMK(int value);

	int m_bfmeSpareMK;
	BfmeTargetMK *m_bfmeTargetMK;
	int m_bfmeLowMK;
	int m_bfmeHighMK;
};

void BfmeSliderMK::bfmeSetMK(int value)
{
	BfmeTargetMK *target = m_bfmeTargetMK;

	if (target)
	{
		int low = m_bfmeLowMK;
		int span = m_bfmeHighMK - low;

		target->bfmeApplyMK(low + (int)((float)span * ((float)value * g_01076C24)));
	}
}
