// cl: /DNDEBUG /MD
// Retail 0x002EDE20 is ScriptActions::doModCameraMoveToSelection.  The
// executeAction dispatch names this camera action, and the body walks the
// GameClient drawable list before calling View::cameraModFinalMoveTo.

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D(void) {}

	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
};

class Drawable
{
public:
	Drawable *getNextDrawable(void) const
	{
		return *(Drawable **)((char *)this + 0x104);
	}

	Bool isSelected(void) const
	{
		return *(const unsigned char *)((const char *)this + 0x3ac) != 0;
	}

	const Coord3D *getPosition(void) const;
};

class ClientRoot4120
{
public:
	virtual void _gc_0(void) = 0;
	virtual void _gc_1(void) = 0;
	virtual void _gc_2(void) = 0;
	virtual void _gc_3(void) = 0;
	virtual void _gc_4(void) = 0;
	virtual void _gc_5(void) = 0;
	virtual void _gc_6(void) = 0;
	virtual void _gc_7(void) = 0;
	virtual void _gc_8(void) = 0;
	virtual void _gc_9(void) = 0;
	virtual void _gc_10(void) = 0;
	virtual void _gc_11(void) = 0;
	virtual Drawable *firstDrawable(void) = 0;
};

class View
{
public:
	virtual void _view_0(void) = 0;
	virtual void _view_1(void) = 0;
	virtual void _view_2(void) = 0;
	virtual void _view_3(void) = 0;
	virtual void _view_4(void) = 0;
	virtual void _view_5(void) = 0;
	virtual void _view_6(void) = 0;
	virtual void _view_7(void) = 0;
	virtual void _view_8(void) = 0;
	virtual void _view_9(void) = 0;
	virtual void _view_10(void) = 0;
	virtual void _view_11(void) = 0;
	virtual void _view_12(void) = 0;
	virtual void _view_13(void) = 0;
	virtual void _view_14(void) = 0;
	virtual void _view_15(void) = 0;
	virtual void _view_16(void) = 0;
	virtual void _view_17(void) = 0;
	virtual void _view_18(void) = 0;
	virtual void _view_19(void) = 0;
	virtual void _view_20(void) = 0;
	virtual void _view_21(void) = 0;
	virtual void _view_22(void) = 0;
	virtual void _view_23(void) = 0;
	virtual void _view_24(void) = 0;
	virtual void _view_25(void) = 0;
	virtual void _view_26(void) = 0;
	virtual void _view_27(void) = 0;
	virtual void _view_28(void) = 0;
	virtual void _view_29(void) = 0;
	virtual void _view_30(void) = 0;
	virtual void _view_31(void) = 0;
	virtual void _view_32(void) = 0;
	virtual void _view_33(void) = 0;
	virtual void _view_34(void) = 0;
	virtual void _view_35(void) = 0;
	virtual void _view_36(void) = 0;
	virtual void _view_37(void) = 0;
	virtual void cameraModFinalMoveTo(Coord3D *location) = 0;
};

extern ClientRoot4120 *TheGameClient;
extern View *TheTacticalView;

class ScriptActions
{
protected:
	void doModCameraMoveToSelection(void);
};

// ?doModCameraMoveToSelection@ScriptActions@@IAEXXZ
void ScriptActions::doModCameraMoveToSelection(void)
{
	Int count = 0;
	Coord3D destination;
	destination.x = destination.y = destination.z = 0;

	for (Drawable *draw = TheGameClient->firstDrawable(); draw; draw = draw->getNextDrawable())
	{
		if (draw->isSelected())
		{
			Coord3D position = *draw->getPosition();
			destination.x += position.x;
			destination.y += position.y;
			destination.z += position.z;
			count++;
		}
	}

	if (count)
	{
		destination.z /= count;
		destination.x /= count;
		destination.y /= count;
		TheTacticalView->cameraModFinalMoveTo(&destination);
	}
}
