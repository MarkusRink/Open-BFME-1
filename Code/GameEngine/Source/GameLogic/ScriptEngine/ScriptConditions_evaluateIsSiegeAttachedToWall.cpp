// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ScriptConditions::evaluateIsSiegeAttachedToWall at retail RVA 0x003237F0.

typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Parameter;
class Module;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual class Object *getUnitNamed(Parameter *name) = 0;
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;
};

class SiegeDeploySpecialPower
{
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_00048112();

static __forceinline Bool isSiegeAttached(SiegeDeploySpecialPower *module)
{
	typedef Bool (SiegeDeploySpecialPower::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00048112;
	return (reinterpret_cast<SiegeDeploySpecialPower *>(module)->*fn.member)();
}

class ScriptConditions
{
protected:
	Bool evaluateIsSiegeAttachedToWall(Parameter *unitParm);
};

// ?evaluateIsSiegeAttachedToWall@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateIsSiegeAttachedToWall(Parameter *unitParm)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitParm);
	if (unit)
	{
		static NameKeyType key =
			TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
		Module *module = unit->findModule(key);
		if (module)
			return isSiegeAttached((SiegeDeploySpecialPower *)module);
	}
	return false;
}
