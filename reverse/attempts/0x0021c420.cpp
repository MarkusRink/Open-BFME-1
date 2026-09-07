// ?bfmeAddESB@BfmeHostESB@@QAEXPAVBfmeThingESB@@@Z (identity unknown)
// partial score=0.98 date=2026-09-07
// 104/104 EXACT SIZE, ONE misplaced instruction:
//   retail  mov [ecx],eax / mov [esi+4],eax / pop edi / pop esi / pop ebx
//   MSVC    pop edi / mov [ecx],eax / mov [esi+4],eax / pop esi / pop ebx
// edi holds the argument and dies at the placement-new store, so MSVC
// shrink-wraps its pop one slot earlier. Pure scheduling; the store order and
// every other byte match.
// Ruled out: computing prev before the placement new (moves the head->prev
// load above the lea and costs three more diffs).
//
// Model notes worth reusing: the body is an STLport list push_back --
// _STL::__new_alloc::allocate(12) then placement new of the pointer into
// node+8 (that is what the lea ecx,[eax+8] / test ecx,ecx / je gives), then
// next/prev/prev->next/head->prev in that order. Declaring the real
// ?allocate@__new_alloc@_STL@@SAPAXI@Z via namespace _STL { struct
// __new_alloc { static void *allocate(unsigned int); }; } needs no pin -- it
// is already a matched definition.
// Pins are already in symbols.csv.
inline void *__cdecl operator new(unsigned int size, void *place) { return place; }

namespace _STL
{
	struct __new_alloc
	{
		static void *allocate(unsigned int size);
	};
}

class BfmeThingESB
{
public:
	int bfmeIdESB();
};

typedef BfmeThingESB *BfmeThingPtrESB;

struct BfmeNodeESB
{
	BfmeNodeESB *m_bfmeNextESB;
	BfmeNodeESB *m_bfmePrevESB;
	BfmeThingESB *m_bfmeValueESB;
};

class BfmeHostESB
{
public:
	virtual void bfmeSlot00ESB();
	virtual void bfmeSlot01ESB();
	virtual void bfmeSlot02ESB();
	virtual void bfmeSlot03ESB();
	virtual void bfmeSlot04ESB();
	virtual void bfmeSlot05ESB();
	virtual void bfmeSlot06ESB();
	virtual void bfmeSlot07ESB();
	virtual void bfmeSlot08ESB();
	virtual void bfmeSlot09ESB();
	virtual void bfmeSlot10ESB();
	virtual void bfmeSlot11ESB();
	virtual void bfmeSlot12ESB();
	virtual void bfmeSlot13ESB();
	virtual void bfmeSlot14ESB();
	virtual void bfmeSlot15ESB();
	virtual void bfmeSlot16ESB();
	virtual void bfmeSlot17ESB();
	virtual void bfmeSlot18ESB();
	virtual void bfmeSlot19ESB();
	virtual void bfmeSlot20ESB();
	virtual void bfmeSlot21ESB();
	virtual void bfmeSlot22ESB();
	virtual void bfmeSlot23ESB();
	virtual void bfmeSlot24ESB();
	virtual void bfmeSlot25ESB();
	virtual void bfmeSlot26ESB();
	virtual void bfmeSlot27ESB();
	virtual void bfmeSlot28ESB();
	virtual void bfmeSlot29ESB();
	virtual void bfmeSlot30ESB();
	virtual void bfmeSlot31ESB();
	virtual void bfmeSlot32ESB();
	virtual void bfmeSlot33ESB();
	virtual void bfmeSlot34ESB();
	virtual void bfmeSlot35ESB();
	virtual void bfmeSlot36ESB();
	virtual void bfmeSlot37ESB();
	virtual void bfmeSlot38ESB();
	virtual void bfmeSlot39ESB();
	virtual void bfmeSlot40ESB();
	virtual void bfmeSlot41ESB();
	virtual void bfmeSlot42ESB();
	virtual void bfmeSlot43ESB();
	virtual void bfmeSlot44ESB();
	virtual void bfmeSlot45ESB();
	virtual void bfmeSlot46ESB();
	virtual void bfmeSlot47ESB();
	virtual void bfmeSlot48ESB();
	virtual void bfmeSlot49ESB();
	virtual void bfmeSlot50ESB();
	virtual void bfmeSlot51ESB();
	virtual void bfmeSlot52ESB();
	virtual void bfmeSlot53ESB();
	virtual void bfmeSlot54ESB();
	virtual void bfmeSlot55ESB();
	virtual void bfmeSlot56ESB();
	virtual void bfmeSlot57ESB();
	virtual void bfmeSlot58ESB();
	virtual void bfmeSlot59ESB();
	virtual void bfmeSlot60ESB();
	virtual void bfmeSlot61ESB();
	virtual void bfmeSlot62ESB();
	virtual void bfmeSlot63ESB();
	virtual int bfmeSlot64ESB(int mode);

	void bfmeAddESB(BfmeThingESB *thing);
	void bfmeOtherESB(BfmeThingESB *thing);

	unsigned char m_bfmeHeadESB[0x998];
	BfmeNodeESB *m_bfmeListESB;
};

void BfmeHostESB::bfmeAddESB(BfmeThingESB *thing)
{
	if (thing->bfmeIdESB() != (*(BfmeThingESB **)((char *)this - 0x18))->bfmeIdESB() &&
		bfmeSlot64ESB(0))
	{
		BfmeNodeESB *head = m_bfmeListESB;
		BfmeNodeESB *node = (BfmeNodeESB *)_STL::__new_alloc::allocate(12);

		new (&node->m_bfmeValueESB) BfmeThingPtrESB(thing);

		BfmeNodeESB *prev = head->m_bfmePrevESB;

		node->m_bfmeNextESB = head;
		node->m_bfmePrevESB = prev;
		prev->m_bfmeNextESB = node;
		head->m_bfmePrevESB = node;

		return;
	}

	bfmeOtherESB(thing);
}
