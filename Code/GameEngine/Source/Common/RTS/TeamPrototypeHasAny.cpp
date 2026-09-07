// cl: /DNDEBUG /MD /EHsc

// The four TeamPrototype questions answered by asking every team on the
// instance list and stopping at the first yes:
//
//   0x000F6FD0  hasAnyBuildings(Bool)                     59 bytes
//   0x000F7020  hasAnyBuildings(BitFlags<192>, Bool)     117 bytes
//   0x000F70C0  hasAnyBuildings(BitFlags<116>) const      67 bytes
//   0x000F7170  hasAnyObjects(Bool)                       59 bytes
//
// This is the family one level down from PlayerHasAny.cpp: Player forwards each
// question to every prototype, and each prototype forwards it to every team.
// The two halves even name each other -- the ILT thunks Player calls (0x0003DD0C,
// 0x0000B55F, 0x00021D96) are these bodies, and the ILT thunks these call
// (0x00017652, 0x0003B5B6, 0x0003CCD1, 0x0001478B) are Team's.
//
// All four walk the instance list from the head at TeamPrototype+0x274, and
// BFME reaches the next team through a call rather than through the DLINK
// member Zero Hour's macros expand to, so advance() carries its own null
// check -- that is the second test on the same register, and the branch it
// feeds goes straight to the exit because an iterator that is done stays done.
// That iterator was written out four times, once per file.
//
// The one real disagreement between the four used to be left open here: three
// of them declare BitFlags as a template whose array size is computed,
// (NUMBITS + 31) / 32, which gives BitFlags<192> its six dwords, while the
// fourth hardcodes two dwords and ignores NUMBITS, because its row's
// decoration V?$BitFlags@$0HE@@ says 116 bits -- four dwords -- and its body
// copies exactly two. Retail settles it, and the answer is that the DECORATION
// is wrong, in width and in shape both. The formula is not the problem.
//
// A __thiscall member pops its own stack arguments, so the terminal `ret N` is
// the parameter block measured rather than inferred. 0x000F70C0 ends `ret 8`.
// Two controls say the formula reproduces retail wherever the decoration is
// sound: ?clearStatus@Object@@QAEXV?$BitFlags@$0CN@@@@Z is 45 bits, two dwords
// predicted and `ret 8` measured; the sibling at 0x000F7020 is 192 bits, six
// dwords plus a Bool predicted and `ret 0x1c` measured. Only $0HE@ misses, and
// it misses by half.
//
// It is not one 8-byte argument either. 0x000F70C0 forwards through ILT
// 0x0003CCD1 to 0x000F4B60, and that body loads [esp+0x14] into ecx as a THIS
// pointer for a member call and reads [esp+0x18] as a BYTE. So the eight bytes
// are two parameters -- a pointer and a Bool -- not a struct of any width, and
// the hardcoded array is right for a reason that has nothing to do with
// BitFlags. The Bool is the same trailing bfmeFlag the rest of this family
// carries.
//
// 116 is Zero Hour's KINDOF_COUNT, inherited with the name. BFME's own KindOf
// table is a NUL-terminated pointer array at file offset 0x00EAA068 holding 181
// names, OBSTACLE and SELECTABLE and IMMOBILE through to MOVE_FOR_NOONE, and
// 181 bits round to exactly the 192 the sibling overload already uses. So the
// KindOf mask in this binary is six dwords, and no BitFlags here is four.
//
// What is still open is only the replacement name: the pointer's class would be
// named by the member function it is `this` for, and that callee is the
// unidentified dump at 0x003A04A0. Until that has a name this row keeps its
// wrong one rather than trading it for a guess.

typedef unsigned int UnsignedInt;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS> class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

// BFME's two-dword mask. The size is measured from the body; the 116 is
// required by the row's decoration. See the header note -- they disagree, and
// the specialization is where that disagreement is written down.
template <> class BitFlags<116>
{
public:
	UnsignedInt m_bits[2];
};

typedef BitFlags<192> KindOfMaskType;
typedef BitFlags<116> KindOfMask64Type;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyBuildings(Bool bfmeFlag) const;			// ILT thunk at 0x00017652
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag);	// ILT thunk at 0x0003B5B6
	Bool hasAnyBuildings(KindOfMask64Type kindOf) const;		// ILT thunk at 0x0003CCD1
	Bool hasAnyObjects(Bool bfmeFlag) const;			// ILT thunk at 0x0001478B

	// Shape only: thiscall on the team, no arguments, the next team back.
	Team *_bfme_nextInInstanceList();				// ILT thunk at 0x00022A70
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator( Team *head )
		: m_cur( head )
	{
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	Team *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		if( m_cur )
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Bool hasAnyBuildings( Bool bfmeFlag );
	Bool hasAnyBuildings( KindOfMaskType kindOf, Bool bfmeFlag );
	Bool hasAnyBuildings( KindOfMask64Type kindOf ) const;
	Bool hasAnyObjects( Bool bfmeFlag );

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	unsigned char m_unmodelled_000[ 0x274 ];
	Team *m_teamInstanceList;						// +0x274
};

// ?hasAnyBuildings@TeamPrototype@@QAE_N_N@Z
Bool TeamPrototype::hasAnyBuildings( Bool bfmeFlag )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyBuildings( bfmeFlag ) )
			return true;
	}

	return false;
}

// ?hasAnyBuildings@TeamPrototype@@QAE_NV?$BitFlags@$0MA@@@_N@Z
//
// The mask is six dwords passed by value -- which the `ret 0x1C' accounts for
// together with the flag -- so most of the 117 bytes are the copy the compiler
// builds in the outgoing argument slots on every iteration.
Bool TeamPrototype::hasAnyBuildings( KindOfMaskType kindOf, Bool bfmeFlag )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyBuildings( kindOf, bfmeFlag ) )
			return true;
	}

	return false;
}

// ?hasAnyBuildings@TeamPrototype@@QBE_NV?$BitFlags@$0HE@@@@Z
Bool TeamPrototype::hasAnyBuildings( KindOfMask64Type kindOf ) const
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		const UnsignedInt first = kindOf.m_bits[ 0 ];
		const UnsignedInt second = kindOf.m_bits[ 1 ];
		KindOfMask64Type forwarded;
		forwarded.m_bits[ 0 ] = first;
		forwarded.m_bits[ 1 ] = second;
		if( iter.cur()->hasAnyBuildings( forwarded ) )
			return true;
	}

	return false;
}

// ?hasAnyObjects@TeamPrototype@@QAE_N_N@Z
Bool TeamPrototype::hasAnyObjects( Bool bfmeFlag )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyObjects( bfmeFlag ) )
			return true;
	}

	return false;
}
