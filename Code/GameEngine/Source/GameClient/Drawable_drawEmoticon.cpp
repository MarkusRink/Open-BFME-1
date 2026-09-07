// cl: /DNDEBUG /MD /EHsc
// BFME's dispatcher calls the no-argument Drawable::drawEmoticon body.

typedef int Int;
typedef unsigned int UnsignedInt;

class DrawableIconInfo
{
public:
    void *m_icon[14];
    UnsignedInt m_keepTillFrame[14];
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
    if (m_iconInfo != 0 && getIconInfo()->m_icon[11] != 0)
    {
        UnsignedInt now = TheBfmeGameLogic->m_frame;
        if (getIconInfo()->m_keepTillFrame[11] >= now)
        {
            Int barWidth = m_emoticonRegionRight - m_emoticonRegionLeft;
            Int frameWidth = ((Anim2D *)getIconInfo()->m_icon[11])->getCurrentFrameWidth();
            Int frameHeight = ((Anim2D *)getIconInfo()->m_icon[11])->getCurrentFrameHeight();
            Int screenX = (Int)(m_emoticonRegionLeft + (barWidth * 0.5f) - (frameWidth * 0.5f));
            Int screenY = m_emoticonRegionBottom - frameHeight;
            ((Anim2D *)getIconInfo()->m_icon[11])->draw(screenX, screenY, frameWidth, frameHeight);
        }
        else
        {
            clearEmoticon();
        }
    }
}
