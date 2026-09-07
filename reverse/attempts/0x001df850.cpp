// ?bfmeSendQK@BfmeOwnerQK@@QAEXXZ (identity unknown)
// partial score=0.95 date=2026-09-07
// 58/58 bytes; 12 of 22 instructions differ, from two allocation/order choices:
//   1. retail saves BOTH esi and edi before the switch; MSVC saves edi there
//      and shrink-wraps esi into the tail, so every later displacement shifts.
//   2. at the call retail does `mov ecx,edi` BEFORE `push esi`; MSVC pushes
//      first and sets the receiver last.
// Settled: the two-case subtract chain (`sub eax,0` / `je` / `dec` / `jne`)
// comes straight from a `switch` with a `default: return;`, the sink null test
// follows the switch, and the second call takes (item, make(item)) with the
// make being a __stdcall taking the same item.
// Tried: declaring both locals before the switch, and hoisting the make result
// into its own local -- both make it worse (14 differing lines).
void * __stdcall bfmeMakeQK(void *item);

class BfmeSinkQK
{
public:
	void bfmeDoQK(void *item, void *made);
};

class BfmeOwnerQK
{
public:
	void bfmeSendQK(void);

	unsigned char m_bfmeHeadQK[0xf8];
	BfmeSinkQK *m_bfmeAQK;
	BfmeSinkQK *m_bfmeBQK;
	int m_bfmeSpareQK;
	int m_bfmeModeQK;
	void *m_bfmeItemQK;
};

void BfmeOwnerQK::bfmeSendQK(void)
{
	BfmeSinkQK *sink;

	switch (m_bfmeModeQK)
	{
	case 0:
		sink = m_bfmeAQK;
		break;

	case 1:
		sink = m_bfmeBQK;
		break;

	default:
		return;
	}

	if (sink == 0)
		return;

	void *item = m_bfmeItemQK;

	sink->bfmeDoQK(item, bfmeMakeQK(item));
}
