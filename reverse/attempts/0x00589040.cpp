// ?bfmeDrawEQ@@YAXHMMPBVBfmeVecEQ@@0@Z
// partial score=0.96 date=2026-09-08
extern const float g_bfmeK1257;

class BfmeVecEQ
{
public:
	float m_bfmeXEQ;
	float m_bfmeYEQ;
};

class Display
{
public:
	virtual void bfmeSlot0EQ();
	virtual void bfmeSlot1EQ();
	virtual void bfmeSlot2EQ();
	virtual void bfmeSlot3EQ();
	virtual void bfmeSlot4EQ();
	virtual void bfmeSlot5EQ();
	virtual void bfmeSlot6EQ();
	virtual void bfmeSlot7EQ();
	virtual void bfmeSlot8EQ();
	virtual void bfmeSlot9EQ();
	virtual void bfmeSlot10EQ();
	virtual void bfmeSlot11EQ();
	virtual void bfmeSlot12EQ();
	virtual void bfmeSlot13EQ();
	virtual void bfmeSlot14EQ();
	virtual void bfmeSlot15EQ();
	virtual void bfmeSlot16EQ();
	virtual void bfmeSlot17EQ();
	virtual void bfmeSlot18EQ();
	virtual void bfmeSlot19EQ();
	virtual void bfmeSlot20EQ();
	virtual void bfmeSlot21EQ();
	virtual void bfmeSlot22EQ();
	virtual void bfmeSlot23EQ();
	virtual void bfmeSlot24EQ();
	virtual void bfmeSlot25EQ();
	virtual void bfmeSlot26EQ();
	virtual void bfmeSlot27EQ();
	virtual void bfmeSlot28EQ();
	virtual void bfmeSlot29EQ();
	virtual void bfmeSlot30EQ();
	virtual void bfmeSlot31EQ();
	virtual void bfmeSlot32EQ();
	virtual void bfmeSlot33EQ();
	virtual void bfmeSlot34EQ();
	virtual void bfmeSlot35EQ();
	virtual void bfmeSlot36EQ();
	virtual void bfmeSlot37EQ();
	virtual void bfmeSlot38EQ();
	virtual void bfmeSlot39EQ();
	virtual void bfmeSlot40EQ();
	virtual void bfmeSlot41EQ();
	virtual void bfmeSlot42EQ();
	virtual void bfmeSlot43EQ();
	virtual void bfmeBeginEQ();
	virtual void bfmeSlot45EQ();
	virtual void bfmeSlot46EQ();
	virtual void bfmeSlot47EQ();
	virtual void bfmeSlot48EQ();
	virtual void bfmeSlot49EQ();
	virtual void bfmeSlot50EQ();
	virtual void bfmeSlot51EQ();
	virtual void bfmeSlot52EQ();
	virtual void bfmeLineEQ(int tag, float x1, float y1, float x2, float y2, int color, int width);
	virtual void bfmeSlot54EQ();
	virtual void bfmeEndEQ();
};

extern Display *TheDisplay;

void bfmeDrawEQ(int tag, float bx, float by, const BfmeVecEQ *v1, const BfmeVecEQ *v2)
{
	bx += (v1->m_bfmeXEQ - v2->m_bfmeXEQ) * g_bfmeK1257;

	by += (v1->m_bfmeYEQ - v2->m_bfmeYEQ) * g_bfmeK1257;

	float ey = by + v2->m_bfmeYEQ;
	float ex = bx + v2->m_bfmeXEQ;

	Display *d = TheDisplay;

	d->bfmeBeginEQ();
	d->bfmeLineEQ(tag, bx, by, ex, ey, -1, 2);
	d->bfmeEndEQ();
}
