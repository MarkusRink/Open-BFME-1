// ?d_001aa780@@YAXXZ
// partial score=0.98 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME: TerrainLogic::addBridgeToLogic, retail 0x001AA780.

#include <new>

template <class T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &source);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

	private:
	char *m_text;
	int m_extra;
};

class BridgeInfo
{
	char m_data[0x6c];
};

class Dict;

enum PathfindLayerEnum
{
};

class Bridge
{
public:
	Bridge(BridgeInfo &info, Dict *props, AsciiString name);

	void setNext(Bridge *next)
	{
		m_next = next;
	}

	void setLayer(PathfindLayerEnum layer)
	{
		m_layer = layer;
	}

private:
	void *m_vtable;
	Bridge *m_next;
	char m_data[0x80];
	PathfindLayerEnum m_layer;
	char m_tail[4];
};

class Pathfinder
{
public:
	PathfindLayerEnum addBridge(Bridge *bridge);
};

class AI
{
public:
	Pathfinder *pathfinder(void) const
	{
		return *(Pathfinder **)((const char *)this + 0x0c);
	}
};

extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void addBridgeToLogic(BridgeInfo *info, Dict *props, AsciiString name);

private:
	char m_data[0x30];
	Bridge *m_bridgeListHead;
};

void TerrainLogic::addBridgeToLogic(BridgeInfo *info, Dict *props,
	AsciiString name)
{
	Bridge *bridge = new Bridge(*info, props, name);
	bridge->setNext(m_bridgeListHead);
	m_bridgeListHead = bridge;
	PathfindLayerEnum layer = TheAI->pathfinder()->addBridge(bridge);
	bridge->setLayer(layer);
}
