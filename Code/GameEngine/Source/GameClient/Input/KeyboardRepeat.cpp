// cl: /DNDEBUG /MD /EHsc
//
// BFME recovery for retail RVA 0x005A3E00 (181 bytes).
// This is deliberately address-qualified.  The original ZH source calls the
// operation Keyboard::checkKeyRepeat, but BFME moved the event stream from the
// inline ZH array to a three-pointer vector at +0x0c.
//
// Identity anchors (read-only evidence):
//   * Keyboard ctor 0x005A3AC0 (69B) stores vtable 0x0110CD60.
//   * vtable 0x0110CD60 slot +0x14 -> j_0001ce45 -> 0x005A41F0.
//   * 0x005A41F0's tail call enters 0x005A3EF0, whose j_00039144 call
//     enters this body at 0x005A3E00.
//   * The ctor and the matched Keyboard implementation pin the event range
//     at +0x0c/+0x10/+0x14, status records at +0x18 (8-byte stride), names at
//     +0x818, and input frame at +0xe18.
//
// Retail extent: 0x005A3E00..0x005A3EB4 inclusive (181 bytes).  The only
// non-local relocation is j_00010e33 -> 0x005A3C00, the STL vector
// _M_insert_overflow body for this 8-byte event type.

typedef unsigned char  UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int   UnsignedInt;
typedef bool           Bool;

struct KeyboardIO
{
	UnsignedByte  key;
	UnsignedByte  status;
	UnsignedShort state;
	UnsignedInt   sequence;
};

// The empty tag and helper signature follow the retail call to the existing
// STL body at RVA 0x005A3C00.  Its first three arguments are the insertion
// position, the value, and the false-type tag; the final two are count/flag.
struct BfmeFalseType
{
};

struct BfmeKeyboardEventVector
{
	KeyboardIO *begin;    // this+0x0c
	KeyboardIO *end;      // this+0x10
	KeyboardIO *capacity; // this+0x14

	void Rva005A3C00InsertOverflow( KeyboardIO *where,
		const KeyboardIO &value,
		const BfmeFalseType &tag,
		UnsignedInt count,
		bool one );

    void push_back(const KeyboardIO &value)
    {
        if (end != capacity)
        {
            if (end != 0)
                *end = value;
            ++end;
        }
        else
        {
            BfmeFalseType tag;
            Rva005A3C00InsertOverflow(end, value, tag, 1, true);
        }
    }
};

struct BfmeKeyboardKeyName
{
	UnsignedShort standard;
	UnsignedShort shifted;
	UnsignedShort shifted2;
};

// The address-qualified owner matches the caller at RVA0x005A3EF0.
// Raw offsets retain the established Keyboard layout.  The eight-byte prefix includes
// the inherited vptr/name pair; the rest is the proven BFME object layout.
class Rva005A3EF0Keyboard
{
public:
	void processKeyEvents(void);
	UnsignedShort Rva005A3460TranslateKey(UnsignedShort keyCode);
	Bool Rva005A3E00CheckRepeat(void);

	UnsignedByte m_basePrefix[ 8 ];
	UnsignedShort m_modifiers; // +0x08
	UnsignedByte m_shift2Key;  // +0x0a
	UnsignedByte m_pad0b;
	BfmeKeyboardEventVector m_events; // +0x0c
	KeyboardIO m_keyStatus[ 256 ];  // +0x18 .. +0x818
	BfmeKeyboardKeyName m_keyNames[ 256 ]; // +0x818 .. +0xe18
	UnsignedInt m_inputFrame; // +0xe18
};

// Preserve the original nested loop and return-value structure, with the
// BFME vector replacing the older inline event array. No volatile or assembly.
Bool Rva005A3EF0Keyboard::Rva005A3E00CheckRepeat(void)
{
    Bool retVal = false;
    int key;
    for (key = 0; key < 256; ++key)
    {
        if ((m_keyStatus[key].state & 2) != 0)
        {
            if ((m_inputFrame - m_keyStatus[key].sequence) > 10)
            {
                KeyboardIO repeat;
                repeat.key = (UnsignedByte)key;
                repeat.state = 0x0102;
                repeat.status = 0;
                m_events.push_back(repeat);
                for (int index = 0; index < 256; ++index)
                    m_keyStatus[index].sequence = m_inputFrame;
                m_keyStatus[key].sequence = m_inputFrame - 12;
                retVal = true;
                break;
            }
        }
    }
    return retVal;
}
