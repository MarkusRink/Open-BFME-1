// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BFME SurfaceClass is the one-pointer COM owner established by the matched
// surface-level accessor and its caller TextureHandleApply.cpp. The query
// and pixel-size helper retain address-qualified BFME method identities.
class SurfaceClass
{
public:
    struct SurfaceDescription
    {
        unsigned int Format;
        unsigned int Width;
        unsigned int Height;
        unsigned int Rva008FC4F0_PixelSize() const;
    };
    void Get_Description(SurfaceDescription &description);
    unsigned int Rva008FCA30_Surface_Byte_Size() const;
private:
    void *surface;
};

unsigned int SurfaceClass::Rva008FCA30_Surface_Byte_Size() const
{
    if (!surface)
        return 0;
    SurfaceDescription description;
    const_cast<SurfaceClass *>(this)->Get_Description(description);
    unsigned int pixelSize = description.Rva008FC4F0_PixelSize();
    if (pixelSize)
        return description.Width * description.Height * pixelSize;
    if (description.Format != 0x31545844 && description.Format != 0x32545844 &&
        description.Format != 0x33545844 && description.Format != 0x34545844 &&
        description.Format != 0x35545844)
        return 0;
    unsigned int size = description.Width * description.Height;
    if (description.Format == 0x31545844)
        size /= 2;
    return size;
}
