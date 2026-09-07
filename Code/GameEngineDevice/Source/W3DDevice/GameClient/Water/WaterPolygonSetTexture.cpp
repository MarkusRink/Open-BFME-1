// cl: /DNDEBUG /MD /EHsc
// Constructor 0x007A4FD0 and initializer 0x007A4D40 pass the same 0x80-byte
// polygon object here. Its original class and method spelling are unproven;
// the address-derived owner distinguishes it from the larger water renderer.

typedef int Int;
typedef char Char;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, Int mipCount, Int format);

class TextureHolder
{
public:
	void bind(const BFMEWaterTrackTextureHandle &texture);
};

class InlineTextureHolder
{
public:
	TextureClass *m_texture;

	__forceinline void bind(const BFMEWaterTrackTextureHandle &texture)
	{
		if (texture.m_texture)
			++*(unsigned short *)((char *)texture.m_texture + 4);
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
		m_texture = texture.m_texture;
	}
};

static inline void BFMEAssignWaterTrackTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN = 0
};

enum WaterTextureIndex
{
	WATER_TEXTURE_0 = 0
};

class W3DRadarFormatCaps
{
public:
	Bool supportTextureFormat(WW3DFormat format);
};

extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;

static __forceinline Bool BFMEWaterTrackIndexInRange(Int index)
{
	return (unsigned)index < 6;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Char *m_data;

	AsciiString &operator=(const AsciiString &other);

	Char *str(void) const
	{
		if (m_data)
			return m_data + 8;
		return (Char *)0x0107388b;
	}

	Bool isEmpty(void) const
	{
		return m_data == 0 || *(unsigned short *)(m_data + 4) == 0;
	}
};

class Rva007A1230ArrayOwner
{
public:
	virtual ~Rva007A1230ArrayOwner();
	void setTexture(const AsciiString &name, WaterTextureIndex index);

private:
	Bool m_flag04;
	Char m_beforeNames[7];
	AsciiString m_textureNames[6];
	TextureClass *m_textureReferences[6];
};

void Rva007A1230ArrayOwner::setTexture(
	const AsciiString &name, WaterTextureIndex index)
{
	register Rva007A1230ArrayOwner *self = this;
	Int indexValue = (Int)index;
	if (!BFMEWaterTrackIndexInRange(indexValue))
		return;

	self->m_textureNames[indexValue] = name;
	if (self->m_textureNames[indexValue].isEmpty())
		return;

	if (!self->m_flag04 && indexValue == 4)
	{
		Int format = 0;
		if (TheW3DRadarFormatCaps->supportTextureFormat(
			(WW3DFormat)0x3c))
			format = 0x3c;
		else if (TheW3DRadarFormatCaps->supportTextureFormat(
			(WW3DFormat)0x3e))
			format = 0x3e;
		else if (TheW3DRadarFormatCaps->supportTextureFormat(
			(WW3DFormat)0x3d))
			format = 0x3d;

		((TextureHolder *)((char *)self + 0x34))->bind(
			BFMEGetWaterTrackTexture(
				self->m_textureNames[4].str(), 1, format));
	}
	else
	{
		BFMEAssignWaterTrackTexture(
			self->m_textureReferences[indexValue],
			BFMEGetWaterTrackTexture(
				self->m_textureNames[indexValue].str(), 0, 0));
	}
}
