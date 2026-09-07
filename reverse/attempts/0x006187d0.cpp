// ?rva006187d0@Rva00618600Poly@@QAE_NPAX@Z
// partial score=0.35 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x006187D0, 111 bytes.  The public class spelling is not recovered:
// the same-file constructor at 0x00618890 installs vtable 0x01116D64, and that
// table has only the two already-matched address-derived Rva00618600Poly
// destructors.  This method therefore keeps the truthful address-derived
// owner and method spelling rather than assigning a Living World class name.
//
// The body is the Living World move-army-to-position message path.  It accepts
// one four-byte source-object argument, is enabled only for object state 5,
// asks the proven BfmeGameCW data-bearing object whether that source is usable,
// builds a Coord3D through the proven state vtable slot +0x20, then appends
// message 1103 with the existing type-6 argument helper and location helper.

typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

// This is the actual data-bearing global view already used by
// Bfme5TinyTwentyNine.cpp: m_bfmeOver is at +0x288, not an empty fabricated
// receiver.  The method declaration is the neutral source-level view of the
// existing retail body at 0x0060D5A0 (the 0x00014858 ILT reaches it).
class BfmeGameCW
{
public:
	char m_bfmeHead[0x288];
	bool m_bfmeOver;
	Bool rva0060d5a0(void *source);
};

extern BfmeGameCW *g_bfmeGameCW;

class BfmeStateDF
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void buildFramePoint(void *source, Coord3D *point) = 0;
};

extern "C" BfmeStateDF *g_bfmeStateDF;

class GameMessage
{
public:
	// Proven GameMessage storage: header +0x00..0x13, player index +0x14,
	// and the remaining message state through +0x23.
	void appendLocationArgument(const Coord3D &arg);

	unsigned char m_bfmeHead[0x14];
	int m_playerIndex;
	unsigned char m_bfmeTail[0x0c];
};

class MessageStream
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2C(void) = 0;
	virtual void slot30(void) = 0;
	virtual GameMessage *appendMessage(UnsignedInt type) = 0;
};

extern MessageStream *TheMessageStream;

struct BfmeSubENE
{
	unsigned char m_bfmeHead[8];
	void *m_bfmeP;
	unsigned char m_bfmePad[0xc];
	int m_bfmeK;
};

// Existing matched 0x0008AC10 type-6 argument body.  The complete data view
// is copied from BfmeConv880.cpp; the call therefore uses its verified C++
// member ABI instead of an empty receiver plus a function-pointer thunk cast.
struct BfmeThingENE
{
	BfmeSubENE *bfmeGoENE(void *value);
	BfmeSubENE *bfmeBaseENE();
};

class Rva00618600Poly
{
public:
	virtual ~Rva00618600Poly();
	Bool rva006187d0(void *source);

private:
	unsigned char m_unmodelled04[4];
	void *m_source;
	unsigned char m_unmodelled0c[0x14];
	int m_state;
};

Bool Rva00618600Poly::rva006187d0(void *source)
{
	void *sourceArg = source;
	if (m_state != 5)
		goto failure;

	if (!g_bfmeGameCW->rva0060d5a0(sourceArg))
		goto failure;

	Coord3D location;
	g_bfmeStateDF->buildFramePoint(sourceArg, &location);

	GameMessage *message = TheMessageStream->appendMessage(1103);

	// BFME inserts SQUADID at argument ordinal 6.  This is the existing
	// matched BfmeThingENE::bfmeGoENE member ABI (retail ILT 0x00015C1C,
	// body 0x0008AC10).
	(reinterpret_cast<BfmeThingENE *>(message)->bfmeGoENE(m_source));
	message->appendLocationArgument(location);
	return true;

failure:
	return false;
}
