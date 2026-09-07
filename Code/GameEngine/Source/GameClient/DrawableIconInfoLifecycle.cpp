// cl: /DNDEBUG /MD /EHsc
// readable body of ??0DrawableIconInfo@@QAE@XZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?clear@DrawableIconInfo@@QAEXXZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ??1DrawableIconInfo@@MAE@XZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// BFME releases unpooled icons through virtual delete; the pooled reference calls freeBlock.
class Anim2D { public: virtual ~Anim2D(); };
class DrawableIconInfo
{
public:
    DrawableIconInfo();
    __declspec(noinline) void clear();
protected:
    virtual ~DrawableIconInfo();
private:
    Anim2D *m_icon[14];
    unsigned int m_keepTillFrame[14];
};
DrawableIconInfo::DrawableIconInfo()
{
    for (int i = 0; i < 14; ++i) {
        m_icon[i] = 0;
        m_keepTillFrame[i] = 0;
    }
}
void DrawableIconInfo::clear()
{
    for (int i = 0; i < 14; ++i) {
        delete m_icon[i];
        m_icon[i] = 0;
        m_keepTillFrame[i] = 0;
    }
}
DrawableIconInfo::~DrawableIconInfo() { clear(); }

// The linker stub forwards ECX unchanged to the out-of-line clear body.
void __fastcall rva0000DBA7ClearIcons(DrawableIconInfo *icons) { icons->clear(); }
