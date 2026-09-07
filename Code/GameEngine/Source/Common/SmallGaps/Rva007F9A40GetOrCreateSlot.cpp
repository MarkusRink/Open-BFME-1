// ?rva007F9A40GetOrCreateSlot@BfmeMgrVPE@@QAEPAUBfmeSlotVPE@@PBURva007F9A40Key@@HH@Z
// Address-derived: find-or-allocate a BfmeSlotVPE (class/struct reused from
// Code/GameEngine/Source/Common/BfmeConv1559.cpp), then fill it from a
// 12-byte source key struct plus two extra int fields.
#pragma intrinsic(strcmp)
extern "C" int strcmp(const char *, const char *);

struct Rva007F9A40Key
{
	const char *a;
	const char *b;
	int c;

	bool matches(const Rva007F9A40Key *other) const;
};

struct BfmeSlotVPE
{
	char m_bfme00;
	char m_pad1[3];
	Rva007F9A40Key m_key;
	int m_10;
	int m_14;
};

class BfmeMgrVPE
{
public:
	BfmeSlotVPE* bfmeAllocSlotVPE();
	char m_bfmePad000[0x10];
	int m_bfme10;
	char m_bfmePad014[0x394];
	BfmeSlotVPE m_bfme3a8[0x20];

	BfmeSlotVPE* rva007F9A40GetOrCreateSlot(const Rva007F9A40Key* key, int a4, int a5);
};

bool Rva007F9A40Key::matches(const Rva007F9A40Key *other) const
{
	if (strcmp(a, other->a) != 0)
		return false;
	if (c != 0)
		return c == other->c;
	return strcmp(b, other->b) == 0;
}

extern void d_007f9530();

BfmeSlotVPE* BfmeMgrVPE::rva007F9A40GetOrCreateSlot(const Rva007F9A40Key* key, int a4, int a5)
{
	typedef BfmeSlotVPE* (BfmeMgrVPE::*FindFn)(const Rva007F9A40Key*);
	union { void (*raw)(); FindFn member; } fn;
	fn.raw = d_007f9530;

	BfmeSlotVPE* slot = (this->*fn.member)(key);
	if (!slot)
		slot = bfmeAllocSlotVPE();

	slot->m_key = *key;
	slot->m_10 = a4;
	slot->m_14 = a5;
	return slot;
}
