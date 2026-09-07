// ?d_004945e0@@YAXXZ
// partial score=0.98 date=2026-09-08
extern "C" void *bfmeVftEAJ[];

class SubsystemInterface
{
public:
	SubsystemInterface();

	void *volatile m_bfmeVftEAJ;
	int m_bfmeBaseEAJ;
};

class BfmeOwnedEAJ : public SubsystemInterface
{
public:
	BfmeOwnedEAJ(void *param);

	int m_bfmeAEAJ;
	int m_bfmeBEAJ;
	int m_bfmeCEAJ;
	int m_bfmeDEAJ;
	int m_bfmeEEAJ;
	int m_bfmeFEAJ;
	char m_bfmeFlagsEAJ;
	unsigned char m_bfmePadEAJ[3];
	int m_bfmeGEAJ;
	int m_bfmeHEAJ;
	int m_bfmeIEAJ;
	void *m_bfmeParamEAJ;
	int m_bfmeJEAJ;
};

BfmeOwnedEAJ::BfmeOwnedEAJ(void *param)
{
	m_bfmeFlagsEAJ = (char)(*(volatile char *)&m_bfmeFlagsEAJ & 0xf8);

	m_bfmeAEAJ = 0;
	m_bfmeFEAJ = 0;
	m_bfmeHEAJ = 0;
	m_bfmeIEAJ = 0;
	m_bfmeJEAJ = 0;
	m_bfmeBEAJ = 0;
	m_bfmeCEAJ = 0;
	m_bfmeDEAJ = 0;
	m_bfmeEEAJ = 0;

	m_bfmeVftEAJ = bfmeVftEAJ;

	m_bfmeGEAJ = -1;
	m_bfmeParamEAJ = param;
}
