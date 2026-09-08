// ?bfmeWriteXZ@@YAPAVStreamWriter@@PAV1@PAUBfmeVecXZ@@@Z
// partial score=0.98 date=2026-09-08
// pin needed: ?bfmePutXZ@StreamWriter@@QAEXH@Z,0x0002408C
class StreamWriter
{
public:
	void bfmePutXZ(int ch);
};

struct BfmeVecXZ
{
	unsigned char m_bfmeHeadXZ[4];
	float m_bfme04XZ;
	float m_bfme08XZ;
};

StreamWriter *formatReal(StreamWriter *w, double v);

StreamWriter *bfmeWriteXZ(StreamWriter *w, BfmeVecXZ *v)
{
	float x = v->m_bfme04XZ;
	float y = v->m_bfme08XZ;
	StreamWriter *out;

	out = formatReal(w, x);
	out->bfmePutXZ(0x20);
	formatReal(out, y);

	return w;
}
