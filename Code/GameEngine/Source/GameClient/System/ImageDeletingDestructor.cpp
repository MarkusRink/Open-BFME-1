// cl: /O2
// Open-BFME: Image scalar-deleting destructor wrapper, retail 0x005D2BD0
// (30 bytes). Image vtable 0x0110FFEC slot 0 routes here through ILT
// 0x004294CE; the matched Image constructor at 0x005D2260 installs it.

class Image
{
public:
    __declspec(noinline) virtual ~Image();
};

Image::~Image()
{
}
