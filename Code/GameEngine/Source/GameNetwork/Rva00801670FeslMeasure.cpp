// cl: /GX- /GS
// FESL game-browser record measurement at retail 0x00801670.
//
// The enclosing object is the BfmeThingVHW family: the matched
// BfmeThingVHW::bfmeClearVHW body installs the same vtable that the nearby
// constructor/destructor pair installs, and its direct caller writes the host
// pointer at +0x04 before calling this body.  The method name below is kept
// address-derived because no public source name for this slot was recovered.
//
// The helper at 0x007F76D0 is already matched as the bfmeAt body.  Its body
// reads the vector and index from [esp+4]/[esp+8] and returns with ret 8, but
// every named demangler-family caller loads the host into ECX before those
// pushes.  This neutral receiver view preserves that proven source ABI while
// making no claim about an unrecovered public helper class name.

class Rva00800290Buffer
{
public:
	void addPadded( int size );
	void addString( const char *text );

	char *m_ptr;
	int m_size;
};

class BfmeSlotCZ
{
public:
	int *m_bfmePointer;
	int m_bfmeTag;
};

class BfmeVecCZ
{
public:
	BfmeSlotCZ *m_bfmeStart;
	int m_bfmeCount;
};

class Rva00801670Host
{
public:
	int *rva007F76D0( BfmeVecCZ *vector, int index );
};

class Rva007FBEF0GameRecord
{
public:
	bool Rva007FBE80( const char *key, char *dest, unsigned destSize );

	char m_pad00[0x26];
	char m_str26;
	char m_pad27[0x7F];
	char m_strA6;
	char m_padA7[0x89];
	char m_str130;
};

// The matched 0x007FBE70 accessor reads its receiver's byte at +0x190 and
// returns that buffer or null.  Keep that existing address-derived owner view
// separate from the record's named lookup-helper view; the retail call passes
// the same record pointer to both bodies.
class Gen_007fbe70
{
public:
	char *bfmeText();

	char m_bfmeHead[0x190];
	char m_bfmeBuffer[1];
};

class BfmeThingVHW
{
public:
	void rva00801670( Rva007FBEF0GameRecord *rec );

	void *m_bfmeVfptr;
	Rva00801670Host *m_bfme04;
	char m_bfmePad08[8];
	Rva00800290Buffer m_bfme10;
};

void BfmeThingVHW::rva00801670( Rva007FBEF0GameRecord *rec )
{
	char slot[0x40];
	int count;
	int i;
	BfmeVecCZ *vector;
	char *key;

	m_bfme10.addString( &rec->m_str26 );
	m_bfme10.addString( &rec->m_strA6 );
	m_bfme10.addString( &rec->m_str130 );
	if( ( (Gen_007fbe70 *)rec )->bfmeText() )
		m_bfme10.addPadded( 0x28 );
	else
		m_bfme10.addPadded( 0x10 );

	vector = (BfmeVecCZ *)( (char *)m_bfme04 + 0x2A8 );
	count = vector->m_bfmeCount;
	m_bfme10.addPadded( count * 4 );
	for( i = 0; i < count; i++ )
	{
		key = (char *)m_bfme04->rva007F76D0( vector, i );
		slot[0] = 0;
		if( rec->Rva007FBE80( key, slot, 0x40 ) )
			m_bfme10.addString( slot );
	}
}
