// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2

struct Region3D_003D2E00
{
	float m_loX;
	float m_loY;
	float m_loZ;
	float m_hiX;
	float m_hiY;
	float m_hiZ;
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void getBounds(Region3D_003D2E00 *bounds) = 0;
};

extern TerrainLogic *TheTerrainLogic;

class Rva003D2E00Element
{
public:
	void update(Region3D_003D2E00 *bounds);
};

#pragma comment(linker, "/alternatename:?update@Rva003D2E00Element@@QAEXPAURegion3D_003D2E00@@@Z=?j_0002588d@@YAXXZ")

class Rva003D2E00
{
public:
	void call();

private:
	unsigned char m_pad00[0x18];
	Rva003D2E00Element **m_begin;
	Rva003D2E00Element **m_end;
	unsigned char m_pad20[0x78];
	float m_loX;
	float m_loY;
	float m_hiX;
	float m_hiY;
};

// ?call@Rva003D2E00@@QAEXXZ
void Rva003D2E00::call()
{
	Region3D_003D2E00 bounds;
	TheTerrainLogic->getBounds(&bounds);

	if (bounds.m_hiX != m_hiX
		|| bounds.m_hiY != m_hiY
		|| bounds.m_loX != m_loX
		|| bounds.m_loY != m_loY)
	{
		m_hiX = bounds.m_hiX;
		m_hiY = bounds.m_hiY;
		m_loX = bounds.m_loX;
		m_loY = bounds.m_loY;

		for (Rva003D2E00Element **it = m_begin; it != m_end; ++it)
			(*it)->update(&bounds);
	}
}
