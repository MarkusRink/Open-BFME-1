// ?bfmeDrawAAQ@@YGXHHHHHH@Z
// partial score=0.96 date=2026-09-08
class Display
{
public:
	virtual void bfmeSlot0AAQ();
	virtual void bfmeSlot1AAQ();
	virtual void bfmeSlot2AAQ();
	virtual void bfmeSlot3AAQ();
	virtual void bfmeSlot4AAQ();
	virtual void bfmeSlot5AAQ();
	virtual void bfmeSlot6AAQ();
	virtual void bfmeSlot7AAQ();
	virtual void bfmeSlot8AAQ();
	virtual void bfmeSlot9AAQ();
	virtual void bfmeSlot10AAQ();
	virtual void bfmeSlot11AAQ();
	virtual void bfmeSlot12AAQ();
	virtual void bfmeSlot13AAQ();
	virtual void bfmeSlot14AAQ();
	virtual void bfmeSlot15AAQ();
	virtual void bfmeSlot16AAQ();
	virtual void bfmeSlot17AAQ();
	virtual void bfmeSlot18AAQ();
	virtual void bfmeSlot19AAQ();
	virtual void bfmeSlot20AAQ();
	virtual void bfmeSlot21AAQ();
	virtual void bfmeSlot22AAQ();
	virtual void bfmeSlot23AAQ();
	virtual void bfmeSlot24AAQ();
	virtual void bfmeSlot25AAQ();
	virtual void bfmeSlot26AAQ();
	virtual void bfmeSlot27AAQ();
	virtual void bfmeSlot28AAQ();
	virtual void bfmeSlot29AAQ();
	virtual void bfmeSlot30AAQ();
	virtual void bfmeSlot31AAQ();
	virtual void bfmeSlot32AAQ();
	virtual void bfmeSlot33AAQ();
	virtual void bfmeSlot34AAQ();
	virtual void bfmeSlot35AAQ();
	virtual void bfmeSlot36AAQ();
	virtual void bfmeSlot37AAQ();
	virtual void bfmeSlot38AAQ();
	virtual void bfmeSlot39AAQ();
	virtual void bfmeSlot40AAQ();
	virtual void bfmeSlot41AAQ();
	virtual void bfmeSlot42AAQ();
	virtual void bfmeSlot43AAQ();
	virtual void bfmeBeginAAQ();
	virtual void bfmeSlot45AAQ();
	virtual void bfmeSlot46AAQ();
	virtual void bfmeRectAAQ(float l, float t, float w, float h, int a, int b);
	virtual void bfmeSlot48AAQ();
	virtual void bfmeSlot49AAQ();
	virtual void bfmeSlot50AAQ();
	virtual void bfmeSlot51AAQ();
	virtual void bfmeSlot52AAQ();
	virtual void bfmeSlot53AAQ();
	virtual void bfmeSlot54AAQ();
	virtual void bfmeEndAAQ();
};

extern Display *TheDisplay;

void __stdcall bfmeDrawAAQ(int a0, int a1, int a2, int a3, int a4, int a5);

void __stdcall bfmeDrawAAQ(int a0, int a1, int a2, int a3, int a4, int a5)
{
	Display *d = TheDisplay;

	d->bfmeBeginAAQ();
	d->bfmeRectAAQ((float)a2, (float)a3, (float)(a4 - a2), (float)(a5 - a3), a1, a0);
	d->bfmeEndAAQ();
}
