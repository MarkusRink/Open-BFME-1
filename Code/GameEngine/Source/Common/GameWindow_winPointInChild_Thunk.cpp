// cl: /DNDEBUG /MD /EHsc
// BFME GameWindow layout and audio declarations for winPointInChild.

typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	char *m_data;
};

enum ObjectID
{
	INVALID_ID = 0
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
	~AudioEventRTS();

private:
	char m_data[0x70];
};

#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual AudioHandle addAudioEvent(const AudioEventRTS *event);
};

extern AudioManager *TheAudio;

class GameWindow
{
public:
	GameWindow *winPointInChild(Int x, Int y, Bool ignoreEnableCheck, Bool playDisabledSound);

private:
	char m_pad00[0x08];
	unsigned int m_status;
	Int m_sizeX;
	Int m_sizeY;
	Int m_regionLoX;
	Int m_regionLoY;
	Int m_regionHiX;
	Int m_regionHiY;
	char m_pad24[0x1d4];
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
};

// ?winPointInChild@GameWindow@@QAEPAV1@HH_N0@Z
GameWindow *GameWindow::winPointInChild(Int x, Int y, Bool ignoreEnableCheck, Bool playDisabledSound)
{
	GameWindow *child;

	for (child = m_child; child; child = child->m_next)
	{
		Int originX = child->m_regionLoX;
		Int originY = child->m_regionLoY;
		GameWindow *parent = child->m_parent;

		while (parent)
		{
			originX += parent->m_regionLoX;
			originY += parent->m_regionLoY;
			parent = parent->m_parent;
		}

		if (x >= originX && x <= originX + child->m_sizeX &&
			y >= originY && y <= originY + child->m_sizeY)
		{
			Bool enabled = ignoreEnableCheck || (child->m_status & 0x08) != 0;
			Bool hidden = ((child->m_status >> 4) & 1) != 0;

			if (!hidden)
			{
				if (enabled)
				{
					return child->winPointInChild(x, y, ignoreEnableCheck, playDisabledSound);
				}
				else if ((child->m_status & 0x20000000) != 0)
				{
					return child->winPointInChild(x, y, ignoreEnableCheck, playDisabledSound);
				}
				else if (playDisabledSound)
				{
					AudioEventRTS disabledClick((const char *)0x010f77bc, (ObjectID)2);
					if (TheAudio)
					{
						TheAudio->addAudioEvent(&disabledClick);
					}
				}
			}
		}
	}

	return this;
}
