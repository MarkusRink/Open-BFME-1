// ?bfmeFindMR@BfmeOwnerMR@@QAEPAXPAVBfmeKeyMR@@@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 82/82 bytes, 4 instructions out of 27 differ and ALL of them are the position
// of one store. Everything else -- the guard chain, the two calls, the pair of
// lea'd out-parameters, the end-iterator compare and the shared epilogue --
// matches byte for byte.
// Two things had to be right to get here: the `found == end` case needs an
// EXPLICIT `return value;` before the assignment (without it MSVC forwards the
// last assignment into eax and duplicates the epilogue, +6 bytes), and the
// resolve result must be written back into the parameter (a separate local
// takes a slot of its own, 94 bytes).
// Residue: retail SINKS `mov [esp+0x10],eax` past `mov esi,[esi+0xc]` and
// `test esi,esi` so both paths execute it; MSVC keeps it inside the taken arm
// right after the call. Tried: ternary spelling, a named `inner` local, nested
// ifs instead of the && chain, /G7 (much worse), /Oy, /Ot. Store-placement
// residue.
class BfmeKeyMR;

class BfmeInnerMR
{
public:
	BfmeKeyMR *bfmeResolveMR(void);
};

class BfmeKeyMR
{
public:
	int m_bfmeSpareMR;
	BfmeInnerMR *m_bfmeInnerMR;
};

class BfmeNodeMR
{
public:
	unsigned char m_bfmeHeadMR[0x14];
	void *m_bfmeValueMR;
};

class BfmeTableMR
{
public:
	void bfmeLookupMR(BfmeNodeMR **found, BfmeKeyMR **key);

	BfmeNodeMR *m_bfmeEndMR;
	int m_bfmeReadyMR;
};

class BfmeOwnerMR
{
public:
	void *bfmeFindMR(BfmeKeyMR *key);

	unsigned char m_bfmeHeadMR[8];
	void *m_bfmeDefaultMR;
	BfmeTableMR *m_bfmeTableMR;
};

void *BfmeOwnerMR::bfmeFindMR(BfmeKeyMR *key)
{
	void *value = m_bfmeDefaultMR;

	if (key)
	{
		if (key->m_bfmeInnerMR)
			key = key->m_bfmeInnerMR->bfmeResolveMR();

		BfmeTableMR *table = m_bfmeTableMR;

		if (table && table->m_bfmeReadyMR)
		{
			BfmeNodeMR *found;

			table->bfmeLookupMR(&found, &key);

			if (found == table->m_bfmeEndMR)
				return value;

			value = found->m_bfmeValueMR;
		}
	}

	return value;
}
