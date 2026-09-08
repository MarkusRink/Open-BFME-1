// ?bfmeResetXV@BfmeHostXV@@QAEXXZ
// partial score=0.98 date=2026-09-08
// pin needed: ??1BfmeElemXV@@QAE@XZ,0x0000CA68
class BfmeElemXV
{
public:
	~BfmeElemXV();
};

class BfmeHostXV
{
public:
	void bfmeResetXV();

	unsigned char m_bfmeHeadXV[0x18];
	BfmeElemXV *m_bfme18XV;
	int m_bfme1CXV;
	int m_bfme20XV;
	int m_bfme24XV;
	float m_bfme28XV;
	int m_bfme2CXV;
	int m_bfme30XV;
};

void BfmeHostXV::bfmeResetXV()
{
	if (m_bfme18XV)
	{
		delete m_bfme18XV;

		m_bfme18XV = 0;
		m_bfme1CXV = 0;
		m_bfme20XV = 0;
		m_bfme24XV = 0;
		m_bfme28XV = 10.0f;
		m_bfme2CXV = 0;
		m_bfme30XV = 0;
	}
}
