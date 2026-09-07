// cl: /DNDEBUG /MD
// BFME GameLogic::deselectObject, retail 0x00382F50, 178 bytes.
// BFME moves Object::getDrawable to virtual slot 10 and
// InGameUI::deselectDrawable to virtual slot 57. The final Object callback
// reaches retail body 0x001C89E0 through ILT 0x000380CD.

typedef bool Bool;
typedef unsigned short PlayerMaskType;

class Object;
class Player;
class AIGroup;
class Drawable;

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class AI
{
public:
	AIGroup *createGroup(void);
	void destroyGroup(AIGroup *group);
};

class Player
{
public:
	void getCurrentSelectionAsAIGroup(AIGroup *group);
	void setCurrentlySelectedAIGroup(AIGroup *group);
};

class AIGroup
{
public:
	Bool remove(Object *obj);
};

class BFMEGameLogicObjectDrawableShim
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot05() = 0;
	virtual void bfmeSlot06() = 0;
	virtual void bfmeSlot07() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot09() = 0;
	virtual Drawable *getDrawable() const = 0;
};

class BFMEGameLogicInGameUIShim
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot05() = 0;
	virtual void bfmeSlot06() = 0;
	virtual void bfmeSlot07() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot09() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot11() = 0;
	virtual void bfmeSlot12() = 0;
	virtual void bfmeSlot13() = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot15() = 0;
	virtual void bfmeSlot16() = 0;
	virtual void bfmeSlot17() = 0;
	virtual void bfmeSlot18() = 0;
	virtual void bfmeSlot19() = 0;
	virtual void bfmeSlot20() = 0;
	virtual void bfmeSlot21() = 0;
	virtual void bfmeSlot22() = 0;
	virtual void bfmeSlot23() = 0;
	virtual void bfmeSlot24() = 0;
	virtual void bfmeSlot25() = 0;
	virtual void bfmeSlot26() = 0;
	virtual void bfmeSlot27() = 0;
	virtual void bfmeSlot28() = 0;
	virtual void bfmeSlot29() = 0;
	virtual void bfmeSlot30() = 0;
	virtual void bfmeSlot31() = 0;
	virtual void bfmeSlot32() = 0;
	virtual void bfmeSlot33() = 0;
	virtual void bfmeSlot34() = 0;
	virtual void bfmeSlot35() = 0;
	virtual void bfmeSlot36() = 0;
	virtual void bfmeSlot37() = 0;
	virtual void bfmeSlot38() = 0;
	virtual void bfmeSlot39() = 0;
	virtual void bfmeSlot40() = 0;
	virtual void bfmeSlot41() = 0;
	virtual void bfmeSlot42() = 0;
	virtual void bfmeSlot43() = 0;
	virtual void bfmeSlot44() = 0;
	virtual void bfmeSlot45() = 0;
	virtual void bfmeSlot46() = 0;
	virtual void bfmeSlot47() = 0;
	virtual void bfmeSlot48() = 0;
	virtual void bfmeSlot49() = 0;
	virtual void bfmeSlot50() = 0;
	virtual void bfmeSlot51() = 0;
	virtual void bfmeSlot52() = 0;
	virtual void bfmeSlot53() = 0;
	virtual void bfmeSlot54() = 0;
	virtual void bfmeSlot55() = 0;
	virtual void bfmeSlot56() = 0;
	virtual void deselectDrawable(Drawable *draw) = 0;
};

class BFMEGameLogicObjectSelectionDeselectShim
{
public:
	void notifyRva001C89E0(Player *player);
};

class GameLogic
{
public:
	void deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient);
};

extern PlayerList *ThePlayerList;
extern AI *TheAI;
extern BFMEGameLogicInGameUIShim *TheInGameUI;

void GameLogic::deselectObject(Object *obj, PlayerMaskType playerMask, Bool affectClient)
{
	if (!obj) {
		return;
	}

	while (playerMask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (!player) {
			return;
		}

		AIGroup *group = 0;
		group = TheAI->createGroup();
		player->getCurrentSelectionAsAIGroup(group);

		Bool deleted = false;
		Bool actuallyRemoved = false;

		if (group) {
			deleted = group->remove(obj);
			actuallyRemoved = true;
		}

		if (actuallyRemoved) {
			if (!deleted) {
				player->setCurrentlySelectedAIGroup(group);
				TheAI->destroyGroup(group);
			} else {
				player->setCurrentlySelectedAIGroup(0);
			}

			if (affectClient) {
				Drawable *draw = reinterpret_cast<BFMEGameLogicObjectDrawableShim *>(obj)->getDrawable();
				if (draw) {
					reinterpret_cast<BFMEGameLogicInGameUIShim *>(TheInGameUI)->deselectDrawable(draw);
				}
			}
		}

		reinterpret_cast<BFMEGameLogicObjectSelectionDeselectShim *>(obj)->notifyRva001C89E0(player);
	}
}
