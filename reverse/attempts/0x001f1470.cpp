// ??0BezierProjectileBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.52 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: BezierProjectileBehavior module constructor.  The named factory
// proves the identity; its destructor fixes the vector at +0x44 and list at
// +0x7c.  Field initialization follows the original projectile source.

#include <list>
#include <vector>

class Thing;
class ModuleData;
class Object;

class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual void moduleSlot() = 0;
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot() = 0; };
class UpdateModuleInterface { public: virtual void updateSlot() = 0; };

class UpdateModuleState
{
public:
	UpdateModuleState()
	{
		m_indexInLogic = -1;
		m_updateState = -1;
		m_nextCallFrameAndPhase = 0;
	}
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface,
	public UpdateModuleInterface, public UpdateModuleState
{
public:
	UpdateModule(Thing *thing, const ModuleData *data) : ObjectModule(thing, data) {}
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *, unsigned int);
};

template <int Number>
class BezierProjectileInterface { public: virtual void slot() = 0; };

struct Coord3D
{
	void zero() { x = 0; y = 0; z = 0; }
	unsigned int x, y, z;
};

class BezierProjectileBehavior : public UpdateModule,
	public BezierProjectileInterface<1>, public BezierProjectileInterface<2>
{
public:
	BezierProjectileBehavior(Thing *, const ModuleData *);
private:
	unsigned int m_launcherID;
	unsigned int m_victimID;
	void *m_detonationWeaponTmpl;
	unsigned int m_lifespanFrame;
	unsigned int m_38;
	unsigned int m_3c;
	unsigned int m_40;
	_STL::vector<Coord3D> m_flightPath;
	Coord3D m_flightPathStart;
	Coord3D m_flightPathEnd;
	unsigned int m_flightPathSpeed;
	unsigned int m_flightPathSegments;
	unsigned int m_currentFlightPathStep;
	unsigned int m_extraBonusFlags;
	unsigned int m_78;
	_STL::list<int> m_list;
	bool m_hasDetonated;
	unsigned char m_pad81[3];
	float m_scale;
};

// ??0BezierProjectileBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
BezierProjectileBehavior::BezierProjectileBehavior(Thing *thing, const ModuleData *data)
	: UpdateModule(thing, data),
	  m_flightPath(_STL::allocator<Coord3D>()),
	  m_list(_STL::allocator<int>())
{
	m_launcherID = 0;
	m_victimID = 0;
	m_detonationWeaponTmpl = 0;
	m_lifespanFrame = 0;
	m_38 = 0;
	m_3c = 0;
	m_40 = 0;
	m_flightPath.clear();
	m_flightPathSegments = 0;
	m_flightPathSpeed = 0;
	m_flightPathStart.zero();
	m_flightPathEnd.zero();
	m_currentFlightPathStep = 0;
	m_extraBonusFlags = 0;
	m_hasDetonated = false;
	m_78 = 0;
	m_scale = 1.0f;
	setWakeFrame(getObject(), 0x3fffffff);
}
