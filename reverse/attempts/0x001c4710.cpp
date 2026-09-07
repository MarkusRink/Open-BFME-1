// ?rva001C4710Check@Rva001C4710Owner@@QAE_NXZ
// partial score=0.5 date=2026-09-06
// ?rva001C4710Check@Rva001C4710Owner@@QAE_NXZ
// Address-derived: if bit 6 of this->m_28c is set, return true immediately.
// Otherwise fetch a value from the already-named thunk 0x00029DC0, use it to
// get a list from TheControlBar via the already-named thunk 0x00048CCA, then
// walk up to 20 items via the already-named thunk 0x00003F80 (an iterator
// "next" method), returning true the first time an item's byte at +0x18 has
// bit 0x10 set, and false if the list is empty, an item is null, or 20 items
// pass without a match.
class Rva001C4710Bar;
class Rva001C4710List;
class Rva001C4710Item;

extern void j_00029dc0();
extern void j_00048cca();
extern void j_00003f80();

extern Rva001C4710Bar *TheControlBar;

class Rva001C4710List
{
public:
	Rva001C4710Item *next();
};

class Rva001C4710Bar
{
public:
	Rva001C4710List *getList(int which);
};

class Rva001C4710Owner
{
public:
	unsigned char m_pad0[0x28c];
	unsigned int m_28c;

	bool rva001C4710Check();
};

bool Rva001C4710Owner::rva001C4710Check()
{
	unsigned int flags = m_28c;
	unsigned int shifted = flags >> 6;
	if (shifted & 1)
		return true;

	typedef int (*Fn0)();
	Fn0 fn0 = (Fn0)j_00029dc0;
	int val = fn0();

	typedef Rva001C4710List *(Rva001C4710Bar::*Fn1)(int);
	union { void (*raw)(); Fn1 member; } u1;
	u1.raw = j_00048cca;
	Rva001C4710List *list = (TheControlBar->*u1.member)(val);
	if (!list)
		return false;

	typedef Rva001C4710Item *(Rva001C4710List::*Fn2)();
	union { void (*raw)(); Fn2 member; } u2;
	u2.raw = j_00003f80;

	for (int i = 0; i < 20; ++i)
	{
		Rva001C4710Item *item = (list->*u2.member)();
		if (!item)
			return false;
		if (*((unsigned char *)item + 0x18) & 0x10)
			return true;
	}
	return false;
}
