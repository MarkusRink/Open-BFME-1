// ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
// partial score=0.55 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Clean C++ recovery of ScriptActions::doMoveCameraTo.
// Retail RVA 0x002F24F0 (186 bytes), executeAction MOVE_CAMERA_TO arm 14.
// BFME resolves a waypoint first and then lets the tactical view's named
// camera-marker list override its position when one has the same name.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	float x;
	float y;
	float z;
};

// The by-value TerrainLogic argument is the one-word BFME string view.  Its
// copy constructor is the shared StringBase<char> body at 0x00887B60.
class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}

	~BfmeAsciiStringArg();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
	public:
	unsigned char m_beforeLocation[0x0c];
	Coord3D m_location;
	const Coord3D *getLocation() const { return &m_location; }
};

class TerrainLogic
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual Waypoint *getWaypointByName(BfmeAsciiStringArg name) = 0;
};

struct CameraMarker
{
	CameraMarker *m_next;
	AsciiString m_name;
	Coord3D m_position;
};

// The returned marker is owned by the list embedded in View at +0x80.  This
// declaration reuses the already matched find body; the resolver selects its
// retail incremental-link thunk at 0x00036A43 for this call site.
class CameraMarkerList
{
private:
	unsigned char m_beforeMarkers[0x80];
	CameraMarker *m_markers;

public:
	CameraMarker *find(const AsciiString &name) const;
};

// View's slot +0x60 has the BFME marker-aware ABI: the marker itself is the
// second argument, followed by the scaled duration and the two ease values.
class View
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void moveCameraTo(const Coord3D *position,
		CameraMarker *marker, Int milliseconds, Bool snap,
		Real easeIn, Real easeOut) = 0;
};

extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;

class ScriptActions
{
protected:
	void doMoveCameraTo(const AsciiString &, Real, Real, Real, Real);
};

// ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
void ScriptActions::doMoveCameraTo(const AsciiString &name, Real seconds,
	Real, Real easeIn, Real easeOut)
{
	const AsciiString *namePointer = &name;
	CameraMarker *marker;
	Waypoint *waypoint = TheTerrainLogic->getWaypointByName(*namePointer);

	marker =
		((CameraMarkerList *)TheTacticalView)->find(*namePointer);

	Coord3D destination;
	if (waypoint == 0 && marker == 0)
		return;
	if (waypoint != 0)
	{
		const Coord3D *location = waypoint->getLocation();
		destination = *location;
	}

	if (marker != 0)
	{
		const Coord3D *position = &marker->m_position;
		destination = *position;
	}

	TheTacticalView->moveCameraTo(&destination, marker,
		(Int)(seconds * *(const Real *)0x01075c68), true,
		easeIn * *(const Real *)0x01075c68,
		easeOut * *(const Real *)0x01075c68);
}
