// cl: /DNDEBUG /MD /EHsc

// Everything TeamPrototype does by walking its instance list -- the head at
// +0x274, advanced through the ILT at 0x00022A70:
//
//   0x000F6FD0  hasAnyBuildings(Bool)                     59 bytes
//   0x000F7020  hasAnyBuildings(BitFlags<192>, Bool)     117 bytes
//   0x000F70C0  hasAnyBuildings(BitFlags<116>) const      67 bytes
//   0x000F7170  hasAnyObjects(Bool)                       59 bytes
//   0x000ED6C0  findTeamByID(UnsignedInt)                 38 bytes
//   0x000F41A0  damageTeamMembers(Real)                   46 bytes
//   0x000F7FA0  xfer(Xfer *)                             368 bytes
//
// The first four stop at the first yes; the last two look for one team by id
// and forward to every team in turn. countTeamInstances and hasAnyUnits are the
// same walk again and stay in Team.cpp, where they are already matched.
//
// This is the family one level down from PlayerHasAny.cpp: Player forwards each
// question to every prototype, and each prototype forwards it to every team.
// The two halves even name each other -- the ILT thunks Player calls (0x0003DD0C,
// 0x0000B55F, 0x00021D96) are these bodies, and the ILT thunks these call
// (0x00017652, 0x0003B5B6, 0x0003CCD1, 0x0001478B) are Team's.
//
// All six walk the instance list from the head at TeamPrototype+0x274, and
// BFME reaches the next team through a call rather than through the DLINK
// member Zero Hour's macros expand to, so advance() carries its own null
// check -- that is the second test on the same register, and the branch it
// feeds goes straight to the exit because an iterator that is done stays done.
// That iterator was written out SEVEN times, once per file -- xfer included,
// which is the last of them.
//
// xfer is what finally makes TeamPrototype itself say something. Every walk
// body needs only the instance-list head, so all six spelled the object as
// 0x274 opaque bytes and a pointer. xfer names four things inside that run: the
// class is POLYMORPHIC, with the factory at +0x04 and the owning player at
// +0x08, the production-condition flag at +0x1C, the team template at +0x12C,
// and the attack-priority string at +0x270 immediately before the list head.
// The vptr it implies is why the padding here is 0x274 counted FROM the vptr
// rather than 0x274 of nothing -- same total, and now for a reason.
//
// The six files disagreed about two more things, both settled here.
//
// Team. Five files gave it only the methods they called; findTeamByID gave it a
// layout -- vptr, prototype pointer, then the id at +0x08, where BFME dropped
// Zero Hour's second base vptr. One Team carries both.
//
// The advance call. Five files call _bfme_nextInInstanceList on Team;
// findTeamByID casts each node to a separate BfmeTeamInstanceLink and calls it
// there, which is a DIFFERENT decoration. Those are not two functions: reverse
// pins ?_bfme_nextInInstanceList@Team@@QAEPAV1@XZ and
// ?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QAEPAV1@XZ to the same
// 0x00022A70, and symbols.csv already calls the second the view-class spelling
// of the first. So the walk is spelled once here -- and once more since, because
// xfer arrived carrying the view-class spelling too and now uses the Team one.
// The view class keeps its pin, which Team.cpp still uses.
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
// It is not one 8-byte argument either -- but `ret 8` is NOT what shows that,
// and the distinction matters because it is easy to cite the wrong half. The
// return arity fixes the WIDTH only: two dwords read separately and forwarded in
// order is exactly what one 8-byte by-value struct produces (copied low dword to
// low address) AND exactly what two 4-byte scalars produce, so the calling
// convention cannot separate them here.
//
// The CALLEE separates them. 0x000F70C0 forwards through ILT 0x0003CCD1 to
// 0x000F4B60, which is four pushes deep, so [esp+0x14] is arg1 and [esp+0x18] is
// arg2. At +0x4E it does `mov ecx,[esp+0x14]` immediately before a thiscall, and
// at +0x20 `mov al, byte ptr [esp+0x18]`. Half of a by-value struct cannot become
// a THIS pointer for a member call, so the eight bytes are two parameters -- a
// pointer and a Bool -- not a struct of any width, and the hardcoded array is
// right for a reason that has nothing to do with BitFlags. The Bool is the same
// trailing bfmeFlag the rest of this family carries.
//
// Where 116 comes from was got wrong here at first, and the corrected answer
// makes the case stronger rather than weaker. It is NOT Zero Hour's
// KINDOF_COUNT inherited with the name: Zero Hour's KindOf.h enumerates about
// 122, not 116. 116 is an exact enum count in THIS image -- the special-power
// name table at file offset 0x00EA8D40 holds exactly 116 entries,
// SPECIAL_INVALID through SPECIAL_HARVEST -- so V?$BitFlags@$0HE@@ is a real
// four-dword type that fourteen ledger rows use. The decoration is not
// nonsense, then; it is simply not this function's, because this body takes two
// dwords and that type is four. A wrong name borrowed from a real neighbour is
// harder to notice than an impossible one.
//
// BFME's own KindOf table is a NUL-terminated pointer array at file offset
// 0x00EAA068 holding 181 names, OBSTACLE and SELECTABLE and IMMOBILE through to
// MOVE_FOR_NOONE, and 181 bits round to exactly the 192 the sibling overload
// already uses. So the KindOf mask in this binary is six dwords, and nothing
// here is four dwords for KindOf reasons.
//
// Both tables are in reverse/name_tables.tsv. tools/name_tables.py sweeps them
// out of the image, and its --bitflags mode checks every decoration in the
// ledger against them, which is what caught the KINDOF_COUNT claim above.
//
// What is still open is only the replacement name: the pointer's class would be
// named by the member function it is `this` for, and that callee is the
// unidentified dump at 0x003A04A0. Until that has a name this row keeps its
// wrong one rather than trading it for a guess.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS> class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

// The two-dword specialization is NOT a claim that a 116-bit KindOf mask is two
// dwords. It is local to the one body above whose decoration says BitFlags<116>
// while its parameter block is not a mask at all -- `ret 8` there is a pointer
// plus a Bool, per the header note.
//
// The corroboration is in this directory: Team_countObjects.cpp holds
// ?countObjects@Team@@QAEHV?$BitFlags@$0HE@@@0@Z -- the SAME $0HE@ decoration,
// 116 bits -- and models the mask as SIX dwords, byte-matching. That body really
// does take two masks by value, and six dwords is what it takes. So the two
// sizes under one decoration are not a contradiction between the files: they are
// two bodies, and neither is passing the four-dword special-power type the
// decoration actually names. A fourth independent route to the header's
// conclusion, arrived at from a third size.
//
// Note what this specialization is therefore NOT saying. Per the header,
// V?$BitFlags@$0HE@@ is a real four-dword type -- the special-power mask, used
// by fourteen ledger rows -- so two dwords is not what BitFlags<116> means
// anywhere but here, and here only because this one body's decoration is
// borrowed from a neighbour. If a later body in this TU needs BitFlags<116> to
// mean the special-power mask it will want four dwords and this specialization
// will be in its way; the fix then is to correct THIS row's decoration, not to
// resize the type.
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
	Bool damageTeamMembers(Real amount);				// ILT 0x0000D148 -> 0x000F33F0

	UnsignedInt getID() const { return m_id; }

	// Shape only: thiscall on the team, no arguments, the next team back.
	Team *_bfme_nextInInstanceList();				// ILT thunk at 0x00022A70

	// Public because xfer both reads the id when saving and writes it into a
	// freshly created instance when loading.
	void *m_vptr;							// +0x00
	void *m_proto;							// +0x04
	UnsignedInt m_id;						// +0x08, BFME dropped ZH's second base vptr
};

class Snapshot
{
public:
	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);
};

class AsciiString
{
	void *m_data;
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isDoingCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *);
	virtual void slot27();
	virtual void slot28();
	virtual void xferTeamID(UnsignedInt *);
	virtual void xferInt(Int *);
	virtual void xferUnsignedShort(UnsignedShort *);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *);
};

class Player
{
public:
	Int m_pad[9];
	Int m_playerIndex;					// +0x24
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);
};

class TeamPrototype;

// Pin ?find@Rva002BD630TeamFactory@@QAEPAXH@Z @ 0x00044C2E
class Rva002BD630TeamFactory
{
public:
	void *find(Int teamID);
};

class TeamFactory
{
public:
	Team *createTeamOnPrototype(TeamPrototype *proto);
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

class TeamTemplateInfo
{
public:
	unsigned char m_body[0x144];
};

extern PlayerList *ThePlayerList;
extern TeamFactory *TheTeamFactory;

// The view xfer walks the instance list through. Kept as its own cast target
// rather than folded into the member below, so that body is unchanged.
struct BfmeTeamPrototypeInstances
{
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;

	BfmeTeamInstanceIterator iterate() const
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Bool hasAnyBuildings( Bool bfmeFlag );
	Bool hasAnyBuildings( KindOfMaskType kindOf, Bool bfmeFlag );
	Bool hasAnyBuildings( KindOfMask64Type kindOf ) const;
	Bool hasAnyObjects( Bool bfmeFlag );
	Team *findTeamByID( UnsignedInt teamID );
	void damageTeamMembers( Real amount );
	virtual void xfer( Xfer *xfer );				// vptr at +0x00

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	void *m_factory;							// +0x04
	Player *m_owningPlayer;							// +0x08
	unsigned char m_mid_00c[0x1c - 0x0c];
	Bool m_productionConditionAlwaysFalse;					// +0x1C
	unsigned char m_mid_01d[0x12c - 0x1d];
	TeamTemplateInfo m_teamTemplate;					// +0x12C
	AsciiString m_attackPriorityName;					// +0x270
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

// ?findTeamByID@TeamPrototype@@QAEPAVTeam@@I@Z
Team *TeamPrototype::findTeamByID( UnsignedInt teamID )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->getID() == teamID )
			return iter.cur();
	}
	return 0;
}

// ?damageTeamMembers@TeamPrototype@@QAEXM@Z
//
// Team::damageTeamMembers walks Team+0x0C members, skips effectively-dead and
// destroyed ones, and either kills or attempts damage from the amount.
void TeamPrototype::damageTeamMembers( Real amount )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		iter.cur()->damageTeamMembers( amount );
	}
}

// ?xfer@TeamPrototype@@UAEXPAVXfer@@@Z
void TeamPrototype::xfer(Xfer *xfer)
{
	if (xfer->isDoingCRC())
		return;

	// Retail frame is 0xC: teamID @ +0, version @ +4, owningPlayerIndex @ +8.
	// Count lives in the dead xfer* argument slot.
	struct Frame
	{
		UnsignedInt teamID;
		XferVersion version;
		Int owningPlayerIndex;
	};
	Frame frame;
	UnsignedShort teamInstanceCount;

	frame.version.m_version = 1;
	frame.version.m_currentVersion = 1;
	xfer->xferVersion(&frame.version);

	if (xfer->isSaving())
		frame.owningPlayerIndex = m_owningPlayer->m_playerIndex;
	xfer->xferInt(&frame.owningPlayerIndex);
	m_owningPlayer = ThePlayerList->getNthPlayer(frame.owningPlayerIndex);

	xfer->xferAsciiString(&m_attackPriorityName);
	xfer->xferBool(&m_productionConditionAlwaysFalse);
	xfer->xferSnapshot((Snapshot *)&m_teamTemplate);

	teamInstanceCount = 0;
	for (BfmeTeamInstanceIterator iter = ((const BfmeTeamPrototypeInstances *)this)->iterate();
		 !iter.done();
		 iter.advance())
		teamInstanceCount++;
	xfer->xferUnsignedShort(&teamInstanceCount);

	if (xfer->isSaving())
	{
		for (BfmeTeamInstanceIterator iter = ((const BfmeTeamPrototypeInstances *)this)->iterate();
			 !iter.done();
			 iter.advance())
		{
			frame.teamID = iter.cur()->m_id;
			xfer->xferTeamID(&frame.teamID);
			xfer->xferSnapshot((Snapshot *)iter.cur());
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < teamInstanceCount; ++i)
		{
			xfer->xferTeamID(&frame.teamID);
			Team *teamInstance = (Team *)((Rva002BD630TeamFactory *)TheTeamFactory)->find((Int)frame.teamID);
			if (teamInstance == 0)
			{
				teamInstance = TheTeamFactory->createTeamOnPrototype(this);
				if (teamInstance)
					teamInstance->m_id = frame.teamID;
			}
			xfer->xferSnapshot((Snapshot *)teamInstance);
		}
	}
}
