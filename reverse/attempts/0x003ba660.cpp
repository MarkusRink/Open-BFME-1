// ?SplineCameraParseINIBlock@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.75 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: SplineCamera::ParseINIBlock (retail 0x003BA660 165 B; a gap
// claimed through its own exception text -- despite the "::" in the name the
// entry point takes no `this`, it is a plain (INI*, void*, void*, const
// void*) callback like its neighbours).  With no INI or instance it throws
// INIException(3 "SplineCamera::ParseINIBlock::Invalid data passed in.").
//
// IDENTITY LEVER (confirmed, matches the brief's own hint): the destructor
// thunk the body calls (j_000451f1 -> FUN_007ab460 -> retail RVA 0x003AB460)
// is ALREADY in the ledger as
// ??1?$_Rb_tree@HU?$pair@$$CBHUGen_t_003ab460_p24cd@@...@@QAE@XZ
// (Code/gen_small/tgrid_113.cpp, a std::map<int, Gen_t_003ab460_p24cd>
// destructor).  So this record genuinely embeds an std::map<int, X> member,
// not a plain polymorphic base -- this IS the "_Rb_tree destructor" case
// the brief flagged for this address.
//
// The constructor thunk (j_0001ca35 -> retail RVA 0x003BA5F0) and the append
// thunk (j_00016086 -> retail RVA 0x003B2890) are BOTH themselves unclaimed
// gap functions in functions.csv (tag "gap"); pinning either first (they are
// small, likely a map-constructing ctor and a thiscall append) would
// directly identify this record's real layout instead of guessing it.
//
// UNRESOLVED: right before calling the _Rb_tree destructor, the body writes
// a literal VA 0x010EC84C into the record's first dword. That address is
// NOT a vtable (no pin exists there yet) -- reading the image at that VA
// shows two dwords followed immediately by the ASCII strings
// "ModifyArmyEntry\0", "EyeTowerPoints\0", "UpdateAnimObject\0": it looks
// like an entry in a name/dispatch table (rodata), not a vfptr. Treating it
// as a "reset the record's own vtable before calling a base/member dtor"
// (the shape that worked for the sibling records with a real polymorphic
// virtual destructor, e.g. ForceBattle-style out-of-line dtor + virtual)
// gets CLOSE (37/165 bytes differ, first divergence right after the
// constructor call) but is provably the wrong model since there's no vtable
// pin at that address and the tree destructor doesn't need one. A worker
// with more time should: (1) pin the ctor/append thunks above first since
// they are their own unclaimed gap rows, (2) treat 0x010EC84C as a plain
// data pointer field of the record (perhaps a key/name pointer stored
// alongside the map) rather than a vtable, and (3) model the record as
// { somePointerOrTagField; std::map<int,Gen_t_003ab460_p24cd> m_map; } with
// the tag field written both at construction (inside the out-of-line ctor,
// invisible to us) and re-written to a fixed value before the map's dtor
// runs (defensive re-tag, not vtable reset).
//
// t=30min model=sonnet

typedef int Int;

struct FieldParse;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
};

class Rva003BA660Record
{
public:
	Rva003BA660Record();
	virtual ~Rva003BA660Record();

private:
	char m_body[ 0x14 ];
};

extern const FieldParse Rva003BA660RecordFieldParseTable[];

class Rva003BA660Owner
{
public:
	void append( Rva003BA660Record *record );
};

// ?SplineCameraParseINIBlock@@YAXPAVINI@@PAX1PBX@Z
void SplineCameraParseINIBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003BA660Record record;
		ini->initFromINI( &record, Rva003BA660RecordFieldParseTable );
		((Rva003BA660Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "SplineCamera::ParseINIBlock::Invalid data passed in." );
}
