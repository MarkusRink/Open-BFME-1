// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ScienceStore::playerHasRootPrereqsForScience, retail 0x000E8040.
//
// The control-bar callers pass TheScienceStore, a Player pointer, and a
// ScienceType to this two-argument member before checking hasScience,
// playerHasPrereqsForScience, and the purchase cost.  Retail constructs a
// temporary STLport map<int,bool> and hands it to the three-argument recursive
// science prerequisite helper at 0x000E7C20.  The helper's original spelling
// is not established by the available headers, so its TU-local declaration is
// deliberately address-derived and pinned to the verified retail body; the
// compiler's call resolver selects the image's incremental thunk at each site.

#include <map>

typedef bool Bool;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Player;

class ScienceStore
{
public:
	Bool playerHasRootPrereqsForScience( const Player *player, ScienceType st ) const;

private:
	Bool rva000E7C20SciencePrereqMemo( const Player *player, ScienceType st,
		void *memo ) const;
};

Bool ScienceStore::playerHasRootPrereqsForScience( const Player *player, ScienceType st ) const
{
	std::map<ScienceType, Bool> memo;
	return rva000E7C20SciencePrereqMemo( player, st, &memo );
}
