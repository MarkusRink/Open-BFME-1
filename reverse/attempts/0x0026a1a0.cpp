// ?loadPostProcess@SpecialPowerModule@@MAEXXZ
// partial score=0.97 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc
// BFME retail layout reconstruction of SpecialPowerModule::loadPostProcess.

typedef unsigned char Bool;
typedef int Int;
typedef unsigned int ObjectID;
const Bool TRUE = 1;

#include "../../../../../../../reference/shims/stringinline/StringInline.h"

class SpecialPowerTemplate
{
public:
	const SpecialPowerTemplate *getFinalOverride() const
	{
		if (m_nextOverride != 0) {
			SpecialPowerTemplate *next = m_nextOverride;
			if (next->m_nextOverride != 0)
				return next->m_nextOverride->getFinalOverride();
			return next;
		}
		return this;
	}
	Bool hasPublicTimer() const { return getFinalOverride()->m_hasPublicTimer; }
	Bool isSharedNSync() const { return getFinalOverride()->m_sharedNSync; }

	void *m_vptr;
	SpecialPowerTemplate *m_nextOverride;
	unsigned char m_unmodelled[0x10c];
	Bool m_hasPublicTimer;
	Bool m_sharedNSync;
};

class SpecialPowerModuleData
{
public:
	unsigned char m_unmodelled[8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
	unsigned char m_unmodelled[0x24];
	Int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool isKindOf(Int kindOf) const;
	ObjectID getID() const { return m_id; }

	unsigned char m_unmodelled[0x74];
	ObjectID m_id;
};

class BehaviorModule
{
public:
	void loadPostProcess();
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10();
	virtual AsciiString getPowerName() const;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
};

class InGameUI
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4c(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6c(); virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7c(); virtual void slot80();
	virtual void addSuperweapon(Int playerIndex, const AsciiString &powerName,
		ObjectID objectID, const SpecialPowerTemplate *specialPowerTemplate);
};

extern InGameUI *TheInGameUI;

class SpecialPowerModule
{
protected:
	virtual void loadPostProcess();
	const SpecialPowerTemplate *getSpecialPowerTemplate() const
		{ return m_specialPowerInterface.getSpecialPowerTemplate(); }
	AsciiString getPowerName() const { return m_specialPowerInterface.getPowerName(); }
	Object *getObject() const { return m_object; }
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }

	SpecialPowerModuleData *m_moduleData;
	Object *m_object;
	void *m_unmodelled0c;
	SpecialPowerModuleInterface m_specialPowerInterface;
	unsigned int m_availableOnFrame;
	Int m_pausedCount;
};

void SpecialPowerModule::loadPostProcess()
{
	SpecialPowerModule *module = this;
	((BehaviorModule *)this)->loadPostProcess();

	if (module->m_pausedCount == 0 &&
		module->getSpecialPowerTemplate()->isSharedNSync() == TRUE &&
		module->getSpecialPowerTemplate()->hasPublicTimer() == TRUE &&
		module->getObject()->getControllingPlayer() != 0 &&
		module->getObject()->isKindOf(7))
	{
		TheInGameUI->addSuperweapon(
			module->getObject()->getControllingPlayer()->getPlayerIndex(),
			module->m_specialPowerInterface.getPowerName(), module->getObject()->getID(),
			module->getSpecialPowerModuleData()->m_specialPowerTemplate);
	}
}
