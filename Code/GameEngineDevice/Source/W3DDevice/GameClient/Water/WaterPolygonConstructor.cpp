// cl: /DNDEBUG /MD /EHsc
// The vtable and array callbacks tie this constructor to the owner at
// 0x007A1230, whose original class identity remains unproven. The paired
// callbacks distinguish ASCII texture names from owning texture references.

class AsciiString
{
public:
	AsciiString(void);
	~AsciiString(void);

private:
	void *m_data;
};

class TextureClass;

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(void);
	~RefCountPtr(void);

private:
	T *m_referent;
};

class Rva007A1230ArrayOwner
{
public:
	Rva007A1230ArrayOwner(void *source);
	virtual ~Rva007A1230ArrayOwner(void);
	void initialize(void *source);

private:
	unsigned char m_flag04;
	unsigned char m_padding05[3];
	void *m_field08;
	AsciiString m_textureNames[6];
	RefCountPtr<TextureClass> m_textureReferences[6];
	unsigned char m_flag3c;
	unsigned char m_padding3d[0x0f];
	unsigned int m_value4c;
	unsigned int m_value50;
	// The initializer passes these raw values to AABoxClass(Vector3 *, int).
	unsigned int m_pointStorage;
	unsigned int m_pointCount;
	unsigned int m_value5c;
	unsigned int m_value60;
	unsigned char m_boundsValid;
};

// The initializer is still a generic dump row.  Keep its call target named by
// that existing row until the adjacent body is converted; the cast supplies
// the recovered thiscall/one-argument ABI without inventing a second address.
extern void d_007a4d40(void);

// VC7.1 reserves __thiscall in a free-function-pointer typedef.  A fastcall
// cast with the source duplicated gives the same ECX object and stack argument
// while leaving the otherwise-unused EDX copy harmless at the target.
typedef void (__fastcall *WaterPolygonInitializeCall)(
	Rva007A1230ArrayOwner *, void *, void *);

Rva007A1230ArrayOwner::Rva007A1230ArrayOwner(void *source)
	: m_flag04(0), m_field08(0)
{
	m_flag3c = 0;
	m_value4c = 0;
	m_value50 = 0;
	m_pointStorage = 0;
	m_pointCount = 0;
	m_value5c = 0;
	m_value60 = 0;
	m_boundsValid = 0;
	((WaterPolygonInitializeCall)d_007a4d40)(this, source, source);
}
