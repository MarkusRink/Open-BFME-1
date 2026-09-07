// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

// NetPacket::readGameSpyStatsAuthKeyMessage, retail 0x0067EC70, 251 bytes.
//
// The type-6 raw-data branch constructs the BFME GameSpy auth-key command and
// carries two NUL-terminated ASCII fields: login name followed by locale/key
// text.  The same command's matched size, fill, add, getter and setter bodies
// establish the two StringBase<char> members at +0x1C and +0x20.

#include "StringInline.h"

typedef int Int;
typedef unsigned char UnsignedByte;

class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg();

protected:
	unsigned char m_bfmeHead[0x1C - 4];
};

class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetGameSpyStatsAuthKeyCommandMsg();
	void setText1C(AsciiString text);
	void setText20(AsciiString text);

	AsciiString m_text1C;
	AsciiString m_text20;
};

class NetPacket
{
protected:
	static NetCommandMsg *readGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i);
};

NetCommandMsg *NetPacket::readGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i)
{
	BFMENetGameSpyStatsAuthKeyCommandMsg *msg =
		new BFMENetGameSpyStatsAuthKeyCommandMsg;
	char text[256];
	char *c = text;

	while (data[i] != 0) {
		*c = data[i];
		++c;
		++i;
	}
	*c = 0;
	++i;
	msg->setText1C(AsciiString(text));

	c = text;
	while (data[i] != 0) {
		*c = data[i];
		++c;
		++i;
	}
	*c = 0;
	++i;
	msg->setText20(AsciiString(text));

	return msg;
}
