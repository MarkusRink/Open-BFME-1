// ??0Rva005EBD40@@QAE@ABV0@@Z
// partial score=0.93 date=2026-09-06
// cl: /EHs-c-
//
// The clone at 0x005EBCC0 forwards to this 0x8e4-byte derived copy
// constructor.  Its two 90-element blocks contain three dwords each, and the
// final eleven dwords follow the two blocks.

class V3Head14
{
public:
	virtual ~V3Head14();
	int m_a, m_b, m_c, m_d;
};

class V3Vt0110F97C
{
public:
	virtual void s0();
};

class Rva005EB7B0 : public V3Head14, public V3Vt0110F97C
{
public:
	Rva005EB7B0( const Rva005EB7B0 & );
};

class Rva005EBD40Middle : public Rva005EB7B0
{
};

namespace FXParticleSystem
{

class LightningDrawModuleInfo
{
public:
	LightningDrawModuleInfo( const LightningDrawModuleInfo & );
	virtual ~LightningDrawModuleInfo();
	char m_storage[ 0x2c ];
};

}

struct Rva005EBD40Triple
{
	int m_a, m_b, m_c;
};

struct Rva005EBD40Tail
{
	int m_a0, m_a1, m_a2, m_a3, m_a4, m_a5;
	int m_a6, m_a7, m_a8, m_a9, m_a10;
};

class Rva005EBD40
	: public Rva005EBD40Middle, public FXParticleSystem::LightningDrawModuleInfo
{
public:
	Rva005EBD40( const Rva005EBD40 & );

	Rva005EBD40Triple m_first[ 90 ];
	Rva005EBD40Triple m_second[ 90 ];
	Rva005EBD40Tail m_tail;
};

Rva005EBD40::Rva005EBD40( const Rva005EBD40 &o )
	: Rva005EBD40Middle( o ), FXParticleSystem::LightningDrawModuleInfo( o )
{
	int *destination = (int *)m_first;
	const int *source = &o.m_first[ 0 ].m_c;
	for ( int i = 0; i < 90; ++i )
	{
		destination[ 0 ] = source[ -2 ];
		destination[ 1 ] = source[ -1 ];
		destination[ 2 ] = source[ 0 ];
		destination += 3;
		source += 3;
	}

	destination = (int *)m_second;
	source = &o.m_second[ 0 ].m_c;
	for ( int i = 0; i < 90; ++i )
	{
		destination[ 0 ] = source[ -2 ];
		destination[ 1 ] = source[ -1 ];
		destination[ 2 ] = source[ 0 ];
		destination += 3;
		source += 3;
	}

	m_tail.m_a0 = o.m_tail.m_a0;
	m_tail.m_a1 = o.m_tail.m_a1;
	m_tail.m_a2 = o.m_tail.m_a2;
	m_tail.m_a3 = o.m_tail.m_a3;
	m_tail.m_a4 = o.m_tail.m_a4;
	m_tail.m_a5 = o.m_tail.m_a5;
	m_tail.m_a6 = o.m_tail.m_a6;
	m_tail.m_a7 = o.m_tail.m_a7;
	m_tail.m_a8 = o.m_tail.m_a8;
	m_tail.m_a9 = o.m_tail.m_a9;
	m_tail.m_a10 = o.m_tail.m_a10;
}
