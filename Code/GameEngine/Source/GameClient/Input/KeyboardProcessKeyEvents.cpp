// cl: /DNDEBUG /MD /EHsc
//
// BFME recovery for retail RVA 0x005A3EF0 (179 bytes).
// The historical ZH source calls the operation Keyboard::updateKeys, but
// BFME splits acquisition (0x005A40E0) from this event/status pass.  The name
// below is intentionally address-qualified because the original BFME split-method spelling is
// unknown; constructor and vtable evidence establish Keyboard ownership.
//
// Identity anchors (read-only evidence):
//   * Keyboard ctor 0x005A3AC0 (69B) stores vtable 0x0110CD60.
//   * vtable slot +0x14 is j_0001ce45 -> 0x005A41F0; that body calls
//     0x005A40E0 and tail-jumps through j_00039671 -> this 0x005A3EF0.
//   * This body calls j_00039144 -> 0x005A3E00 and j_00025374 ->
//     0x005A3460 (the Keyboard modifier/character translation body; still ASM).
//   * The matched DirectInputKeyboard vtable 0x0111CDCC resolves slot +0x2c
//     through j_000149c0 -> 0x006BB320 (getKey), proving the surrounding
//     vector is Keyboard input state rather than an unrelated 8-byte array.
//
// Retail extent: 0x005A3EF0..0x005A3FA2 inclusive (179 bytes).  There are two
// direct/ILT code relocations: j_00025374 -> 0x005A3460 and j_00039144 ->
// 0x005A3E00.  No CRT/import calls occur in this body.

typedef unsigned char  UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int   UnsignedInt;
typedef bool           Bool;

enum
{
	KEY_NONE   = 0x00,
	KEY_TAB    = 0x0f,
	KEY_CAPS   = 0x3a,
	KEY_LCTRL  = 0x1d,
	KEY_RCTRL  = 0x9d,
	KEY_LSHIFT = 0x2a,
	KEY_RSHIFT = 0x36,
	KEY_LALT   = 0x38,
	KEY_RALT   = 0xb8,
	KEY_STATE_DOWN = 0x0002
};

struct KeyboardIO
{
	UnsignedByte  key;
	UnsignedByte  status;
	UnsignedShort state;
	UnsignedInt   sequence;
};

struct BfmeKeyboardEventVector
{
	KeyboardIO *begin;    // this+0x0c
	KeyboardIO *end;      // this+0x10
	KeyboardIO *capacity; // this+0x14
};

struct BfmeKeyboardKeyName
{
	UnsignedShort standard;
	UnsignedShort shifted;
	UnsignedShort shifted2;
};

class Rva005A3EF0Keyboard
{
public:
	void processKeyEvents( void );
	UnsignedShort Rva005A3460TranslateKey( UnsignedShort keyCode ); // 0x005A3460
	Bool Rva005A3E00CheckRepeat( void ); // 0x005A3E00

	UnsignedByte m_basePrefix[ 8 ];
	UnsignedShort m_modifiers; // +0x08
	UnsignedByte m_shift2Key;  // +0x0a
	UnsignedByte m_pad0b;
	BfmeKeyboardEventVector m_events; // +0x0c
	KeyboardIO m_keyStatus[ 256 ];  // +0x18 .. +0x818
	BfmeKeyboardKeyName m_keyNames[ 256 ]; // +0x818 .. +0xe18
	UnsignedInt m_inputFrame; // +0xe18
};

// @?processKeyEvents@Rva005A3EF0Keyboard@@QAEXXZ 0x005A3EF0
void Rva005A3EF0Keyboard::processKeyEvents( void )
{
	KeyboardIO *event = m_events.begin;
	KeyboardIO *end = m_events.end;

	while( event != end )
	{
		m_keyStatus[ event->key ].state = event->state;
		m_keyStatus[ event->key ].status = event->status;
		m_keyStatus[ event->key ].sequence = m_inputFrame;

		// Prevent ALT-TAB from creating a TAB event.
		if( event->key == KEY_TAB )
		{
			if( (m_keyStatus[ KEY_LALT ].state & KEY_STATE_DOWN) != 0 ||
				(m_keyStatus[ KEY_RALT ].state & KEY_STATE_DOWN) != 0 )
			{
				event->status = 1;
			}
		}
		else if( event->key == KEY_CAPS || event->key == KEY_LCTRL ||
			event->key == KEY_RCTRL || event->key == KEY_LSHIFT ||
			event->key == KEY_RSHIFT || event->key == KEY_LALT ||
			event->key == KEY_RALT )
		{
			// Retail ignores the return value; the call updates modifier state.
			Rva005A3460TranslateKey( (UnsignedShort)event->key );
		}

		++event;
	}

	Rva005A3E00CheckRepeat();

	if( m_modifiers != 0 )
	{
		KeyboardIO *modifier_end = m_events.end;
		event = m_events.begin;
		while( event != modifier_end )
		{
			event->state = (UnsignedShort)(event->state | m_modifiers);
			++event;
		}
	}
}
