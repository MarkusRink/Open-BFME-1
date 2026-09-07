// ??0BfmeOwnerYK@@QAE@XZ (identity unknown)
// partial score=0.95 date=2026-09-07
// 84/84, identical instruction set, THREE transposed instructions:
//   retail  xor edx,edx / lea ecx,[esi+4] / mov [esi],<vftable>
//   MSVC    mov [esi],<vftable> / xor edx,edx / lea ecx,[esi+4]
// The memory-operation order is identical (vftable, EH state, string); only the
// two register setups sit on the other side of the immediate store. /G7 does
// not move it, nor does putting the vfptr in the base initialiser list.
//
// Everything else is SOLVED and is the reusable part for the other 14 members
// of this family (SEH prologue + a call to releaseBuffer at 0x00887940):
//   * TWO EH states (`mov [esp+0x10],edx` = 0 then `mov byte [esp+0x10],al` = 1)
//     mean TWO destructible sub-objects. Here: a BASE holding the vfptr with a
//     declared destructor (state 0, its ctor inlined to the vftable store) and a
//     string member at +4 with a destructor (state 1). Modelling both as plain
//     members of one class gives only one state and comes out 5 bytes short.
//   * the state store lands at each sub-object boundary, so the state count and
//     order read straight off the destructible-member list.
//   * `mov [esp+4],esi` is the unwind record's object pointer; it is emitted
//     automatically, no source handle.
//   * `mov eax,1` is shared between the state byte and the m_a=1 store.
extern "C" void *bfmeVftYK[];

class BfmeStringYK
{
public:
	BfmeStringYK()
	{
		m_bfmeDataYK = 0;
	}

	~BfmeStringYK()
	{
		bfmeClearYK();
	}

	void bfmeClearYK();

	void *m_bfmeDataYK;
};

class BfmeBaseYK
{
public:
	BfmeBaseYK()
		: m_bfmeVfptrYK(bfmeVftYK)
	{
	}

	~BfmeBaseYK();

	void *m_bfmeVfptrYK;
};

class BfmeOwnerYK : public BfmeBaseYK
{
public:
	BfmeOwnerYK();

	BfmeStringYK m_bfmeStrYK;
	int m_bfmeAYK;
	int m_bfmeBYK;
};

BfmeOwnerYK::BfmeOwnerYK()
{
	m_bfmeAYK = 1;
	m_bfmeBYK = 0;
	m_bfmeStrYK.bfmeClearYK();
}
