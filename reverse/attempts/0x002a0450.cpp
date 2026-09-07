// ?bfmeTickYO@BfmeOwnerYO@@QAEHXZ (identity unknown)
// partial score=0.95 date=2026-09-07
// 93/96. Everything matches except the three-byte flag-update block. Solved and
// reusable: the whole body is a single guarded block that always `return 1;`
// (every early exit jumps to the shared `mov eax,1; ret`), the frame test is
// UNSIGNED (`jbe`), `mov ecx,[ecx-8]` is a raw read of a pointer stored 8 bytes
// before `this`, and the two `test ah,4` / `test ah,8` are bits 0x400 / 0x800 of
// the int at +0x118 -- the guard is `(flags & 0x400) || !(flags & 0x800)`.
// The member must be `volatile int`, otherwise MSVC dead-store-eliminates the
// first of the two writes ([[volatile-preserves-dead-stores]]).
// Residue:
//   retail  mov edx,[+0x118] / and edx,imm32 (6-byte form) / mov eax,edx /
//           or eax,0x800 / mov [+0x118],edx / mov [+0x118],eax
//   MSVC    mov eax,[+0x118] / and eax,imm32 (5-byte eax form) / store /
//           or eax,0x800 / store
// i.e. retail computes both values before either store and pays for it with the
// `mov eax,edx` copy and the longer edx-form `and`. Naming both values in
// locals, and writing them as one common subexpression, both still let MSVC
// store eagerly.
class BfmeThingYO
{
public:
	void bfmeNotifyYO();

	unsigned char m_bfmeHeadYO[0x118];
	volatile int m_bfmeFlagsYO;
};

class BfmeLogicYO
{
public:
	unsigned char m_bfmeHeadYO[0x3c];
	unsigned int m_bfmeFrameYO;
};

extern BfmeLogicYO *TheBfmeLogicYO;

class BfmeOwnerYO
{
public:
	int bfmeTickYO();

	unsigned char m_bfmeHeadYO[0x10];
	unsigned int m_bfmeCountYO;
	char m_bfmeDoneYO;
};

int BfmeOwnerYO::bfmeTickYO()
{
	if (m_bfmeCountYO != 0 && m_bfmeDoneYO != 1 &&
	    TheBfmeLogicYO->m_bfmeFrameYO > m_bfmeCountYO)
	{
		m_bfmeDoneYO = 1;
		m_bfmeCountYO = 0;

		BfmeThingYO *thing = *(BfmeThingYO **)((char *)this - 8);
		int flags = thing->m_bfmeFlagsYO;

		if ((flags & 0x400) != 0 || (flags & 0x800) == 0)
		{
			int cleared = thing->m_bfmeFlagsYO & ~0x400;
			int raised = cleared | 0x800;

			thing->m_bfmeFlagsYO = cleared;
			thing->m_bfmeFlagsYO = raised;
			thing->bfmeNotifyYO();
		}
	}

	return 1;
}
