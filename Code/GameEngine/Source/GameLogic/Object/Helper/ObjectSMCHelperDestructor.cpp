// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>

class Thing;
class ModuleData;

class ObjectHelper
{
public:
	ObjectHelper(Thing *, const ModuleData *);
	virtual ~ObjectHelper();

private:
	unsigned char m_base[0x8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

struct Gen_p8pod
{
	unsigned int m_condition;
	unsigned int m_frame;
};

class ObjectSMCHelper : public ObjectHelper,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	virtual ~ObjectSMCHelper();

private:
	unsigned char m_padding[0xc];
	_STL::list<Gen_p8pod> m_timers;
};

// ??1ObjectSMCHelper@@UAE@XZ
ObjectSMCHelper::~ObjectSMCHelper()
{
	m_timers.clear();
}
