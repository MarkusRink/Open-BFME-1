// ??0SupplyTruckAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.95 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SupplyTruckAIUpdate constructor.  The factory, matched
// destructor and original source fix the AI interface and member layout.

class Thing;
class ModuleData;
class Object;

class BehaviorModule
{
public: virtual void slot();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

template <int Number> class __declspec(novtable) SupplyTruckIface { public: virtual void slot() = 0; };
class __declspec(novtable) SupplyTruckWideIface
{
public: virtual void slot() = 0;
private: unsigned int m_14, m_18, m_1c;
};
class __declspec(novtable) SupplyTruckPaddedIface
{
public: virtual void slot() = 0;
private: unsigned char m_pad[0x318];
};
class SupplyTruckAIInterface
{
public:
	virtual ~SupplyTruckAIInterface();
	virtual void slot();
};

class AnimalAIUpdateBase : public BehaviorModule
{
public:
	AnimalAIUpdateBase(Thing *, const ModuleData *);
	Object *getObject() const { return m_object; }
};

class AsciiString {};
extern const AsciiString Rva01336E50Str;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &, int);
	virtual ~AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &);
private:
	unsigned char m_pad[0x6c];
};

class SupplyTruckStateMachine
{
public:
	SupplyTruckStateMachine(Object *);
	virtual ~SupplyTruckStateMachine();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void initDefaultState();
private:
	unsigned char m_pad[0x40];
};

class SupplyTruckAIUpdateModuleData
{
private:
	unsigned char m_pad[0x84];
public:
	AudioEventRTS m_suppliesDepletedVoice;
};

class SupplyTruckAIUpdate : public AnimalAIUpdateBase,
	public SupplyTruckIface<1>, public SupplyTruckWideIface,
	public SupplyTruckIface<2>, public SupplyTruckPaddedIface,
	public SupplyTruckAIInterface
{
public:
	SupplyTruckAIUpdate(Thing *, const ModuleData *);
	virtual ~SupplyTruckAIUpdate();
private:
	SupplyTruckStateMachine *m_supplyTruckStateMachine;
	unsigned int m_preferredDock;
	unsigned int m_numberBoxes;
	unsigned int m_value350;
	unsigned int m_value354;
	bool m_flag358;
	unsigned char m_pad359[3];
	unsigned int m_value35c;
	bool m_forcePending;
	bool m_forcedBusyPending;
	unsigned char m_pad362[2];
	AudioEventRTS m_suppliesDepletedVoice;
};

// ??0SupplyTruckAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SupplyTruckAIUpdate::SupplyTruckAIUpdate(Thing *thing, const ModuleData *data)
	: AnimalAIUpdateBase(thing, data), m_suppliesDepletedVoice(Rva01336E50Str, 0)
{
	m_supplyTruckStateMachine = 0;
	m_preferredDock = 0;
	m_numberBoxes = 0;
	m_value350 = 0;
	m_value354 = 0;
	m_flag358 = false;
	m_value35c = 0;
	m_forcePending = false;
	m_forcedBusyPending = false;
	m_supplyTruckStateMachine = new SupplyTruckStateMachine(getObject());
	m_supplyTruckStateMachine->initDefaultState();
	const SupplyTruckAIUpdateModuleData *moduleData =
		(const SupplyTruckAIUpdateModuleData *)m_moduleData;
	m_suppliesDepletedVoice = moduleData->m_suppliesDepletedVoice;
}
