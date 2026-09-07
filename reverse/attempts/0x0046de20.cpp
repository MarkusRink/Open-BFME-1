// ?bfmeSetERS@BfmeHostERS@@QAEXPAXVBfmePtrERS@@@Z (identity unknown)
// partial score=0.96 date=2026-09-07
// 163/163 EXACT SIZE. First banked SOURCE MODEL for this body (the earlier
// 38-minute attempt reported the same length but left no stash).
// Shape: a by-value ref-counted smart pointer parameter that the callee
// destroys, a hash lookup at this+0x30, a conditional slot assignment with
// addRef/release, then the parameter destructor. MSVC merges the guard
// "if (value.m_p == 0) return;" with the destructor null test, which is why
// one test esi,esi at the top covers both.
// The sentinel compared against the locate() result is &value.m_bfmePtrERS --
// the by-value parameter's own storage at [esp+0x20]. An uninitialised local
// instead lands in the arg1 home slot at [esp+0x1c] and is wrong.
//
// Three residual instructions, all register/scheduling:
//  1. lea ecx,[esp+0x20] vs lea eax,[esp+0x20] -- naming the address in a
//     local before or after the call does not move it; flipping the compare
//     operands flips the encoding to 3b c7 as expected but keeps eax.
//  2/3. inside the inlined destructor retail emits
//       dec ecx / mov [esi+4],ecx / mov eax,ecx / test / state=-1 / jg
//     and MSVC
//       dec ecx / mov eax,ecx / test / state=-1 / mov [esi+4],ecx / jg
//     plus mov ecx,esi / push 1 the other way round at the virtual call.
// Ruled out for the destructor: naming the receiver in a local; splitting to
// "int n = p->ref - 1; p->ref = n;" (loses the mov eax,ecx entirely, 161
// bytes); "int n = --p->ref;" (identical to the && form).
// NOTE the SAME construct a few instructions earlier -- the release of the
// OLD slot value -- already matches retail byte for byte with the plain
// && form, storing AFTER the test. So retail schedules the two expansions
// differently and only one of them can be spelled at a time.
// Pins are already in symbols.csv.
class BfmeValueERS
{
public:
	virtual void bfmeReleaseERS(int flag);

	int m_bfmeRefERS;
};

class BfmePtrERS
{
public:
	BfmePtrERS(const BfmePtrERS &other);

	~BfmePtrERS()
	{
		BfmeValueERS *p = m_bfmePtrERS;

		if (p != 0 && --p->m_bfmeRefERS <= 0)
			p->bfmeReleaseERS(1);
	}

	BfmeValueERS *m_bfmePtrERS;
};

struct BfmeEntryERS
{
	unsigned char m_bfmeHeadERS[8];
	BfmeValueERS *m_bfmeValueERS;
};

class BfmeHashERS
{
public:
	BfmeEntryERS *bfmeFindERS(void *key);
	BfmeValueERS **bfmeLocateERS(void *key);
};

class BfmeHostERS
{
public:
	void bfmeSetERS(void *key, BfmePtrERS value);

	unsigned char m_bfmeHeadERS[0x30];
	BfmeHashERS m_bfmeHashERS;
};

void BfmeHostERS::bfmeSetERS(void *key, BfmePtrERS value)
{
	if (value.m_bfmePtrERS == 0)
		return;

	BfmeEntryERS *found = m_bfmeHashERS.bfmeFindERS(key);

	if (found == 0 || found->m_bfmeValueERS == 0)
	{
		BfmeValueERS **slot = m_bfmeHashERS.bfmeLocateERS(key);
		BfmeValueERS **self = &value.m_bfmePtrERS;

		if (slot != self)
		{
			++value.m_bfmePtrERS->m_bfmeRefERS;

			BfmeValueERS *old = *slot;

			if (old != 0 && --old->m_bfmeRefERS <= 0)
				old->bfmeReleaseERS(1);

			*slot = value.m_bfmePtrERS;
		}
	}
}
