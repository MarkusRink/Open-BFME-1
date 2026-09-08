// ?friend_bindToObject@Drawable@@QAEXPAVObject@@@Z
// partial score=0.82 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /MD /EHs-c-

typedef unsigned int UnsignedInt;

class Object
{
public:
	int getNightIndicatorColor() const;
	int getIndicatorColor() const;
};

class DrawModule
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void onDrawableBoundToObject() = 0;
};

struct BfmeGameLogicIndicatorFields
{
	unsigned char m_pad00[0x180];
	unsigned char m_indicatorOverride;
	unsigned char m_pad181[3];
	UnsignedInt m_indicatorColor;
};

struct BfmeGlobalIndicatorFields
{
	unsigned char m_pad00[0x218];
	UnsignedInt m_timeOfDay;
};

class Drawable
{
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
	virtual void drawableBoundToObject() = 0;

	unsigned char m_pad00[0xf8];
	Object *m_object;
	unsigned char m_pad100[0x50];
	DrawModule **m_drawModules;

public:
	void setIndicatorColor(UnsignedInt color);
	void friend_bindToObject(Object *obj);
};

void Drawable::friend_bindToObject(Object *obj)
{
	m_object = obj;
	if (obj)
	{
		const BfmeGameLogicIndicatorFields *logic =
			*(const BfmeGameLogicIndicatorFields **)0x012F0898;
		UnsignedInt color;
		if (logic->m_indicatorOverride == 1)
			color = logic->m_indicatorColor;
		else if (((const BfmeGlobalIndicatorFields *)*(const void **)0x012ED5C8)->m_timeOfDay == 4)
			color = obj->getNightIndicatorColor();
		else
			color = obj->getIndicatorColor();
		setIndicatorColor(color);
	}

	for (DrawModule **dm = m_drawModules; *dm; ++dm)
		(*dm)->onDrawableBoundToObject();
	drawableBoundToObject();
}
