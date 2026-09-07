// ?bfmeResolveCI@BfmeHostCI@@QAEXPAVBfmeKeyCI@@@Z (identity unknown)
// partial score=0.94 date=2026-09-07
// 63/65. Guards, the sub-object find call, the arm polarity and both epilogues
// match. Retail's two arms each carry their own load+store of the value, and
// the t != 0 arm opens with a redundant `mov eax,esi` so both arms use eax --
// the signature of MSVC DUPLICATING a shared tail ([[msvc-duplicates-shared-tail]]).
// Writing that shared form (`if (t == 0) t = bfmeDefault(); m_value = t->data;`)
// makes THIS MSVC merge instead of duplicate: 49 bytes, one load and one store.
// Writing the two arms out explicitly (below) reproduces the duplication but
// then each arm loads straight through its own register, so the 2-byte
// `mov eax,esi` never appears. Both halves are reachable, not together.
// Arm polarity IS controllable: `if (t == 0) <default> else <found>` puts the
// found arm last as retail has it; the other way round costs the same 2 bytes
// plus a wrong branch target.
class BfmeThingCI
{
public:
	unsigned char m_bfmeHeadCI[0xac];
	int m_bfmeDataCI;
};

class BfmeKeyCI
{
public:
	int m_bfmeIdCI;
};

class BfmeMapCI
{
public:
	void bfmeFindCI(BfmeKeyCI *key);

	BfmeThingCI *m_bfmeFoundCI;
	unsigned char m_bfmePadCI[8];
};

extern "C" BfmeThingCI *__cdecl bfmeDefaultCI(void);

class BfmeHostCI
{
public:
	void bfmeResolveCI(BfmeKeyCI *key);

	unsigned char m_bfmeHeadCI[0x14];
	BfmeMapCI m_bfmeMapCI;
	int m_bfmeValueCI;
};

void BfmeHostCI::bfmeResolveCI(BfmeKeyCI *key)
{
	if (key->m_bfmeIdCI == 0)
		return;

	m_bfmeMapCI.bfmeFindCI(key);

	BfmeThingCI *t = m_bfmeMapCI.m_bfmeFoundCI;

	if (t == 0)
		m_bfmeValueCI = bfmeDefaultCI()->m_bfmeDataCI;
	else
		m_bfmeValueCI = t->m_bfmeDataCI;
}
