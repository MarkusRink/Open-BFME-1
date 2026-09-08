// ?bfmeSetHQ@BfmeXfHQ@@QAEXPAVMatrix3D@@@Z
// partial score=0.95 date=2026-09-08
class Matrix3D
{
public:
	float Get_Z_Rotation() const;

	float m_bfmeMHQ[12];
};

class BfmeTripleHQ
{
public:
	float m_bfmeXHQ;
	float m_bfmeYHQ;
	float m_bfmeZHQ;
};

class BfmeXfHQ
{
public:
	virtual void bfmeVt0HQ();
	virtual void bfmeVt1HQ();
	virtual void bfmeVt2HQ();
	virtual void bfmeVt3HQ();
	virtual void bfmeVt4HQ();
	virtual void bfmeApplyHQ(Matrix3D *m, BfmeTripleHQ *t, float r);

	void bfmeSetHQ(Matrix3D *m);

	unsigned char m_bfmeGapHQ[4];
	Matrix3D m_bfmeMatrixHQ;
	BfmeTripleHQ m_bfmePosHQ;
	float m_bfme44HQ;
	unsigned char m_bfmeGap2HQ[0x14];
	int m_bfme5cHQ;
};

void BfmeXfHQ::bfmeSetHQ(Matrix3D *m)
{
	float rot = m_bfme44HQ;
	BfmeTripleHQ pos;
	Matrix3D old;

	pos.m_bfmeXHQ = m_bfmePosHQ.m_bfmeXHQ;
	pos.m_bfmeYHQ = m_bfmePosHQ.m_bfmeYHQ;
	pos.m_bfmeZHQ = m_bfmePosHQ.m_bfmeZHQ;

	old.m_bfmeMHQ[0] = m_bfmeMatrixHQ.m_bfmeMHQ[0];
	old.m_bfmeMHQ[1] = m_bfmeMatrixHQ.m_bfmeMHQ[1];
	old.m_bfmeMHQ[2] = m_bfmeMatrixHQ.m_bfmeMHQ[2];
	old.m_bfmeMHQ[3] = m_bfmeMatrixHQ.m_bfmeMHQ[3];
	old.m_bfmeMHQ[4] = m_bfmeMatrixHQ.m_bfmeMHQ[4];
	old.m_bfmeMHQ[5] = m_bfmeMatrixHQ.m_bfmeMHQ[5];
	old.m_bfmeMHQ[6] = m_bfmeMatrixHQ.m_bfmeMHQ[6];
	old.m_bfmeMHQ[7] = m_bfmeMatrixHQ.m_bfmeMHQ[7];
	old.m_bfmeMHQ[8] = m_bfmeMatrixHQ.m_bfmeMHQ[8];
	old.m_bfmeMHQ[9] = m_bfmeMatrixHQ.m_bfmeMHQ[9];
	old.m_bfmeMHQ[10] = m_bfmeMatrixHQ.m_bfmeMHQ[10];
	old.m_bfmeMHQ[11] = m_bfmeMatrixHQ.m_bfmeMHQ[11];

	m_bfmeMatrixHQ.m_bfmeMHQ[0] = m->m_bfmeMHQ[0];
	m_bfmeMatrixHQ.m_bfmeMHQ[1] = m->m_bfmeMHQ[1];
	m_bfmeMatrixHQ.m_bfmeMHQ[2] = m->m_bfmeMHQ[2];
	m_bfmeMatrixHQ.m_bfmeMHQ[3] = m->m_bfmeMHQ[3];
	m_bfmeMatrixHQ.m_bfmeMHQ[4] = m->m_bfmeMHQ[4];
	m_bfmeMatrixHQ.m_bfmeMHQ[5] = m->m_bfmeMHQ[5];
	m_bfmeMatrixHQ.m_bfmeMHQ[6] = m->m_bfmeMHQ[6];
	m_bfmeMatrixHQ.m_bfmeMHQ[7] = m->m_bfmeMHQ[7];
	m_bfmeMatrixHQ.m_bfmeMHQ[8] = m->m_bfmeMHQ[8];
	m_bfmeMatrixHQ.m_bfmeMHQ[9] = m->m_bfmeMHQ[9];
	m_bfmeMatrixHQ.m_bfmeMHQ[10] = m->m_bfmeMHQ[10];
	m_bfmeMatrixHQ.m_bfmeMHQ[11] = m->m_bfmeMHQ[11];

	m_bfmePosHQ.m_bfmeXHQ = m_bfmeMatrixHQ.m_bfmeMHQ[3];
	m_bfmePosHQ.m_bfmeYHQ = m_bfmeMatrixHQ.m_bfmeMHQ[7];
	m_bfmePosHQ.m_bfmeZHQ = m_bfmeMatrixHQ.m_bfmeMHQ[11];
	m_bfme44HQ = m_bfmeMatrixHQ.Get_Z_Rotation();
	m_bfme5cHQ = 0;

	bfmeApplyHQ(&old, &pos, rot);
}
