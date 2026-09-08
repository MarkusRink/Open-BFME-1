// ??0FVFInfoClass@@QAE@II@Z
// partial score=0.89 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2
// BFME extends Zero Hour's FVFInfoClass with a format index at +0x3c.

extern "C" unsigned __stdcall D3DXGetFVFVertexSize(unsigned fvf);

class BFMEVertexFVFInfo
{
public:
	void Initialize(unsigned fvf, unsigned vertexSize);

private:
	unsigned m_fvf;
	unsigned m_fvfSize;
	unsigned m_locationOffset;
	unsigned m_normalOffset;
	unsigned m_blendOffset;
	unsigned m_texcoordOffset[8];
	unsigned m_diffuseOffset;
	unsigned m_specularOffset;
	unsigned m_format;
};

static const unsigned s_vertexFormats[15] = {
	0x00000012, 0x00000112, 0x00000212, 0x00000152, 0x00000252,
	0x00000142, 0x00000242, 0x00000102, 0x00000202, 0x00540452,
	0x000b0312, 0x00000052, 0x00000344, 0x00000444, 0x00000000
};

void BFMEVertexFVFInfo::Initialize(unsigned fvf, unsigned vertexSize)
{
	unsigned zero = 0;
	m_fvf = fvf;
	m_fvfSize = fvf != zero ? D3DXGetFVFVertexSize(fvf) : vertexSize;
	m_locationOffset = zero;
	m_blendOffset = m_locationOffset;
	if ((m_fvf & 0x002) == 0x002)
		m_blendOffset += 3 * sizeof(float);

	m_normalOffset = m_blendOffset;
	if ((m_fvf & 0x00c) == 0x00c && (m_fvf & 0x1000) == 0x1000)
		m_normalOffset += 3 * sizeof(float) + sizeof(unsigned);

	m_diffuseOffset = m_normalOffset;
	if ((m_fvf & 0x010) == 0x010)
		m_diffuseOffset += 3 * sizeof(float);

	m_specularOffset = m_diffuseOffset;
	if ((m_fvf & 0x040) == 0x040)
		m_specularOffset += sizeof(unsigned);

	m_texcoordOffset[0] = m_specularOffset;
	if ((m_fvf & 0x080) == 0x080)
		m_texcoordOffset[0] += sizeof(unsigned);

	unsigned shift = 15;
	unsigned count = 7;
	unsigned *offset = &m_texcoordOffset[1];
	do {
		unsigned previous = offset[-1];
		unsigned sizeOne = 3u << shift;
		*offset = previous;
		if ((m_fvf & sizeOne) == sizeOne)
			previous += sizeof(float);
		else
			previous += 2 * sizeof(float);
		*offset = previous;
		++offset;
		++shift;
	} while (--count != 0);

	m_format = 15;
	unsigned value = 2;
	const unsigned *format = &s_vertexFormats[1];
	unsigned groups = 3;
	do {
		if (m_fvf == format[-1]) m_format = value - 2;
		if (m_fvf == format[0]) m_format = value - 1;
		if (m_fvf == format[1]) m_format = value;
		if (m_fvf == format[2]) m_format = value + 1;
		if (m_fvf == format[3]) m_format = value + 2;
		value += 5;
		format += 5;
	} while (--groups != 0);
}
