// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?deleteBridges@TerrainLogic@@IAEXXZ, retail 0x001AB150.
// The identity follows TerrainLogic's private deleteBridges declaration and
// the retail call to its deleteBridge vtable slot at +0xB4.
// stlport
typedef int ObjectID;

class Object;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	__forceinline Object *findObjectByIDNonzero(ObjectID id)
	{
		ObjectPtrHash::iterator it = m_objectHash.find(id);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad[0xB0];
	ObjectPtrHash m_objectHash;
};

class Bridge
{
public:
	void *m_vtable;
	Bridge *m_next;
	char m_pad[0x58];
	ObjectID m_bridgeObjectID;

	Bridge *getNext(void) { return m_next; }
};

class TerrainLogic
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void); virtual void slot26(void);
	virtual void slot27(void); virtual void slot28(void); virtual void slot29(void);
	virtual void slot30(void); virtual void slot31(void); virtual void slot32(void);
	virtual void slot33(void); virtual void slot34(void); virtual void slot35(void);
	virtual void slot36(void);
	virtual Bridge *getFirstBridge(void);
	virtual void slot38(void); virtual void slot39(void); virtual void slot40(void);
	virtual void slot41(void); virtual void slot42(void); virtual void slot43(void);
	virtual void slot44(void);
	virtual void deleteBridge(Bridge *bridge);

	protected:
	void deleteBridges(void);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

void TerrainLogic::deleteBridges(void)
{
	Bridge *bridge = getFirstBridge();
	if (bridge == 0)
		return;
	GameLogic *gameLogic = TheBfmeGameLogic;
	Bridge *next;
	do
	{
		next = bridge->getNext();
		if (bridge->m_bridgeObjectID == 0
			|| gameLogic->findObjectByIDNonzero(bridge->m_bridgeObjectID) == 0)
		{
			deleteBridge(bridge);
			gameLogic = TheBfmeGameLogic;
		}
		bridge = next;
	}
	while (bridge);
}

#undef TheBfmeGameLogic
