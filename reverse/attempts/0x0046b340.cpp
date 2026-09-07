// ?bfmeAddDR@BfmeOwnerDR@@QAEXPAVDrawable@@@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 89/81 bytes with the faithful model (this file); 77 with the alias hack
// below. Everything else matches.
// The callee is named in the ledger and gives the types away:
//   ?_M_insert_overflow@?$vector@PAVDrawable@@...@_STL@@IAEXPAPAVDrawable@@
//   ABQAV3@ABU__true_type@2@I_N@Z
// so this is `_STL::vector<Drawable*>::push_back`: compare finish against
// end_of_storage, placement-new the value (hence the `test eax,eax` null check
// on the returned pointer -- needs the inline placement operator new), bump
// finish through a POINTER to the vector (`add dword ptr [ecx+4],4`), else call
// _M_insert_overflow(finish, value, __true_type(), 1, true); then set the
// owner's dirty byte just past the vector.
// Residue: retail gives the empty `__true_type()` temporary NO storage -- both
// `lea` instructions in the overflow call compute the same address, the value
// parameter's own home slot. MSVC allocates a separate 4-byte slot for it
// (`push ecx`), +8 bytes. Passing `*(BfmeTagDR const *)&value` for the tag
// removes the slot but then MSVC computes the address once and pushes it
// twice, 77 bytes.
class Drawable;

typedef Drawable *BfmePtrDR;

struct BfmeTagDR
{
};

inline void * __cdecl operator new(unsigned int size, void *place) { return place; }

class BfmeVecDR
{
public:
	void bfmeOverflowDR(BfmePtrDR *where, BfmePtrDR const &value, BfmeTagDR const &tag, unsigned int count, bool flag);

	BfmePtrDR *m_bfmeStartDR;
	BfmePtrDR *m_bfmeFinishDR;
	BfmePtrDR *m_bfmeEndDR;
};

class BfmeOwnerDR
{
public:
	void bfmeAddDR(Drawable *value);

	unsigned char m_bfmeHeadDR[0x198];
	BfmeVecDR m_bfmeVecDR;
	char m_bfmeDirtyDR;
};

void BfmeOwnerDR::bfmeAddDR(Drawable *value)
{
	BfmeVecDR *vec = &m_bfmeVecDR;

	if (vec->m_bfmeFinishDR != vec->m_bfmeEndDR)
	{
		new (vec->m_bfmeFinishDR) BfmePtrDR(value);

		vec->m_bfmeFinishDR = vec->m_bfmeFinishDR + 1;
	}
	else
		vec->bfmeOverflowDR(vec->m_bfmeFinishDR, value, BfmeTagDR(), 1, true);

	m_bfmeDirtyDR = 1;
// ?unidentified_0002e9a1@WindowManager@@QAEXH@Z
// partial score=0.95 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );



};
}

class WindowManager
{
public:
	void unidentified_0002e9a1( int value );

private:
	char m_bfmePrefix[ 0x198 ];
	_STL::vector< int, _STL::allocator< int > > m_bfmeValues;
	bool m_bfmeValuesChanged;
};

void WindowManager::unidentified_0002e9a1( int value )
{
	_STL::vector< int, _STL::allocator< int > > &values = m_bfmeValues;

	if ( values._M_finish != values._M_end_of_storage )
	{
		if ( values._M_finish )
			*values._M_finish = value;
		++values._M_finish;
	}
	else
	{
		values._M_insert_overflow( values._M_finish, value,
			reinterpret_cast<const _STL::__false_type &>( value ), 1, true );
	}
	m_bfmeValuesChanged = true;
}
