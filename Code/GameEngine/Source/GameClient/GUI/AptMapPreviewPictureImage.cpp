// cl: /DNDEBUG /MD /EHsc

// Recovered BFME map-picture loader at RVA 0x00520BB0 (431 bytes).
// The descriptive _bfme_ name does not claim an original source spelling.
// AptMapPreview's image selection caller at 0x00520E70 passes a map-name
// string at +0x50, owns the returned Image at +0x34, and falls back to the
// mapped image "MissingMap" when no picture is available.
//
// The Image layout and UV/size operations follow GameClient/Image.h; the
// filename is the map path with its four-character extension replaced by
// "_pic.tga". The string ABI below follows StringInline.h, with the two
// existing public StringBase methods required by this body added locally.
// The address-derived Rva0044F4D0 is an existing one-pointer texture-owner
// ABI shim. Its int argument carries a filename pointer on this 32-bit target.
//
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
public:
	void removeLastChar();
	void concat(const T *, int);
private:
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void removeLastChar() { StringBase<char>::removeLastChar(); }
	void concat(const char *text, int count) { StringBase<char>::concat(text, count); }
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
};

typedef unsigned int size_t;
void *__cdecl operator new(size_t);
void __cdecl operator delete(void *);

class GlobalData;
extern GlobalData *TheWritableGlobalData;

class FileSystem
{
public:
    bool doesFileExist(const char *) const;
};
extern FileSystem *TheFileSystem;

class TextureClass
{
public:
    void Release_Ref();
};

class Rva0044F4D0
{
public:
    Rva0044F4D0(int name);
    ~Rva0044F4D0() { if (m_texture) m_texture->Release_Ref(); }
private:
    TextureClass *m_texture;
};

struct Coord2D { float x, y; };
struct Region2D { Coord2D lo, hi; };

class Image
{
public:
    Image();
    virtual ~Image();
    void setName(AsciiString name);
    void setFilename(AsciiString name);
    void _bfme_setTexture(const Rva0044F4D0 &texture);
    unsigned int setStatus(unsigned int bit);
    void setUV(Region2D *uv) { if (uv) m_uv = *uv; }
    void setTextureHeight(int height) { m_textureHeight = height; }
    void setTextureWidth(int width) { m_textureWidth = width; }
private:
    AsciiString m_name;
    AsciiString m_filename;
    int m_textureWidth;
    int m_textureHeight;
    Region2D m_uv;
    int m_imageWidth;
    int m_imageHeight;
    Rva0044F4D0 *m_texture;
    unsigned int m_status;
};


Image *_bfme_createMapPictureImage(const AsciiString &mapName)
{
    if (!TheWritableGlobalData)
        return 0;

    AsciiString pictureName = mapName;
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    pictureName.concat("_pic.tga", 8);

    Image *image = 0;
    if (TheFileSystem->doesFileExist(pictureName.str()))
    {
        image = new Image;
        image->setName(pictureName);
        image->setFilename(pictureName);
        image->_bfme_setTexture(Rva0044F4D0((int)pictureName.str()));
        image->setStatus(2);
        Region2D uv;
        uv.lo.x = 0.0f;
        uv.lo.y = 0.0f;
        uv.hi.x = 1.0f;
        uv.hi.y = 1.0f;
        image->setUV(&uv);
        image->setTextureHeight(128);
        image->setTextureWidth(128);
    }
    return image;
}
