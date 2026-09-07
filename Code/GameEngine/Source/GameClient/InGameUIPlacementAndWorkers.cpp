// cl: /DNDEBUG /MD /EHsc
// readable body of ?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// readable body of ?recreateControlBar@InGameUI@@UAEXXZ: Code/GameEngine/Source/GameClient/InGameUI.cpp
//
// Four InGameUI members, in two pairs that the image itself puts together:
//
//   destroyPlacementIcons  0x0043AF00   71 B  IAE (protected)
//   placeBuildAvailable    0x0043AF60  363 B  UAE (public virtual)
//   getIdleWorkerCount     0x004422C0   41 B  EAE (private virtual)
//   recreateControlBar     0x00442300  279 B  UAE (public virtual)
//
// Four files, four InGameUIs, each measured from its own field: 0x53c to the
// placement icons, 0x824 to the mouse mode, 0x131c to the idle-worker lists,
// 0x139c to the idle-worker window. Nothing contradicted anything, and one of
// the joins is worth stating on its own -- the thirty-two idle-worker list
// heads run from +0x131c to +0x139c and the idle-worker window is the very
// next field. Two files measured to opposite ends of the same array without
// either being able to say so.
//
// The vtable is the placement file's, which is the only one of the four with
// pinned slots in it: placeBuildAvailable at 48, setPlacementStart at 51,
// setRadiusCursorNone at 71. The other two virtuals are virtual by their
// mangled names and nothing more -- no body here calls them through the table
// -- so they are declared past the pinned run rather than given a number.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct ICoord2D;
class Object;
class Drawable;
class ThingTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unreconstructed_000[0x24];
	Int m_playerIndex;					// +0x024
	unsigned char m_unreconstructed_028[0x1C4 - 0x28];
	UnsignedInt m_playerColor;				// +0x1c4
	UnsignedInt m_playerNightColor;				// +0x1c8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	unsigned char m_unreconstructed_000[0x74];

public:
	UnsignedInt m_id;
	Player *getControllingPlayer(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void setOrientation(float angle);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable : public Thing
{
private:
	unsigned char m_unreconstructed_004[0xAF];

public:
	float m_opacity;
	unsigned char m_unreconstructed_0B4[0x48];
	Object *m_object;

	void setIndicatorColor(UnsignedInt color);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
private:
	unsigned char m_unreconstructed_000[0x3B0];

public:
	float m_placementViewAngle;
};

enum DrawableStatus
{
	DRAWABLE_STATUS_NO_STATE_PARTICLES = 8
};

class BFMEThingFactory
{
public:
	Drawable *newDrawable(const ThingTemplate *thing, DrawableStatus status,
		Int unknown);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
private:
	unsigned char m_unreconstructed_000[0x218];

public:
	Int m_timeOfDay;
};

class Mouse
{
public:
	enum MouseCursor
	{
		ARROW = 2,
		CROSS = 4
	};

	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1C(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2C(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void setCursor(MouseCursor cursor);
	virtual void capture(void);
	virtual void releaseCapture(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	char m_padding00[0x0c];
	Player *m_localPlayer;					// +0x0c
};

extern PlayerList *ThePlayerList;

// Retail's AsciiString is a one-pointer StringBase<char> view.  Keeping the
// constructors and release operation out of line leaves the calls at the
// already matched retail string bodies (0x00888BC0 and 0x00887940).
template <typename T> class StringBase
{
private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &that );
	void releaseBuffer();
	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( text );
	}

	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	const char *str() const
	{
		return m_text ? m_text + 8 : (const char *)0x0107388B;
	}

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	virtual void deleteInstance( UnsignedInt flags );
};

class WindowLayoutInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot000(); virtual void slot004(); virtual void slot008();
	virtual void slot00C(); virtual void slot010(); virtual void slot014();
	virtual void slot018(); virtual void slot01C(); virtual void slot020();
	virtual void slot024(); virtual void slot028(); virtual void slot02C();
	virtual void slot030(); virtual void slot034(); virtual void slot038();
	virtual void slot03C(); virtual void slot040(); virtual void slot044();
	virtual void slot048(); virtual void slot04C(); virtual void slot050();
	virtual void slot054(); virtual void slot058(); virtual void slot05C();
	virtual void slot060(); virtual void slot064();
	virtual GameWindow *winCreateFromScript( AsciiString file,
		WindowLayoutInfo *info, void *extra );		// slot 26, vtable+0x68
	virtual void slot06C(); virtual void slot070(); virtual void slot074();
	virtual void slot078(); virtual void slot07C(); virtual void slot080();
	virtual void slot084(); virtual void slot088(); virtual void slot08C();
	virtual void slot090(); virtual void slot094(); virtual void slot098();
	virtual void slot09C(); virtual void slot0A0(); virtual void slot0A4();
	virtual void slot0A8(); virtual void slot0AC();
	virtual void slot0B0(); virtual void slot0B4(); virtual void slot0B8();
	virtual void slot0BC(); virtual void slot0C0(); virtual void slot0C4();
	virtual void slot0C8(); virtual void slot0CC(); virtual void slot0D0();
	virtual void slot0D4(); virtual void slot0D8();
	virtual GameWindow *winGetWindowFromId( GameWindow *window, Int id );	// slot 55, vtable+0xdc
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	Int nameToKey( const char *name );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	ControlBar();
	virtual ~ControlBar();
	virtual void init();

private:
	char m_unreconstructed[0x2F4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainVisual.h
class TerrainVisual
{
public:
	virtual void reserved00(); virtual void reserved01(); virtual void reserved02();
	virtual void reserved03(); virtual void reserved04(); virtual void reserved05();
	virtual void reserved06(); virtual void reserved07(); virtual void reserved08();
	virtual void reserved09(); virtual void reserved10(); virtual void reserved11();
	virtual void reserved12(); virtual void reserved13(); virtual void reserved14();
	virtual void reserved15(); virtual void reserved16(); virtual void reserved17();
	virtual void reserved18(); virtual void reserved19(); virtual void reserved20();
	virtual void reserved21(); virtual void reserved22(); virtual void reserved23();
	virtual void reserved24(); virtual void reserved25();
	virtual void removeFactionBibDrawable(Drawable *drawable);	// slot 26, vtable+0x68
	virtual void removeAllBibs();					// slot 27, vtable+0x6c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void reserved00(); virtual void reserved01(); virtual void reserved02();
	virtual void reserved03(); virtual void reserved04(); virtual void reserved05();
	virtual void reserved06(); virtual void reserved07(); virtual void reserved08();
	virtual void reserved09(); virtual void reserved10(); virtual void reserved11();
	virtual void reserved12(); virtual void reserved13(); virtual void reserved14();
	virtual void reserved15(); virtual void reserved16(); virtual void reserved17();
	virtual void reserved18(); virtual void reserved19(); virtual void reserved20();
	virtual void reserved21(); virtual void reserved22(); virtual void reserved23();
	virtual void destroyDrawable(Drawable *drawable);		// slot 24, vtable+0x60
};

// The idle-worker lists are STLport list heads: one sentinel pointer each, and
// the count is the walk back round to it.
struct BfmeIdleWorkerNode
{
	BfmeIdleWorkerNode *m_next;
	BfmeIdleWorkerNode *m_prev;
	void *m_object;
};

struct BfmeIdleWorkerList
{
	BfmeIdleWorkerNode *m_head;

	Int size() const
	{
		BfmeIdleWorkerNode *node = m_head->m_next;
		Int count = 0;
		while (node != m_head)
		{
			node = node->m_next;
			++count;
		}
		return count;
	}
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern ControlBar *TheControlBar;
extern TerrainVisual *TheTerrainVisual;
extern GameClient *TheGameClient;

void HideControlBar( bool immediate );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
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
	virtual void slot0A(void);
	virtual void slot0B(void);
	virtual void slot0C(void);
	virtual void slot0D(void);
	virtual void slot0E(void);
	virtual void slot0F(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot1A(void);
	virtual void slot1B(void);
	virtual void slot1C(void);
	virtual void slot1D(void);
	virtual void slot1E(void);
	virtual void slot1F(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot2A(void);
	virtual void slot2B(void);
	virtual void slot2C(void);
	virtual void slot2D(void);
	virtual void slot2E(void);
	virtual void slot2F(void);
	virtual void placeBuildAvailable(const ThingTemplate *build,
		Drawable *buildDrawable);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void setPlacementStart(const ICoord2D *start);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot3A(void);
	virtual void slot3B(void);
	virtual void slot3C(void);
	virtual void slot3D(void);
	virtual void slot3E(void);
	virtual void slot3F(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual void slot43(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void setRadiusCursorNone(void);

	// Virtual by their mangled names -- recreateControlBar is UAE and
	// getIdleWorkerCount EAE -- but no body here calls either through the
	// table, so nothing pins their slot numbers. They sit past the last
	// pinned entry rather than claiming one.
	virtual void recreateControlBar();

	void createControlBar()
	{
		TheWindowManager->winCreateFromScript(
			AsciiString( "ControlBar.wnd" ), 0, 0 );
		HideControlBar( true );
	}

protected:
	void destroyPlacementIcons(void);

private:
	virtual Int getIdleWorkerCount();

	unsigned char m_unreconstructed_004[0x530];
	const ThingTemplate *m_pendingPlaceType;		// +0x534
	UnsignedInt m_pendingPlaceSourceObjectID;		// +0x538
	Drawable **m_placeIcon;					// +0x53c
	unsigned char m_unreconstructed_540[0x2E4];
	Int m_mouseMode;					// +0x824
	Int m_mouseModeCursor;					// +0x828
	unsigned char m_unreconstructed_82c[0x131C - 0x82C];
	BfmeIdleWorkerList m_idleWorkers[32];			// +0x131c
	GameWindow *m_idleWorkerWin;				// +0x139c
};

// ?destroyPlacementIcons@InGameUI@@IAEXXZ
// Retail 0x0043AF00, 71 bytes.
void InGameUI::destroyPlacementIcons()
{
	Drawable *icon = m_placeIcon[0];

	if (icon != 0) {
		TheTerrainVisual->removeFactionBibDrawable(icon);
		TheGameClient->destroyDrawable(m_placeIcon[0]);
	}

	m_placeIcon[0] = 0;
	TheTerrainVisual->removeAllBibs();
}

// ?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z
// Retail 0x0043AF60, 363 bytes.
void InGameUI::placeBuildAvailable(const ThingTemplate *build,
	Drawable *buildDrawable)
{
	if (build != 0)
		setRadiusCursorNone();

	if (m_pendingPlaceType != 0 && build != 0)
		placeBuildAvailable(0, 0);

	Object *sourceObject = 0;
	m_pendingPlaceType = build;
	m_pendingPlaceSourceObjectID = 0;
	if (buildDrawable != 0)
		sourceObject = buildDrawable->m_object;
	if (sourceObject != 0)
		m_pendingPlaceSourceObjectID = sourceObject->m_id;

	Mouse *mouse = *(Mouse **)0x012F4C5C;
	if (mouse == 0)
		return;

	if (build != 0)
	{
		m_mouseMode = 1;
		m_mouseModeCursor = Mouse::CROSS;
		(*(Mouse **)0x012F4C5C)->capture();

		mouse = *(Mouse **)0x012F4C5C;
		if (mouse != 0)
		{
			mouse->setCursor(Mouse::CROSS);
			if (m_mouseMode == 2)
				m_mouseModeCursor = Mouse::CROSS;
		}

		Drawable *draw = (*(BFMEThingFactory **)0x012EF1D8)->newDrawable(
			build, DRAWABLE_STATUS_NO_STATE_PARTICLES, -1);
		if (sourceObject != 0)
		{
			if ((*(GlobalData **)0x012ED5C8)->m_timeOfDay == 4)
				draw->setIndicatorColor(
					sourceObject->getControllingPlayer()->m_playerNightColor);
			else
				draw->setIndicatorColor(
					sourceObject->getControllingPlayer()->m_playerColor);
		}
		draw->setOrientation(build->m_placementViewAngle);
		draw->m_opacity = 0.45f;
		m_placeIcon[0] = draw;
	}
	else
	{
		if (m_mouseMode == 1)
		{
			m_mouseMode = 0;
			m_mouseModeCursor = Mouse::ARROW;
			mouse = *(Mouse **)0x012F4C5C;
		}
		mouse->releaseCapture();

		mouse = *(Mouse **)0x012F4C5C;
		if (mouse != 0)
			mouse->setCursor(Mouse::ARROW);

		setPlacementStart(0);
		destroyPlacementIcons();
	}
}

// ?getIdleWorkerCount@InGameUI@@EAEHXZ
// Retail 0x004422C0, 41 bytes.
Int InGameUI::getIdleWorkerCount()
{
	Int index = ThePlayerList->m_localPlayer->m_playerIndex;
	return m_idleWorkers[index].size();
}

// ?recreateControlBar@InGameUI@@UAEXXZ
// Retail 0x00442300, 279 bytes.
void InGameUI::recreateControlBar()
{
	GameWindow *window = TheWindowManager->winGetWindowFromId(
		0, TheNameKeyGenerator->nameToKey(
			AsciiString( "ControlBar.wnd" ).str() ) );
	if (window)
		window->deleteInstance( 1 );

	m_idleWorkerWin = 0;
	createControlBar();

	if (TheControlBar)
	{
		delete TheControlBar;
		TheControlBar = new ControlBar;
		TheControlBar->init();
	}
}
