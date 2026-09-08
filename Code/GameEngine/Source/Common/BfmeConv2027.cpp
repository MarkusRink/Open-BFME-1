extern "C" double sin(double x);
extern "C" double cos(double x);

#pragma intrinsic(sin, cos)

class BfmeMtxTX
{
public:
	void bfmeRotateXTX(float theta);

	unsigned char m_bfmeHeadTX[0xc0];
	volatile float m_bfmeRowTX[3][4];
	unsigned char m_bfmePadTX[0xb4];
	volatile unsigned char m_bfmeDirtyTX;
};

void BfmeMtxTX::bfmeRotateXTX(float theta)
{
	float s = (float)sin(theta);
	float c = (float)cos(theta);
	float tmp1;
	float tmp2;

	tmp1 = m_bfmeRowTX[0][1];
	tmp2 = m_bfmeRowTX[0][2];
	m_bfmeRowTX[0][1] = c * tmp1 + s * tmp2;
	m_bfmeRowTX[0][2] = c * tmp2 - s * tmp1;

	tmp1 = m_bfmeRowTX[1][1];
	tmp2 = m_bfmeRowTX[1][2];
	m_bfmeRowTX[1][1] = c * tmp1 + s * tmp2;
	m_bfmeRowTX[1][2] = c * tmp2 - s * tmp1;

	tmp1 = m_bfmeRowTX[2][1];
	tmp2 = m_bfmeRowTX[2][2];
	m_bfmeRowTX[2][1] = c * tmp1 + s * tmp2;
	m_bfmeRowTX[2][2] = c * tmp2 - s * tmp1;

	m_bfmeDirtyTX = 0;
}
