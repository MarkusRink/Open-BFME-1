// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// The vector's element width does not identify its members. These placement
// constructors retain the out-of-line copy constructor each retail body calls.

class Open2Rec134500
{
public:
	Open2Rec134500(const Open2Rec134500 &value);
	char m_body[20];
};

class Open2Rec3A4420
{
public:
	Open2Rec3A4420(const Open2Rec3A4420 &value);
	char m_body[20];
};

inline void *operator new(unsigned int, void *place) { return place; }
inline void operator delete(void *, void *) {}

namespace _STL
{
struct Rva00143CE0Element
{
	char m_body[20];
};

struct Rva003A5500Element
{
	char m_body[20];
};

template <class Type>
void _Construct(Type *destination, const Type &value);

// Retail 0x00134F70 calls the copy constructor at 0x00134500 through 0x0001BCF7.
template <>
void _Construct(Rva00143CE0Element *destination, const Rva00143CE0Element &value)
{
	new (destination) Open2Rec134500(reinterpret_cast<const Open2Rec134500 &>(value));
}

// Retail 0x003A4670 calls the copy constructor at 0x003A4420 through 0x0000988B.
template <>
void _Construct(Rva003A5500Element *destination, const Rva003A5500Element &value)
{
	new (destination) Open2Rec3A4420(reinterpret_cast<const Open2Rec3A4420 &>(value));
}
}
