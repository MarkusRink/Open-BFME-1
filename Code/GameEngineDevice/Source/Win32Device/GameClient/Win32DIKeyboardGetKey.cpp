// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#define DIRECTINPUT_VERSION 0x800
#include <windows.h>
#include <dinput.h>

#undef DIERR_NOTACQUIRED
#define DIERR_NOTACQUIRED 0x8007000CL

enum
{
	KEY_NONE = 0,
	KEY_LOST = 0xff,
    KEY_STATE_UP = 1,
    KEY_STATE_DOWN = 2,
};

struct KeyboardIO
{
	enum StatusType
	{
		STATUS_UNUSED = 0,
		STATUS_USED = 1,
	};

	unsigned char key;
	unsigned char status;
	unsigned short state;
	unsigned int sequence;
};

class DirectInputKeyboard
{
protected:
	virtual void getKey( KeyboardIO *key );

	char m_keyboardBase[0xe1c - 4];
	LPDIRECTINPUT8 m_pDirectInput;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice;
};

void DirectInputKeyboard::getKey( KeyboardIO *key )
{
	DIDEVICEOBJECTDATA kbdat;
	DWORD num = 0;
	HRESULT hr;

	key->sequence = 0;
	key->key = KEY_NONE;

	if( m_pKeyboardDevice )
	{
		num = 1;
		hr = m_pKeyboardDevice->Acquire();
		if( hr == DI_OK || hr == S_FALSE )
			hr = m_pKeyboardDevice->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ),
				&kbdat, &num, 0 );
		switch( hr )
		{
		case DI_OK:
			break;

		case DIERR_INPUTLOST:
		case DIERR_NOTACQUIRED:
			hr = m_pKeyboardDevice->Acquire();
			switch( hr )
			{
			case DIERR_INVALIDPARAM:
			case DIERR_NOTINITIALIZED:
			case DIERR_OTHERAPPHASPRIO:
				break;

			case DI_OK:
			case S_FALSE:
				key->key = KEY_LOST;
				break;
			}
			return;

		default:
			return;
		}

		if( num == 0 )
			return;

		key->key = (unsigned char)(kbdat.dwOfs & 0xff);
		key->sequence = kbdat.dwSequence;
		key->state = (( kbdat.dwData & 0x80 ) ? KEY_STATE_DOWN : KEY_STATE_UP);
		key->status = KeyboardIO::STATUS_UNUSED;
	}
}
