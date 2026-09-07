// cl: /DNDEBUG /MD /EHsc
// Open-BFME: PLAYER_COMPARE_LIGHT_POINTS at retail RVA 0x00323D50.

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class Parameter
{
public:
	int getInt(void) const { return m_int; }

private:
	unsigned char m_beforeInt[8];
	int m_int;
};

class Player
{
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class BfmeP1087
{
public:
};

class PlayerLightPoints
{
};

extern BfmeP1087 *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern void j_000230b5();
extern void j_00047d34();

static __forceinline PlayerMaskType bfmeNext1087(
	BfmeP1087 *engine, Parameter *parameter)
{
	typedef PlayerMaskType (BfmeP1087::*Function)(Parameter *);
	union {
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_000230b5;
	return (engine->*fn.member)(parameter);
}

static __forceinline int bfmeGetLightPoints(Player *player)
{
	typedef int (PlayerLightPoints::*Function)();
	union {
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_00047d34;
	return (reinterpret_cast<PlayerLightPoints *>(player)->*fn.member)();
}

class ScriptConditions
{
protected:
	Bool evaluatePlayerHasLightPoints(Parameter *, Parameter *, Parameter *);
};

// ?evaluatePlayerHasLightPoints@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerHasLightPoints(
	Parameter *playerParm, Parameter *comparisonParm, Parameter *countParm)
{
	int totalLightPoints = 0;
	PlayerMaskType playerMask =
		bfmeNext1087(TheScriptEngine, playerParm);
	while (playerMask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (player)
			totalLightPoints += bfmeGetLightPoints(player);
	}

	int comparison = comparisonParm->getInt();
	Bool result = false;
	switch (comparison)
	{
	case 0: result = totalLightPoints < countParm->getInt(); break;
	case 1: result = totalLightPoints <= countParm->getInt(); break;
	case 2: result = totalLightPoints == countParm->getInt(); break;
	case 3: result = totalLightPoints >= countParm->getInt(); break;
	case 4: result = totalLightPoints > countParm->getInt(); break;
	case 5: result = totalLightPoints != countParm->getInt(); break;
	}
	return result;
}
