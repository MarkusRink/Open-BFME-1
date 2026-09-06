// ?bfmeRunFH@BfmeOwnerFH@@QAEXPAVBfmeCheckFH@@@Z (identity unknown)
// partial score=0.94 date=2026-09-07
// 70/70 bytes; every instruction matches except the argument/vftable register
// pair in the virtual-call block: retail mov ecx,[esi+0x10] / mov eax,[ebx] /
// push ecx / call [eax+0x20]; MSVC gives eax/edx/push eax/call [edx+0x20].
// Shape is settled: the advance must be DUPLICATED into both arms (a single
// `next` at the top of the loop body leaves the load above the compare and
// costs 5 bytes). Naming the argument in a local, /G7, /Oy and /Os all leave
// the register pair unchanged; a __thiscall function-pointer vftable is
// rejected by VC7.1 (C4234). Argument-shuttle register class.
class BfmeNodeFH
{
public:
	int m_bfmeSelfFH;
	int m_bfmeKindFH;
	void *m_bfmeKeyFH;
	int m_bfmeSpareFH;
	void *m_bfmeValueFH;
	unsigned char m_bfmeGapFH[0x28];
	BfmeNodeFH *m_bfmeNextFH;
};

class BfmeCheckFH
{
public:
	char bfmeCheckFH(void *key);
};

class BfmeOwnerFH
{
public:
	virtual void bfmeV0FH(void);
	virtual void bfmeV1FH(void);
	virtual void bfmeV2FH(void);
	virtual void bfmeV3FH(void);
	virtual void bfmeV4FH(void);
	virtual void bfmeV5FH(void);
	virtual void bfmeV6FH(void);
	virtual void bfmeV7FH(void);
	virtual void bfmeApplyFH(void *value);

	void bfmeRunFH(BfmeCheckFH *other);

	int m_bfmeSpareFH;
	BfmeNodeFH *m_bfmeListFH;
};

void BfmeOwnerFH::bfmeRunFH(BfmeCheckFH *other)
{
	BfmeNodeFH *node = m_bfmeListFH;

	while (node)
	{
		if (node->m_bfmeKindFH == 1 && other->bfmeCheckFH(node->m_bfmeKeyFH))
		{
			BfmeNodeFH *next = node->m_bfmeNextFH;

			bfmeApplyFH(node->m_bfmeValueFH);
			node = next;
		}
		else
			node = node->m_bfmeNextFH;
	}
}
