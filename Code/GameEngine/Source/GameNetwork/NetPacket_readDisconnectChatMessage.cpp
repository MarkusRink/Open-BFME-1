// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?readDisconnectChatMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z: Code/GameNetwork/Source/GameNetwork/NetPacket.cpp

#include <string.h>
#include <wchar.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

void *__cdecl operator new(unsigned int size);

static int stringLength(const unsigned short *s)
{
	return (int)wcslen((const wchar_t *)s);
}

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();
};

template <typename T>
class StringBase
{
	friend class UnicodeString;
	friend class NetDisconnectChatCommandMsg;
	friend class NetPacket;

public:
	void set(const T *str) { set(str, stringLength(str)); }
	void set(const T *str, int len);

private:
	StringBase() { m_data = 0; }
	StringBase(const StringBase<T> &src);
	~StringBase();
	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}
	void set(const UnsignedShort *str) { StringBase<UnsignedShort>::set(str); }
};

class NetDisconnectChatCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectChatCommandMsg();
	virtual ~NetDisconnectChatCommandMsg();
	void setText(UnicodeString text);

	UnsignedInt m_base[6];
	UnicodeString m_text;
};

class NetPacket
{
protected:
	static NetCommandMsg *readDisconnectChatMessage(UnsignedByte *data, Int &i);
};

NetCommandMsg *NetPacket::readDisconnectChatMessage(UnsignedByte *data, Int &i)
{
	NetDisconnectChatCommandMsg *msg = new NetDisconnectChatCommandMsg;

	UnsignedShort text[256];
	UnsignedByte length;
	memcpy(&length, data + i, sizeof(UnsignedByte));
	++i;
	memcpy(text, data + i, length * sizeof(UnsignedShort));
	i += length * sizeof(UnsignedShort);
	text[length] = 0;

	UnicodeString unitext;
	unitext.set(text);

	msg->setText(unitext);
	return msg;
}
