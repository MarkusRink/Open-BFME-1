// cl: /DNDEBUG /MD /EHsc

class TextureMapperClass
{
public:
    virtual ~TextureMapperClass();
};

__declspec(noinline) TextureMapperClass::~TextureMapperClass() {}

void Force_TextureMapper_Deleting_Destructor(TextureMapperClass *mapper)
{
    delete mapper;
}
