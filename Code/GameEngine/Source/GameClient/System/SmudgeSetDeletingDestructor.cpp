// cl: /O2
// Open-BFME: SmudgeSet scalar-deleting destructor wrapper, retail
// 0x005D42F0 (30 bytes). SmudgeSet vtable 0x0111017C slot 0 routes
// here through ILT 0x0003E662; the matched constructor at 0x005D4160
// installs that vtable and the wrapper calls destructor ILT 0x000056D7.

class SmudgeSet
{
public:
    __declspec(noinline) virtual ~SmudgeSet();
};

SmudgeSet::~SmudgeSet()
{
}
