class BfmeMemACA
{
public:
	~BfmeMemACA();

	unsigned char m_bfmeHeadCA[0xc];
};

class BfmeMemBCA
{
public:
	~BfmeMemBCA();

	unsigned char m_bfmeHeadCA[4];
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);

	unsigned char m_bfmeHeadCA[4];
};

class BfmeOwnCA : public SubsystemInterface
{
public:
	virtual ~BfmeOwnCA(void);
	virtual void bfmePureCA(void) = 0;

	void bfmeFreeCA(void);

	unsigned char m_bfmeMidCA[8];
	BfmeMemACA m_bfmeACA;
	BfmeMemBCA m_bfmeBCA;
};

BfmeOwnCA::~BfmeOwnCA(void)
{
	bfmeFreeCA();
}
