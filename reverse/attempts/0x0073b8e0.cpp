// ?bfmeAdjustEW@BfmeHostEW@@QAEXPAVBfmeVec2EW@@@Z
// partial score=0.95 date=2026-09-08
extern const float g_bfmeScaleEW;

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

class BfmeVec2EW
{
public:
	float m_bfmeXEW;
	float m_bfmeYEW;
};

class BfmeSubEW
{
public:
	virtual void bfmeSlot0EW();
	virtual void bfmeSlot1EW();
	virtual void bfmeSlot2EW();
	virtual void bfmeSlot3EW();
	virtual void bfmeSlot4EW();
	virtual void bfmeSlot5EW();
	virtual void bfmeSlot6EW();
	virtual void bfmeSlot7EW();
	virtual void bfmeSlot8EW();
	virtual void bfmeSlot9EW();
	virtual void bfmeSlot10EW();
	virtual void bfmeSlot11EW();
	virtual void bfmeSlot12EW();
	virtual void bfmeSlot13EW();
	virtual void bfmeSlot14EW();
	virtual void bfmeSlot15EW();
	virtual void bfmeSlot16EW();
	virtual void bfmeSlot17EW();
	virtual void bfmeSlot18EW();
	virtual void bfmeSlot19EW();
	virtual void bfmeSlot20EW();
	virtual void bfmeApplyEW(BfmeVec2EW *p);
};

class BfmeHostEW
{
public:
	void bfmeAdjustEW(BfmeVec2EW *p);

	unsigned char m_bfmeHeadEW[0xc];
	float m_bfmeXEW;
	float m_bfmeYEW;
	unsigned char m_bfmeGap0EW[0x30];
	unsigned char m_bfmeFlagEW;
	unsigned char m_bfmeGap1EW[0xbf];
	RenderObjClass *m_bfmeRenderEW;
	unsigned char m_bfmeGap2EW[0x23b0];
	BfmeSubEW m_bfmeSubEW;
};

void BfmeHostEW::bfmeAdjustEW(BfmeVec2EW *p)
{
	if (m_bfmeFlagEW)
	{
		Vector3 pos = m_bfmeRenderEW->Get_Position();

		float a = *(const volatile float *)&m_bfmeXEW;
		float b = *(const volatile float *)&m_bfmeYEW;

		pos.Z = 0.0f;

		volatile float rx = pos.X - a;
		float ry = pos.Y - b;

		float dx = rx * g_bfmeScaleEW;
		float dy = ry * g_bfmeScaleEW;

		p->m_bfmeXEW += dx;
		p->m_bfmeYEW += dy;

		m_bfmeSubEW.bfmeApplyEW(p);

		p->m_bfmeXEW -= dx;
		p->m_bfmeYEW -= dy;
	}
}
