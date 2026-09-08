// ??4BfmeRefXI@@QAEAAV0@ABV0@@Z
// partial score=0.97 date=2026-09-08
// pin needed: ?bfmeAssignXI@BfmeSubXI@@QAEXABV1@@Z,0x0000FF29
class BfmeObjXI
{
public:
	virtual void bfmeReleaseXI(int deleting) = 0;
	virtual BfmeObjXI *bfmeAddRefXI() = 0;
};

class BfmeSubXI
{
public:
	void bfmeAssignXI(const BfmeSubXI &o);

	unsigned char m_bfmeHeadXI[4];
};

class BfmeRefXI
{
public:
	BfmeRefXI &operator=(const BfmeRefXI &o);

	BfmeObjXI *m_bfmePtrXI;
	BfmeSubXI m_bfme04XI;
};

BfmeRefXI &BfmeRefXI::operator=(const BfmeRefXI &o)
{
	BfmeObjXI *n;

	if (o.m_bfmePtrXI)
		n = o.m_bfmePtrXI->bfmeAddRefXI();
	else
		n = 0;

	if (m_bfmePtrXI)
		m_bfmePtrXI->bfmeReleaseXI(1);

	m_bfmePtrXI = n;
	m_bfme04XI.bfmeAssignXI(o.m_bfme04XI);

	return *this;
}
