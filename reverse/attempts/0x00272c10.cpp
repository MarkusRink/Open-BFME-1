// ?chooseLocomotorSetExplicit@AIUpdateInterface@@AAE_NW4LocomotorSetType@@@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0
};

class LocomotorTemplate;

class LocomotorTemplateVector
{
public:
	char *m_start;
	char *m_finish;

	Int size() const { return (Int)((m_finish - m_start) >> 2); }
	const LocomotorTemplate *at(Int index) const
	{
		return ((const LocomotorTemplate **)m_start)[index];
	}
};

class AIUpdateModuleData;

class BfmeThingTemplate
{
public:
	BfmeThingTemplate *friend_getFinalOverride();
	const LocomotorTemplateVector *findLocomotorTemplateVector(LocomotorSetType type) const;

	char m_vtable[4];
	BfmeThingTemplate *m_nextOverride;
};

class BfmeObject
{
public:
	char m_vtable[4];
	BfmeThingTemplate *m_template;

	__forceinline BfmeThingTemplate *getTemplate() const
	{
		return *(BfmeThingTemplate **)((char *)this + 4);
	}
};

class LocomotorSet
{
public:
	void clear();
	void addLocomotor(const LocomotorTemplate *lt);

	char m_fields[0x24];
};

class AIUpdateInterface
{
	private:
	Bool chooseLocomotorSetExplicit(LocomotorSetType wst);
	__forceinline BfmeObject *getObject() const { return m_object; }

	char m_fields[8];
	BfmeObject *m_object;
	char m_fieldsBeforeLocomotorSet[0x1a8 - 0x0c];
	LocomotorSet m_locomotorSet;
	void *m_curLocomotor;
	LocomotorSetType m_curLocomotorSet;
};

Bool AIUpdateInterface::chooseLocomotorSetExplicit(LocomotorSetType wst)
{
	BfmeObject *object = getObject();
	BfmeThingTemplate **templateSlot = (BfmeThingTemplate **)((char *)object + 4);
	_ReadWriteBarrier();
	BfmeThingTemplate *sourceTemplate = *templateSlot;
	Int zero = 0;
	BfmeThingTemplate *thingTemplate = sourceTemplate;
	if (sourceTemplate != (BfmeThingTemplate *)0)
	{
		BfmeThingTemplate *nextOverride = sourceTemplate->m_nextOverride;
		if (nextOverride != (BfmeThingTemplate *)zero)
			thingTemplate = nextOverride->friend_getFinalOverride();
	}
	const LocomotorTemplateVector *set = thingTemplate->findLocomotorTemplateVector(wst);
	if (set)
	{
		m_locomotorSet.clear();
		m_curLocomotor = 0;
		for (Int i = 0; i < set->size(); ++i)
		{
			const LocomotorTemplate *lt = set->at(i);
			if (lt)
				m_locomotorSet.addLocomotor(lt);
		}
		m_curLocomotorSet = wst;
		return true;
	}
	return false;
}
