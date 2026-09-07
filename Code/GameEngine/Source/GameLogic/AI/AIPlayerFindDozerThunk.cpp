// cl: /DNDEBUG /MD /EHsc
// readable body of ?findDozer@AIPlayer@@MAEPAVObject@@PBUCoord3D@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp

typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

#define NULL 0

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Player;
class Object;

class Overridable
{
public:
	const Overridable *getNextOverride() const { return m_nextOverride; }
	const Overridable *getFinalOverride() const;

private:
	void *m_vtable;
	const Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xc8 - 8];
	unsigned int m_kindOf;
};

class DozerAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Bool isTaskPending(int task);
	virtual void slot1c();
	virtual Bool isAnyTaskPending();
};

class SupplyTruckAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual Bool isCurrentlyFerryingSupplies();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual Bool isForcedIntoWantingState();
};

class AIUpdateInterface
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02c();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03c();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04c();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05c();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06c();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07c();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08c();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09c();
	virtual void slot0a0();
	virtual void slot0a4();
	virtual void slot0a8();
	virtual void slot0ac();
	virtual void slot0b0();
	virtual void slot0b4();
	virtual void slot0b8();
	virtual void slot0bc();
	virtual void slot0c0();
	virtual void slot0c4();
	virtual void slot0c8();
	virtual void slot0cc();
	virtual void slot0d0();
	virtual void slot0d4();
	virtual void slot0d8();
	virtual void slot0dc();
	virtual void slot0e0();
	virtual void slot0e4();
	virtual void slot0e8();
	virtual void slot0ec();
	virtual void slot0f0();
	virtual void slot0f4();
	virtual void slot0f8();
	virtual void slot0fc();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10c();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11c();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12c();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual DozerAIInterface *getDozerAIInterface();
	virtual void slot140();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();
};

class Object
{
public:
	Object *getNextObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) + 0x88);
	}
	Player *getControllingPlayer() const;
	const ThingTemplate *getTemplate() const
	{
		return *reinterpret_cast<const ThingTemplate *const *>(
			reinterpret_cast<const char *>(this) + 4);
	}
	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(
			reinterpret_cast<const char *>(this) + 0x74);
	}
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *reinterpret_cast<AIUpdateInterface *const *>(
			reinterpret_cast<const char *>(this) + 0x204);
	}
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}
};

class GameLogic
{
public:
	Object *getFirstObject();
};

extern GameLogic *TheGameLogic;

class AIPlayer
{
protected:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual Object *findDozer(const Coord3D *pos);
	virtual void queueDozer();

private:
	unsigned char m_unreconstructed_004[8];
	Player *m_player;
	unsigned char m_unreconstructed_010[0x40];
	ObjectID m_repairDozer;
};

enum { DOZER_TASK_BUILD = 0, KINDOF_DOZER = 1 << 14 };

Object *AIPlayer::findDozer(const Coord3D *pos)
{
	Object *obj;
	Object *dozer = NULL;
	Bool needDozer = true;
	Object *closestDozer = NULL;
	Real closestDistSqr = 0;

	for (obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject())
	{
		Player *owner = obj->getControllingPlayer();
		if (owner == m_player)
		{
			const ThingTemplate *thingTemplate = obj->getTemplate();
			if (thingTemplate && thingTemplate->getNextOverride())
				thingTemplate = static_cast<const ThingTemplate *>(
					thingTemplate->getNextOverride()->getFinalOverride());
			if ((thingTemplate->m_kindOf & KINDOF_DOZER) != 0)
			{
				AIUpdateInterface *ai = obj->getAIUpdateInterface();
				if (ai == NULL)
					continue;

				DozerAIInterface *dozerAI = ai->getDozerAIInterface();
				if (dozerAI)
				{
					SupplyTruckAIInterface *supplyTruckAI =
						ai->getSupplyTruckAIInterface();
					if (!dozerAI->isAnyTaskPending() && supplyTruckAI)
					{
						if (supplyTruckAI->isCurrentlyFerryingSupplies()
							|| supplyTruckAI->isForcedIntoWantingState())
							continue;
					}
					if (obj->getID() == m_repairDozer)
						continue;
					needDozer = false;
					if (dozerAI->isTaskPending(DOZER_TASK_BUILD))
						continue;
					if (!dozerAI->isAnyTaskPending())
						dozer = obj;
					if (dozer == NULL)
						dozer = obj;
					if (dozer && !dozerAI->isAnyTaskPending())
					{
						Real distSqr;
						Real dx, dy;
						dx = pos->x - dozer->getPosition()->x;
						dy = pos->y - dozer->getPosition()->y;
						distSqr = dx * dx + dy * dy;
						if (closestDozer == NULL)
						{
							closestDozer = dozer;
							closestDistSqr = distSqr;
						}
						else if (distSqr < closestDistSqr)
						{
							closestDozer = dozer;
							closestDistSqr = distSqr;
						}
					}
				}
			}
		}
	}
	if (needDozer)
		queueDozer();
	if (closestDozer)
		return closestDozer;
	return dozer;
}
