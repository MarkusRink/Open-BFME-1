// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// readable body of ?setWidth@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
// readable body of ?setHeight@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
// readable body of ?setOrigin@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
//
// The three W3DView viewport setters. They are one operation split three ways
// -- setOrigin moves the viewport's corner and then calls setWidth and
// setHeight to re-derive the far edges -- and they were three files.
//
//   setWidth   0x0073DD00   vtable slot 14
//   setHeight               vtable slot 16
//   setOrigin  0x0073DE40   vtable slot 18
//
// They are lifted out of W3DView.cpp because that TU is compiled against the
// Zero Hour headers, where BFME's two extra View vtable entries and its 3D
// camera at +0x104 are both different. W3DView.cpp itself is an upstream file
// name and stays as it is.
//
// The vtable is the reason to merge them rather than the line count. Each file
// was free to guess the slots its own body does NOT call, and each guessed
// differently: setWidth's copy put setWidth at 18 and getHeight at 17,
// setOrigin's put setWidth at 14 and setOrigin at 17. Neither was wrong,
// because a definition does not pin its own slot -- only a CALL through the
// table pins anything. Taking each file's constrained pin and dropping its
// free guesses, the four calls agree completely:
//
//   14 setWidth   (called by setOrigin)
//   15 getWidth   (called by setHeight)
//   16 setHeight  (called by setOrigin)
//   17 getHeight  (called by setWidth)
//
// and setOrigin, which nothing here calls through the table, is declared after
// them rather than given a number of its own.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "wwmath.h"
#include "vector2.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class ViewportClass
{
public:
	ViewportClass(void) : Min(0, 0), Max(1, 1) {}
	ViewportClass(const Vector2 &min, const Vector2 &max) : Min(min), Max(max) {}
	ViewportClass(const ViewportClass &viewport) : Min(viewport.Min), Max(viewport.Max) {}

	Vector2 Min;
	Vector2 Max;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class CameraClass
{
public:
	void Set_Aspect_Ratio(float widthToHeight);
	void Set_View_Plane(float horizontalFov, float verticalFov);

	void Get_Viewport(Vector2 &setMin, Vector2 &setMax) const
	{
		setMin = Viewport.Min;
		setMax = Viewport.Max;
	}

	void Set_Viewport(const Vector2 &min, const Vector2 &max)
	{
		Viewport.Min = min;
		Viewport.Max = max;
		FrustumValid = false;
	}

	private:
	virtual void vtableAnchor();
	unsigned char m_padding04[0xCC - 0x04];
	ViewportClass Viewport;
	unsigned char m_paddingDC[0x100 - 0xDC];
	bool FrustumValid;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void d00() = 0;
	virtual void d01() = 0;
	virtual void d02() = 0;
	virtual void d03() = 0;
	virtual void d04() = 0;
	virtual void d05() = 0;
	virtual void d06() = 0;
	virtual void d07() = 0;
	virtual void d08() = 0;
	virtual void d09() = 0;
	virtual void d10() = 0;
	virtual UnsignedInt getWidth() = 0;			///< +0x2c
	virtual UnsignedInt getHeight() = 0;			///< +0x30
};

extern Display *TheDisplay;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
public:
	virtual void d00() = 0;
	virtual void d01() = 0;
	virtual void d02() = 0;
	virtual void d03() = 0;
	virtual void d04() = 0;
	virtual void d05() = 0;
	virtual void d06() = 0;
	virtual void d07() = 0;
	virtual void d08() = 0;
	virtual void d09() = 0;
	virtual void d10() = 0;
	virtual void d11() = 0;
	virtual void d12() = 0;
	virtual void d13() = 0;
	virtual void setWidth(Int width);			///< +0x38
	virtual Int getWidth() = 0;				///< +0x3c
	virtual void setHeight(Int height);			///< +0x40
	virtual Int getHeight() = 0;				///< +0x44
	// Not pinned by anything here: no body calls setOrigin through the table.
	virtual void setOrigin(Int x, Int y);

private:
	unsigned char m_padding04[0x14];
	Int m_width;						///< +0x18
	Int m_height;						///< +0x1c
	Int m_originX;						///< +0x20
	Int m_originY;						///< +0x24
	unsigned char m_padding28[0x104 - 0x28];
	CameraClass *m_3DCamera;				///< +0x104
};

// ?setWidth@W3DView@@UAEXH@Z
void W3DView::setWidth(Int width)
{
	m_width = width;

	Vector2 vMin, vMax;
	m_3DCamera->Set_Aspect_Ratio((Real)width / (Real)getHeight());
	m_3DCamera->Get_Viewport(vMin, vMax);
	vMax.X = (Real)(m_originX + width) / (Real)TheDisplay->getWidth();
	m_3DCamera->Set_Viewport(vMin, vMax);
	m_3DCamera->Set_View_Plane((Real)width / (Real)TheDisplay->getWidth() * DEG_TO_RADF(50.0f), -1);
}

// ?setHeight@W3DView@@UAEXH@Z
void W3DView::setHeight(Int height)
{
	m_height = height;

	Vector2 vMin,vMax;
	m_3DCamera->Set_Aspect_Ratio((Real)getWidth()/(Real)height);
 	m_3DCamera->Get_Viewport(vMin,vMax);
 	vMax.Y=(Real)(m_originY+height)/(Real)TheDisplay->getHeight();
 	m_3DCamera->Set_Viewport(vMin,vMax);
}

// ?setOrigin@W3DView@@UAEXHH@Z
void W3DView::setOrigin( Int x, Int y)
{
	m_originX = x;
	m_originY = y;

	Vector2 vMin,vMax;

 	m_3DCamera->Get_Viewport(vMin,vMax);
 	vMin.X=(Real)x/(Real)TheDisplay->getWidth();
	vMin.Y=(Real)y/(Real)TheDisplay->getHeight();
 	m_3DCamera->Set_Viewport(vMin,vMax);

	// bottom-right border was also moved my this call, so force an update of extents.
	setWidth(m_width);
	setHeight(m_height);
}
