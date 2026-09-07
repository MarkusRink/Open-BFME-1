// ?bfmeSwapESO@BfmeHostESO@@QAEXPAV1@@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 108/108 EXACT SIZE, only esi/edi swapped: retail keeps other in edi and
// this in esi, MSVC the other way round. Every instruction otherwise matches.
// Ruled out: declaring tb before ob (107 bytes and MSVC stops inlining a
// callee, giving an unresolved REL32).
//
// Three modelling points that were needed and transfer:
//  * a member function taking a pointer to its OWN class mangles the argument
//    with the enclosing-class back-reference: ...@QAEXPAV1@@Z, not the class
//    name spelled out. Getting this wrong reads as "symbol not found in
//    object" from explain_mismatch even though the file compiled fine --
//    dump the obj with strings to recover the real name.
//  * test/lea/jmp/xor around other+4 is an IMPLICIT upcast to a base at
//    offset 4 (null-checked); the same offset applied to this has NO check,
//    so that one must be spelled as explicit arithmetic
//    (BfmeBaseESO *)((char *)this + 4). Modelling both as upcasts adds a
//    redundant test esi,esi.
//  * the second other+4 (for the adjust call) also has no null check, so it
//    is explicit arithmetic too, not a second upcast.
// Pins are already in symbols.csv.
class BfmeFirstESO
{
public:
	unsigned char m_bfmeHeadESO[4];
};

class BfmeBaseESO
{
public:
	int m_bfmeAESO;
	int m_bfmeBESO;
};

class BfmeSubAESO
{
public:
	void bfmeSwapESO(BfmeSubAESO &other);

	unsigned char m_bfmeBodyESO[0x20];
};

class BfmeSubBESO
{
public:
	void bfmeSwapESO(BfmeSubBESO &other);

	unsigned char m_bfmeBodyESO[4];
};

class BfmeHostESO;

void __stdcall bfmeAdjustESO(BfmeHostESO *other, BfmeBaseESO *ob, BfmeBaseESO *tb);

class BfmeHostESO : public BfmeFirstESO, public BfmeBaseESO
{
public:
	void bfmeSwapESO(BfmeHostESO *other);
	void bfmeFixupESO();
	void bfmeFinishESO(BfmeHostESO *other, int *a, int *b);

	BfmeSubAESO m_bfmeSubAESO;
	BfmeSubBESO m_bfmeSubBESO;
};

void BfmeHostESO::bfmeSwapESO(BfmeHostESO *other)
{
	BfmeBaseESO *ob = other;
	BfmeBaseESO *tb = (BfmeBaseESO *)((char *)this + 4);

	int a = ob->m_bfmeAESO;
	int b = tb->m_bfmeAESO;

	tb->m_bfmeAESO = a;
	ob->m_bfmeAESO = b;

	int c = ob->m_bfmeBESO;
	int d = tb->m_bfmeBESO;

	tb->m_bfmeBESO = c;
	ob->m_bfmeBESO = d;

	m_bfmeSubAESO.bfmeSwapESO(other->m_bfmeSubAESO);
	m_bfmeSubBESO.bfmeSwapESO(other->m_bfmeSubBESO);

	bfmeFixupESO();

	bfmeAdjustESO(other, (BfmeBaseESO *)((char *)other + 4), tb);

	bfmeFinishESO(other, &other->m_bfmeBESO, &m_bfmeBESO);
}
