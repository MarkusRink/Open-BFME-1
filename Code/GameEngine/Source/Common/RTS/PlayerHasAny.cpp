// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// The three Player questions that are answered by asking every team prototype
// the same question and stopping at the first yes:
//
//   0x000CDF20  hasAnyBuildings(Bool)                    60 bytes
//   0x000CDF70  hasAnyBuildings(KindOfMaskType, Bool)   118 bytes
//   0x000CE0B0  hasAnyObjects(Bool)                      60 bytes
//
// All three are the reference's body with the same BFME change -- the question
// carries an extra flag that the player forwards untouched -- and all three
// walk the prototype list at this+0x288, reloading the list header each
// iteration for the end test because the call in between is enough to make it.
// Only the mask overload differs in shape, and only because BitFlags<192> is
// six dwords passed by value: most of its 118 bytes are the copy the compiler
// builds in the outgoing argument slots on every turn, which is also what the
// `ret 0x1C` accounts for.
//
// They sat in three files that each declared their own TeamPrototype carrying
// exactly the one method that file called, so nothing said the three questions
// are asked of the same class through the same list. Declared once, they are.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <int NUMBITS> class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Bool hasAnyBuildings(Bool bfmeFlag);				// ILT 0x0003DD0C
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag);	// ILT 0x0000B55F
	Bool hasAnyObjects(Bool bfmeFlag);				// ILT 0x00021D96
};

typedef _STL::list<TeamPrototype *> PlayerTeamList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool hasAnyBuildings(Bool bfmeFlag) const;
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag) const;
	Bool hasAnyObjects(Bool bfmeFlag) const;

private:
	char m_slice_pad[0x288];				// retail this+0x00 .. +0x287, untouched
	PlayerTeamList m_playerTeamPrototypes;			// this+0x288
};

// ?hasAnyBuildings@Player@@QBE_N_N@Z
Bool Player::hasAnyBuildings(Bool bfmeFlag) const
{
	for (PlayerTeamList::const_iterator it = m_playerTeamPrototypes.begin();
			 it != m_playerTeamPrototypes.end(); ++it)
	{
		if ((*it)->hasAnyBuildings(bfmeFlag)) {
			return true;
		}
	}
	return false;
}

// ?hasAnyBuildings@Player@@QBE_NV?$BitFlags@$0MA@@@_N@Z
Bool Player::hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag) const
{
	for (PlayerTeamList::const_iterator it = m_playerTeamPrototypes.begin();
			 it != m_playerTeamPrototypes.end(); ++it)
	{
		if ((*it)->hasAnyBuildings(kindOf, bfmeFlag)) {
			return true;
		}
	}
	return false;
}

// ?hasAnyObjects@Player@@QBE_N_N@Z
Bool Player::hasAnyObjects(Bool bfmeFlag) const
{
	for (PlayerTeamList::const_iterator it = m_playerTeamPrototypes.begin();
			 it != m_playerTeamPrototypes.end(); ++it)
	{
		if ((*it)->hasAnyObjects(bfmeFlag)) {
			return true;
		}
	}
	return false;
}
