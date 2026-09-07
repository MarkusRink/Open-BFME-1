// cl: /DNDEBUG /MD /EHsc
// BFME's dispatcher calls the no-argument Drawable::drawEmoticon body.

typedef int Int;
typedef unsigned int UnsignedInt;

class Anim2D;

// The polymorphic 0x74-byte icon object places emoticon index 10 at +0x2C/+0x64.
enum { ICON_EMOTICON = 10 };

class DrawableIconInfo
{
public:
    Anim2D *m_icon[14];
    UnsignedInt m_keepTillFrame[14];

protected:
    virtual ~DrawableIconInfo();
};

class Anim2D
{
public:
    UnsignedInt getCurrentFrameWidth() const;
    UnsignedInt getCurrentFrameHeight() const;
    void draw(Int x, Int y, Int width, Int height);
};

class GameLogic
{
public:
    char m_unreconstructed_00[0x3c];
    UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class Drawable
{
public:
    DrawableIconInfo *getIconInfo();
    void clearEmoticon();

private:
    void drawEmoticon();

    char m_unreconstructed_00[0x2e0];
    DrawableIconInfo *m_iconInfo;
    char m_unreconstructed_2e4[0xe0];
    Int m_emoticonRegionLeft;
    char m_unreconstructed_3c8[4];
    Int m_emoticonRegionRight;
    Int m_emoticonRegionBottom;
};

// ?drawEmoticon@Drawable@@AAEXXZ
void Drawable::drawEmoticon()
{
    if (m_iconInfo != 0 && getIconInfo()->m_icon[ICON_EMOTICON] != 0)
    {
        UnsignedInt now = TheBfmeGameLogic->m_frame;
        if (getIconInfo()->m_keepTillFrame[ICON_EMOTICON] >= now)
        {
            Int barWidth = m_emoticonRegionRight - m_emoticonRegionLeft;
            Int frameWidth = getIconInfo()->m_icon[ICON_EMOTICON]->getCurrentFrameWidth();
            Int frameHeight = getIconInfo()->m_icon[ICON_EMOTICON]->getCurrentFrameHeight();
            Int screenX = (Int)(m_emoticonRegionLeft + (barWidth * 0.5f) - (frameWidth * 0.5f));
            Int screenY = m_emoticonRegionBottom - frameHeight;
            getIconInfo()->m_icon[ICON_EMOTICON]->draw(screenX, screenY, frameWidth, frameHeight);
        }
        else
        {
            clearEmoticon();
        }
    }
}
