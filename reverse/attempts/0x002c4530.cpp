// ?bfmeFetchYJ@BfmeOwnerYJ@@QAEXPAXPAUBfmeVec3YJ@@@Z (identity unknown)
// partial score=0.94 date=2026-09-07
// 78/78 bytes; 10 of 26 instructions differ.
// Settled: the secondary base at this-338h, a virtual (slot 26) returning the
// thing, two SEPARATE null guards with distinct exits (one before `push esi`,
// one after), a virtual (slot 7) taking (&temp, key, &scratch) and returning a
// pointer whose three dwords are copied to the out parameter.
// Residue: retail reserves SIXTEEN bytes (`sub esp,10h`) and puts the 4-byte
// scratch at esp-10h with the 12-byte temp at esp-0ch; MSVC reserves twelve
// (`sub esp,0ch`) and finds the scratch elsewhere, which shifts every later
// displacement. Also a lone eax/ecx swap in the opening chain (retail holds
// the unit in eax, we chain ecx->ecx).
// Tried: swapping the declaration order of the two locals (same 10 lines).
struct BfmeVec3YJ
{
	int m_bfmeXYJ;
	int m_bfmeYYJ;
	int m_bfmeZYJ;
};

class BfmeThingYJ
{
public:
	virtual void bfmeT0YJ(void);
	virtual void bfmeT1YJ(void);
	virtual void bfmeT2YJ(void);
	virtual void bfmeT3YJ(void);
	virtual void bfmeT4YJ(void);
	virtual void bfmeT5YJ(void);
	virtual void bfmeT6YJ(void);
	virtual BfmeVec3YJ *bfmeQueryYJ(BfmeVec3YJ *out, void *key, int *scratch);
};

class BfmeSourceYJ
{
public:
	virtual void bfmeS0YJ(void);
	virtual void bfmeS1YJ(void);
	virtual void bfmeS2YJ(void);
	virtual void bfmeS3YJ(void);
	virtual void bfmeS4YJ(void);
	virtual void bfmeS5YJ(void);
	virtual void bfmeS6YJ(void);
	virtual void bfmeS7YJ(void);
	virtual void bfmeS8YJ(void);
	virtual void bfmeS9YJ(void);
	virtual void bfmeS10YJ(void);
	virtual void bfmeS11YJ(void);
	virtual void bfmeS12YJ(void);
	virtual void bfmeS13YJ(void);
	virtual void bfmeS14YJ(void);
	virtual void bfmeS15YJ(void);
	virtual void bfmeS16YJ(void);
	virtual void bfmeS17YJ(void);
	virtual void bfmeS18YJ(void);
	virtual void bfmeS19YJ(void);
	virtual void bfmeS20YJ(void);
	virtual void bfmeS21YJ(void);
	virtual void bfmeS22YJ(void);
	virtual void bfmeS23YJ(void);
	virtual void bfmeS24YJ(void);
	virtual void bfmeS25YJ(void);
	virtual BfmeThingYJ *bfmeGetYJ(void);
};

class BfmeUnitYJ
{
public:
	unsigned char m_bfmeHeadYJ[0x1fc];
	BfmeSourceYJ *m_bfmeSourceYJ;
};

class BfmeOwnerYJ
{
public:
	void bfmeFetchYJ(void *key, BfmeVec3YJ *out);
};

void BfmeOwnerYJ::bfmeFetchYJ(void *key, BfmeVec3YJ *out)
{
	BfmeUnitYJ *unit = *(BfmeUnitYJ **)((char *)this - 0x338);
	BfmeThingYJ *thing = unit->m_bfmeSourceYJ->bfmeGetYJ();

	if (thing != 0)
	{
		if (out != 0)
		{
			int scratch;
			BfmeVec3YJ temp;

			*out = *thing->bfmeQueryYJ(&temp, key, &scratch);
		}
	}
}
