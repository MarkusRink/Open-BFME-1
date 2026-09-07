// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/asciistring_downloadmanager

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short wchar_t;

#include "Common/UnicodeString.h"

class GameLogic
{
};

class GameLogicPortraitShim
{
public:
	Bool isInMultiplayerOrSkirmishGame();
};

class PlayerList
{
public:
	Int unidentified_000df510(Bool includeFields);
};

class GlobalData
{
};

class Gen_00083240
{
public:
	float bfmeGet0(Int index) const;
};

class Money
{
public:
	void deposit(UnsignedInt amount, Bool playSound = true);
};

class ScoreKeeper
{
public:
	void addMoneyEarned(Int amount);
};

class Player
{
public:
	Money *getMoney()
	{
		return (Money *)((char *)this + 0x48);
	}

	ScoreKeeper *getScoreKeeper()
	{
		return (ScoreKeeper *)((char *)this + 0x348);
	}

	void *getControllingPlayerPadding();
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva000C97C0Player
{
public:
	Int adjustBountyForLivingWorld(Int bounty);
};

class BfmeQ1254
{
public:
	char m_pad[0x1c4];
	UnsignedInt m_bfme1c4;
};

class BfmeS1254
{
public:
	BfmeQ1254 *bfmeGet1254();
};

class BfmeA1254
{
public:
	void bfmeDraw1254(BfmeS1254 *object, Int text);
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

class SalvageCrateCollideModuleData
{
public:
	char m_pad[0x68];
	Int m_minimumMoney;
	Int m_maximumMoney;
};

class SalvageCrateCollide
{
private:
	virtual void slot00() = 0;
	SalvageCrateCollideModuleData *m_moduleData;
	Object *m_object;

	void doMoney(Object *other);
};

extern char g_bfmeFileAO[];
extern int GetGameLogicRandomValue(Int low, Int high, char *file, Int line);
extern GameLogic *TheBfmeGameLogic;
extern PlayerList *Rva002EE330ThePlayers;
extern GlobalData *TheWritableGlobalData;
extern GameTextInterface *TheGameText;

void SalvageCrateCollide::doMoney(Object *other)
{
	const SalvageCrateCollideModuleData *md = m_moduleData;
	Int money;

	if (md->m_minimumMoney != md->m_maximumMoney)
		money = GetGameLogicRandomValue(md->m_minimumMoney, md->m_maximumMoney,
			g_bfmeFileAO, 0xc4);
	else
		money = md->m_minimumMoney;

	if (money > 0)
	{
		if (((GameLogicPortraitShim *)TheBfmeGameLogic)->isInMultiplayerOrSkirmishGame())
		{
			const Int playerIndex = Rva002EE330ThePlayers->unidentified_000df510(false);
			const float factor = ((Gen_00083240 *)((char *)TheWritableGlobalData + 0xee0))->bfmeGet0(playerIndex);
			money = (Int)(money * factor);
		}

		Player *player = other->getControllingPlayer();
		if (player != 0)
		{
			money = ((Rva000C97C0Player *)player)->adjustBountyForLivingWorld(money);
			player->getMoney()->deposit(money);
			player->getScoreKeeper()->addMoneyEarned(money);
		}

		UnicodeString moneyString;
		moneyString.format(TheGameText->fetch("GUI:AddCash"), money);
		((BfmeA1254 *)this)->bfmeDraw1254((BfmeS1254 *)other, (Int)&moneyString);
	}
}
