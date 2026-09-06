// ??1Rva0014C3B0@@UAE@XZ
// partial score=0.92 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: retail 0x0014C3B0 (162 B). ZH twin: W3DShadowTexture::~W3DShadowTexture
// (W3DProjectedShadow.cpp) which does REF_PTR_RELEASE(m_texture); retail adds a
// second field, a linked list at +0x14 walked and released node by node
// (each node's "next" pointer sits at +0xf8), plus an STLport list<int> at
// +0x10 (thunk 0x000491C0 -> tg_0014bb10, object-symbol
// ??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ), before a stamp field
// at +8 is reset to BfmeBaseVUQ (0x1073744) and the SubsystemInterface base
// destructor runs. The +8 field carries an entry vtable stamp (0x1095994)
// whose slot 2 is SubsystemInterface's loadIniFilesFromLegend override, but
// the base destructor call itself uses `this` unmodified, so the class's own
// base is SubsystemInterface directly at offset 0; the +8 field is
// address-derived and only ever written, never dereferenced by this body.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	int m_bfmeState;			// +4, matches the real SubsystemInterface layout
};

// address-derived: trivial second base, own vtable folds to BfmeBaseVUQ
class Rva0014C3B0Mid
{
public:
	virtual ~Rva0014C3B0Mid() {}
};

// address-derived: m_texture's static type places a second vtable at +4
class Rva0014C3B0TextureBase1
{
public:
	virtual ~Rva0014C3B0TextureBase1() {}
};

class Rva0014C3B0TextureIface
{
public:
	virtual void release( unsigned int );
};

class Rva0014C3B0Texture
	: public Rva0014C3B0TextureBase1, public Rva0014C3B0TextureIface
{
};

// address-derived: linked-list node, vtable at +0, next pointer at +0xf8
class Rva0014C3B0Node
{
public:
	virtual void release( unsigned int );

private:
	char m_pad[ 0xf8 - 4 ];

public:
	Rva0014C3B0Node *m_next;			// +0xf8
};

class Rva0014C3B0 : public SubsystemInterface, public Rva0014C3B0Mid
{
public:
	virtual ~Rva0014C3B0();

private:
	Rva0014C3B0Texture *m_texture;			// +0x0C
	_STL::list<int> m_intList;			// +0x10
	Rva0014C3B0Node *m_list;			// +0x14
};

// ??1Rva0014C3B0@@UAE@XZ
Rva0014C3B0::~Rva0014C3B0()
{
	if ( m_texture )
		( (Rva0014C3B0TextureIface *)m_texture )->release( 1 );
	m_texture = 0;

	while ( m_list )
	{
		Rva0014C3B0Node *node = m_list;
		if ( node )
			m_list = node->m_next;
		if ( node )
			node->release( 1 );
	}
}
