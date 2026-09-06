// ??0BfmeOwnCB@@QAE@XZ (identity unknown)
// partial score=0.88 date=2026-09-06
// 74/84 at exact size. This is a CONSTRUCTOR, not a destructor: it returns
// this and its unwind states count UP (0 then 1) as sub-objects are built.
// Everything is modelled -- the pinned vftable, a 4-byte member at +4 whose
// ctor zeroes it, an 8-byte member at +8 whose ctor writes {1, 0}, and a body
// call to releaseBuffer on the member at +4.
// Residue: retail writes each unwind state BEFORE the member it protects and
// stores `this` into the frame slot first; MSVC writes the state AFTER the
// member is built and sinks the this-slot store past the vftable store. Tried
// an explicit member-init list on the owner, init lists inside both members,
// and throw() on both member ctors -- identical ten-line permutation each time.
class BfmeStrCB
{
public:
	BfmeStrCB(void) throw() { m_bfmeDataCB = 0; }
	~BfmeStrCB();

	void bfmeClearCB(void);

	int m_bfmeDataCB;
};

class BfmeFlagsCB
{
public:
	BfmeFlagsCB(void) throw()
	{
		m_bfmeACB = 1;
		m_bfmeBCB = 0;
	}
	~BfmeFlagsCB();

	int m_bfmeACB;
	int m_bfmeBCB;
};

class BfmeOwnCB
{
public:
	BfmeOwnCB(void);
	virtual void bfmePureCB(void) = 0;

	BfmeStrCB m_bfmeStrCB;
	BfmeFlagsCB m_bfmeFlagsCB;
};

BfmeOwnCB::BfmeOwnCB(void)
{
	m_bfmeStrCB.bfmeClearCB();
}
