// cl: /DNDEBUG /MD /EHsc
//
// No named caller proves the owner class. The distinct retail callbacks
// identify AsciiString names at +0x0C and owning texture references at +0x24;
// using one cell type for both concealed two different destructor targets.

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class TextureClass;

template <class T>
class RefCountPtr
{
public:
	~RefCountPtr();

private:
	T *m_referent;
};

class Rva007A1230ArrayOwner
{
public:
	virtual ~Rva007A1230ArrayOwner();

private:
	void releaseOwnedState(void);
	unsigned char m_beforeArrays[8];
	AsciiString m_textureNames[6];
	RefCountPtr<TextureClass> m_textureReferences[6];
};

Rva007A1230ArrayOwner::~Rva007A1230ArrayOwner()
{
	releaseOwnedState();
}
