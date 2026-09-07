// ?doFXObj@LaserFXNugget@@UBEXPBVObject@@0@Z
// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of Laser's object dispatch.

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

struct Coord3D
{
	float x, y, z;
};

class Matrix3D;
class ThingTemplate;

class ClientUpdateModule
{
};

class AsciiString
{
private:
	char *m_text;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Drawable
{
public:
	ClientUpdateModule *findClientUpdateModule(NameKeyType key);
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class BFMEThingFactory : public ThingFactory
{
public:
	Drawable *newDrawable(const ThingTemplate *thingTemplate,
		DrawableStatus status, Int drawableID);
};

class DrawableForLaser;

#define BFME_OBJECT_SLOT( name ) virtual void name();
class Object
{
public:
	BFME_OBJECT_SLOT(v00) BFME_OBJECT_SLOT(v04)
	BFME_OBJECT_SLOT(v08) BFME_OBJECT_SLOT(v0C)
	BFME_OBJECT_SLOT(v10) BFME_OBJECT_SLOT(v14)
	BFME_OBJECT_SLOT(v18) BFME_OBJECT_SLOT(v1C)
	BFME_OBJECT_SLOT(v20) BFME_OBJECT_SLOT(v24)
	virtual Drawable *getDrawable() const;

public:
	unsigned char m_pad04[0x34];
	Coord3D m_position;
};
#undef BFME_OBJECT_SLOT

class LaserUpdate : public ClientUpdateModule
{
public:
	void initFromDrawables(void *a, Drawable *parent, Drawable *target, void *d);
	void initLaser(const Object *parent, const Coord3D *start,
		const Coord3D *end, Int sizeDeltaFrames);
};

class LaserFXNugget
{
public:
	virtual void v00();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float,
		const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	unsigned char m_unmodelled[0xB0];
	AsciiString m_laserName;
	bool m_laserBackwards;
	unsigned char m_padding[3];
	Coord3D m_targetPositionOffsetFallback;
};

// ?doFXObj@LaserFXNugget@@UBEXPBVObject@@0@Z
void LaserFXNugget::doFXObj(const Object *primary, const Object *secondary) const
{
	if (primary)
	{
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(m_laserName);
		Drawable *draw = ((BFMEThingFactory *)TheThingFactory)->newDrawable(
			thingTemplate, DRAWABLE_STATUS_NONE, -1);
		if (draw)
		{
			static NameKeyType key_LaserUpdate =
				TheNameKeyGenerator->nameToKey("LaserUpdate");
			LaserUpdate *update =
				(LaserUpdate *)draw->findClientUpdateModule(key_LaserUpdate);
			if (update)
			{
				if (secondary)
				{
					update->initFromDrawables((void *)primary,
						primary->getDrawable(), secondary->getDrawable(), 0);
				}
				else
				{
					Coord3D position;
					position.x = primary->m_position.x;
					position.y = primary->m_position.y;
					position.z = primary->m_position.z;
					position.x += m_targetPositionOffsetFallback.x;
					position.y += m_targetPositionOffsetFallback.y;
					position.z += m_targetPositionOffsetFallback.z;
					if (!m_laserBackwards)
					{
						update->initLaser(primary, &primary->m_position,
							&position, 0);
					}
					else
					{
						update->initLaser(primary, &position,
							&primary->m_position, 0);
					}
				}
			}
		}
	}
}
