// ?d_005204f0@@YAXXZ
// partial score=0.75 date=2026-09-07
// ?d_005204f0@@YAXXZ

struct Coord2D
{
	float x;
	float y;
};

class Image
{
public:
	virtual void release(int count);
};

class Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void beginImageDraw();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void drawImageCore(Image *image, float x0, float y0,
		float x1, float y1, int color, int mode);
	virtual void slotD8();
	virtual void endImageDraw();
};

extern Display *TheDisplay;
extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(
	const void *address, unsigned long size);

class Gen005207C0Member
{
public:
	void drawImage(const Coord2D &position, const Coord2D &size,
		int unused1, int unused2);

private:
	char m_unmodelled[0x34];
	Image *m_field34;
};

void Gen005207C0Member::drawImage(const Coord2D &position,
	const Coord2D &size, int unused1, int unused2)
{
	register Gen005207C0Member *self = this;
	if (self->m_field34 == 0)
		return;
	if (IsBadReadPtr(self->m_field34, 0x34))
	{
		self->m_field34 = 0;
		return;
	}

	float endY = size.y + position.y;
	float startX = position.x;
	float endX = position.x + size.x;
	float startY = position.y;
	Image *image = self->m_field34;
	Display *display = TheDisplay;
	TheDisplay->beginImageDraw();
	display->drawImageCore(image, startX, startY, endX, endY, -1, 2);
	display->endImageDraw();
}
