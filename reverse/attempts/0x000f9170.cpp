// ?bfmeAllowQD@BfmeOwnerQD@@QAEDPAVBfmeHolderQD@@D@Z (identity unknown)
// partial score=0.94 date=2026-09-07
// 83/88 bytes. Guards, the resolve, the 0x1000 flag test and the block order
// all match (the `strict` test must be written POSITIVELY -- `if (strict)
// { ...compare... } return 1;` -- so `return 1` is the branch target).
// Residue is the final comparison, 5 bytes:
//   retail  mov eax,[TheWritableGlobalData]; mov eax,[eax+0b60h];
//           mov ecx,[esi+10h]; xor edx,edx; cmp ecx,eax; setl dl; mov al,dl
//   ours    mov eax,[esi+10h]; mov ecx,[global]; cmp eax,[ecx+0b60h]; setl al
// MSVC folds the limit load into the cmp and sets al directly. Hoisting the
// limit into an int local, hoisting BOTH operands into int locals, and casting
// the int result to char at the return all leave the fold in place.
class BfmeThingQD;

class BfmeInnerQD
{
public:
	BfmeThingQD *bfmeResolveQD(void);
};

class BfmeThingQD
{
public:
	int m_bfmeSpareQD;
	BfmeInnerQD *m_bfmeInnerQD;
	unsigned char m_bfmeGapQD[0xc0];
	int m_bfmeFlagsQD;
};

class BfmeHolderQD
{
public:
	int m_bfmeSpareQD;
	BfmeThingQD *m_bfmeThingQD;
};

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadQD[0xb60];
	int m_bfmeLimitQD;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class BfmeOwnerQD
{
public:
	char bfmeAllowQD(BfmeHolderQD *holder, char strict);

	unsigned char m_bfmeHeadQD[0x10];
	int m_bfmeCountQD;
};

char BfmeOwnerQD::bfmeAllowQD(BfmeHolderQD *holder, char strict)
{
	if (holder)
	{
		BfmeThingQD *thing = holder->m_bfmeThingQD;

		if (thing && thing->m_bfmeInnerQD)
			thing = thing->m_bfmeInnerQD->bfmeResolveQD();

		if ((thing->m_bfmeFlagsQD & 0x1000) == 0)
		{
			if (strict)
			{
				int limit = TheWritableGlobalData->m_bfmeLimitQD;
				int allowed = m_bfmeCountQD < limit;

				return (char)allowed;
			}

			return 1;
		}
	}

	return 0;
}
