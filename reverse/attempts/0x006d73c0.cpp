// ??0W3DBibBuffer@@QAE@XZ
// partial score=0.82 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc
// BFME's bib buffer owns two reference-counted texture handles.  The released
// Zero Hour source constructs the same object, but allocates the dynamic
// buffers eagerly; retail BFME leaves those pointers null and loads only the
// two bib textures here.

typedef int Int;

class BFMETextureReference
{
public:
	void Release_Ref(void);
};

class ShroudFilter
{
private:
	char m_pad[0x0c];

public:
	Int m_uAddress;
	Int m_vAddress;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};

class BFMETextureHandle
{
public:
	ShroudTexture *m_texture;

	~BFMETextureHandle(void)
	{
		if (m_texture)
			((BFMETextureReference *)m_texture)->Release_Ref();
	}
};

extern BFMETextureHandle BFMEGetWaterTrackTexture(char *name, Int mipCount, Int format);

class BFMETextureHolder
{
public:
	ShroudTexture *m_texture;

	BFMETextureHolder(void) : m_texture(0) {}
	~BFMETextureHolder(void)
	{
		if (m_texture)
			((BFMETextureReference *)m_texture)->Release_Ref();
	}

	BFMETextureHolder &operator=(const BFMETextureHandle &handle)
	{
		if (handle.m_texture)
			++*(unsigned short *)((char *)handle.m_texture + 4);
		if (m_texture)
			((BFMETextureReference *)m_texture)->Release_Ref();
		m_texture = handle.m_texture;
		return *this;
	}
};

class W3DBibBuffer
{
public:
	W3DBibBuffer(void);
	void clearAllBibs(void);

private:
	void *m_vertexBib;
	Int m_vertexBibSize;
	void *m_indexBib;
	Int m_indexBibSize;
	BFMETextureHolder m_bibTexture;
	BFMETextureHolder m_highlightBibTexture;
	Int m_curNumBibVertices;
	Int m_curNumBibIndices;
	char m_bibStorage[0x109c8 - 0x20];
	Int m_numBibs;
	bool m_anythingChanged;
	char m_pad109cd;
	bool m_initialized;
};

// ??0W3DBibBuffer@@QAE@XZ
W3DBibBuffer::W3DBibBuffer(void)
{
	BFMETextureHolder *bibTexture = &m_bibTexture;
	BFMETextureHolder *highlightTexture = &m_highlightBibTexture;

	m_initialized = false;
	m_vertexBib = 0;
	m_indexBib = 0;
	m_curNumBibVertices = 0;
	m_curNumBibIndices = 0;
	clearAllBibs();
	m_indexBibSize = 384;
	m_vertexBibSize = 256;

	*bibTexture = BFMEGetWaterTrackTexture((char *)"TBBib.tga", 0, 0);
	*highlightTexture = BFMEGetWaterTrackTexture((char *)"TBRedBib.tga", 0, 0);

	bibTexture->m_texture->getFilter()->m_uAddress = 1;
	bibTexture->m_texture->getFilter()->m_vAddress = 1;
	highlightTexture->m_texture->getFilter()->m_uAddress = 1;
	highlightTexture->m_texture->getFilter()->m_vAddress = 1;
	m_initialized = true;
}
