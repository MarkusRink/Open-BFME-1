// ?bfmeGetYC@BfmeOwnerYC@@QAE?AVBfmeRoomYC@@XZ (identity unknown)
// partial score=0.9 date=2026-09-07
// 88/88, exact size, every instruction structurally present. Everything that
// was hard is SOLVED here and worth reusing:
//   * sret return of a class by value: `ret 4` with `mov eax,esi` in both tails.
//   * the `push ecx` slot plus `mov dword ptr [esp+4],0` construction flag
//     appears ONLY when the returned class declares a DESTRUCTOR. Without
//     `~BfmeRoomYC();` the body is 13 bytes short; with it there is still no
//     SEH frame. See [[string-returned-by-value]].
//   * `volatile` on m_bfmeEndYC is required: `end - begin` is evaluated
//     right-to-left, so without it MSVC loads begin first and retail loads end
//     into edx then begin into esi.
//   * guards must be NESTED (index >= 0 outer, bounds inner) so the two member
//     loads land between the two tests rather than above the first.
//   * the bounds test is `index < (unsigned)(end - begin)` -- signed jl on the
//     first test, unsigned jae on the second.
// Residue is one systematic register permutation ([[argument-shuttle-register]]):
//   retail  this->eax (mov eax,ecx), index->ecx, begin->esi, then esi RELOADED
//           with the sret pointer from [esp+0xc] after the call
//   MSVC    this stays in ecx, index->edx, begin->esi, sret pointer hoisted
//           into edi with an extra push edi/pop edi inside the block
// Naming the index in a local does not move it. The sret pointer has no source
// spelling, so the late reload cannot be requested.
class BfmeRoomYC
{
public:
	BfmeRoomYC(const BfmeRoomYC &other);
	~BfmeRoomYC();

	unsigned char m_bfmeBytesYC[0x20];
};

class BfmeSubYC
{
public:
	BfmeRoomYC bfmeRoomYC();
};

class BfmeElemYC
{
public:
	BfmeSubYC *bfmeSubYC();

	unsigned char m_bfmePadYC[0x20];
};

extern BfmeRoomYC g_bfmeDefaultYC;

class BfmeOwnerYC
{
public:
	BfmeRoomYC bfmeGetYC();

	unsigned char m_bfmeHeadYC[0xc];
	int m_bfmeIndexYC;
	BfmeElemYC *m_bfmeBeginYC;
	BfmeElemYC *volatile m_bfmeEndYC;
};

BfmeRoomYC BfmeOwnerYC::bfmeGetYC()
{
	int index = m_bfmeIndexYC;

	if (index >= 0)
	{
		BfmeElemYC *end = m_bfmeEndYC;
		BfmeElemYC *begin = m_bfmeBeginYC;

		if (index < (unsigned int)(end - begin))
			return begin[index].bfmeSubYC()->bfmeRoomYC();
	}

	return g_bfmeDefaultYC;
}
