// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RousingSpeechUpdate::onObjectCreated, retail 0x00264EA0.
// The RousingSpeechUpdate vtable at 0x010B6D90 routes slot 13 through ILT
// 0x000211DE to this body.  Its base onObjectCreated call uses ILT 0x00020AF9.

class RousingObject
{
public:
	void notifyModelConditionChanged();

private:
	unsigned char m_pad[0x128];

public:
	union
	{
		unsigned int m_modelConditionFlags;
		unsigned char m_modelConditionFlagsByte;
	};
};

class RousingFXList
{
public:
	void doFXObj(const RousingObject *primary, const RousingObject *secondary) const;
};

class RousingThingCOF
{
public:
	bool bfmeAskCOF();
};

class RousingSpeechUpdateModuleData
{
private:
	unsigned char m_pad00[0x254];

public:
	float m_animationFrames;

private:
	unsigned char m_pad258[8];

public:
	RousingFXList *m_fxList;

private:
	unsigned char m_pad264[4];

public:
	unsigned char m_hasAnimationFrames;

private:
	unsigned char m_pad269[3];

public:
	float m_animationFrameLimit;
};

class RousingSpeechUpdateBase
{
	virtual void onObjectCreated();

protected:
	RousingSpeechUpdateModuleData *m_moduleData;
	RousingObject *m_object;
	unsigned char m_pad0c[0xe8];

	unsigned int m_unused;
	float m_animationFrames;
};

class RousingSpeechUpdate : public RousingSpeechUpdateBase
{
public:
	virtual void onObjectCreated();
};

extern void j_00020af9();
extern void j_0002191d();
extern void j_00022bba();
extern void j_00011f77();

void RousingSpeechUpdate::onObjectCreated()
{
	j_00020af9();

	RousingObject *object = m_object;
	if ((object->m_modelConditionFlagsByte & 0x10) == 0)
	{
		object->m_modelConditionFlags |= 0x10;
		typedef void (RousingObject::*NotifyCall)();
		union { void *asVoid; NotifyCall asMember; } notifyCast;
		notifyCast.asVoid = (void *)j_0002191d;
		(object->*notifyCast.asMember)();
	}

	RousingSpeechUpdateModuleData *data = m_moduleData;
	RousingFXList *fxList = data->m_fxList;
	if (fxList != 0)
	{
		RousingObject *fxObject = m_object;
		RousingThingCOF *cof = reinterpret_cast<RousingThingCOF *>(fxList);
		typedef bool (RousingThingCOF::*AskCall)();
		union { void *asVoid; AskCall asMember; } askCast;
		askCast.asVoid = (void *)j_00011f77;
		if (!(cof->*askCast.asMember)())
		{
			typedef void (RousingFXList::*FXCall)(const RousingObject *, const RousingObject *) const;
			union { void *asVoid; FXCall asMember; } fxCast;
			fxCast.asVoid = (void *)j_00022bba;
			(fxList->*fxCast.asMember)(fxObject, 0);
		}
	}

	m_unused = 0;
	if (data->m_hasAnimationFrames)
	{
		m_animationFrames = data->m_animationFrameLimit;
		if (m_animationFrames > data->m_animationFrames)
			m_animationFrames = data->m_animationFrames;
	}
	else
	{
		m_animationFrames = data->m_animationFrames;
	}
}
