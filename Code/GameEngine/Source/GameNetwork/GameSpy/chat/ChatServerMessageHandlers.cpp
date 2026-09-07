// cl: /DNDEBUG /MD -Ireference/shims/gamespy

// The GameSpy Chat SDK server-message handlers that were converted to C++
// rather than reconstructed inside the SDK's own .c translation units.
//
//   ciErrNoUniqueNickHandler       0x0086FC70   ciKillHandler        0x0086D900
//   ciErrUniqueNickExpiredHandler  0x0086FC90   ciQuitHandler        0x0086D820
//   ciErrErroneusNicknameHandler   0x0086FC10   ciRplWelcomeHandler  0x0086F5D0
//   ciRplLoginHandler              0x0086F7C0
//   ciRplSecureKeyHandler          0x0086F660
//
// Every one of them is an entry in the same handler table -- (CHAT, const
// ciServerMessage *) -- and every one of them casts the CHAT it is handed to a
// ciConnection. Split one body per file, each file restated both types with
// only the fields its own body touched, so ciConnection appeared with two
// members in one file and with a 0x8b4-byte body in another and nothing said
// they were the same object. The offsets never disagreed, only the amount each
// file bothered to name, so one declaration below carries all of them:
//
//   +0x00 connected     +0x0c nickErrorCallback   +0x1c chatSocket (0x328 B)
//   +0x04 connecting    +0x10 fillInUserCallback  +0x36c nick
//   +0x08 disconnected  +0x14 connectCallback     +0x828 secretKey
//                       +0x18 connectParam        +0x8a8 loginType
//                                                 +0x8ac userID
//                                                 +0x8b0 profileID
//
// ciServerMessage likewise: the parsed IRC line is eight char pointers, then
// params at +0x20 and numParams at +0x24. The files that only needed params
// spelled the first eight as an opaque 0x20-byte pad.

#include <stdlib.h>
#include <string.h>

typedef void *CHAT;
typedef int CHATBool;
typedef unsigned char byte;

enum
{
	CHATFalse,
	CHATTrue
};

typedef void (__cdecl *ciConnectCallback)(CHAT chat, CHATBool success,
	int failureReason, void *param);

struct gs_crypt_key
{
	byte state[256];
	byte x;
	byte y;
};

struct ciSocket
{
	char pad00[0x120];
	int secure;						// +0x120
	gs_crypt_key inKey;					// +0x124
	gs_crypt_key outKey;					// +0x226
};

struct ciConnection
{
	CHATBool connected;
	CHATBool connecting;
	CHATBool disconnected;
	void *nickErrorCallback;
	void *fillInUserCallback;
	ciConnectCallback connectCallback;
	void *connectParam;
	ciSocket chatSocket;					// +0x1c
	char pad344[0x36c - 0x344];
	char nick[64];						// +0x36c
	char pad3ac[0x828 - 0x3ac];
	char secretKey[1];					// +0x828
	char pad829[0x8a8 - 0x829];
	int loginType;						// +0x8a8
	int userID;						// +0x8ac
	int profileID;						// +0x8b0
};

struct ciServerMessage
{
	char *message;
	char *server;
	char *nick;
	char *user;
	char *host;
	char *command;
	char *middle;
	char *param;
	char **params;						// +0x20
	int numParams;						// +0x24
};

extern "C" void __cdecl ciNickError(CHAT chat, int type, const char *nick,
	int numSuggestedNicks, char **suggestedNicks);
extern "C" void __cdecl ciUserEnumChannels(CHAT chat, const char *user,
	void (*callback)(CHAT, const char *, const char *, void *), void *param);
extern "C" void ciKillEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *param);
extern "C" void ciQuitEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *reason);
extern "C" void ciSocketSend(void *chatSocket, const char *buffer);
extern "C" void ciSendNickAndUser(void *chat);
extern "C" void ciSendLogin(void *chat);
extern "C" void gs_xcode_buf(char *buffer, int length, char *key);
extern "C" void gs_prepare_key(const byte *key, int length, gs_crypt_key *out);

// The three nick failures the server can report while we are still connecting.
// They differ only in the code they hand ciNickError and in whether the nick we
// asked for is worth repeating back.

// _ciErrErroneusNicknameHandler, retail 0x0086FC10
extern "C" void ciErrErroneusNicknameHandler(CHAT chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (connection->connecting)
		ciNickError(chat, 1, connection->nick, 0, 0);
}

// _ciErrUniqueNickExpiredHandler, retail 0x0086FC90
extern "C" void ciErrUniqueNickExpiredHandler(CHAT chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (connection->connecting)
		ciNickError(chat, 2, "", 0, 0);
}

// _ciErrNoUniqueNickHandler, retail 0x0086FC70
extern "C" void ciErrNoUniqueNickHandler(CHAT chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (connection->connecting)
		ciNickError(chat, 3, "", 0, 0);
}

// _ciQuitHandler, retail 0x0086D820
extern "C" void ciQuitHandler(CHAT chat, const ciServerMessage *message)
{
	if (message->numParams != 1)
		return;

	ciUserEnumChannels(chat, message->nick, ciQuitEnumChannelsCallback,
		message->params[0]);
}

// _ciKillHandler, retail 0x0086D900
extern "C" void ciKillHandler(CHAT chat, const ciServerMessage *message)
{
	if (message->numParams != 2)
		return;

	ciUserEnumChannels(chat, message->params[0], ciKillEnumChannelsCallback,
		message->params[1]);
}

// _ciRplWelcomeHandler, retail 0x0086F5D0 -- the server accepted us, so the
// connection is up and the caller's connect callback finally fires.
extern "C" void ciRplWelcomeHandler(CHAT chat, const ciServerMessage *message)
{
	char *nick;
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams != 2)
		return;

	nick = message->params[0];

	if (strcmp(connection->nick, nick) != 0)
	{
		strncpy(connection->nick, nick, 64);
		connection->nick[63] = '\0';
	}

	connection->connecting = CHATFalse;
	connection->connected = CHATTrue;

	if (connection->connectCallback != 0)
		connection->connectCallback(chat, CHATTrue, 0,
			connection->connectParam);
}

// _ciRplLoginHandler, retail 0x0086F7C0
extern "C" void ciRplLoginHandler(void *chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams < 3)
		return;

	connection->userID = atoi(message->params[1]);
	connection->profileID = atoi(message->params[2]);

	if (connection->fillInUserCallback)
	{
		ciSocketSend(&connection->chatSocket, "USRIP");
	}
	else
	{
		ciSendNickAndUser(chat);
	}
}

// _ciRplSecureKeyHandler, retail 0x0086F660 -- both halves of the stream key
// arrive in one message, xcoded with the secret key we were built with.
extern "C" void ciRplSecureKeyHandler(void *chat, const ciServerMessage *message)
{
	char *outKeyRand;
	char *inKeyRand;
	int outKeyLen;
	int inKeyLen;
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams != 3)
		return;

	outKeyRand = message->params[1];
	inKeyRand = message->params[2];
	outKeyLen = (int)strlen(outKeyRand);
	inKeyLen = (int)strlen(inKeyRand);
	gs_xcode_buf(outKeyRand, outKeyLen, connection->secretKey);
	gs_xcode_buf(inKeyRand, inKeyLen, connection->secretKey);
	gs_prepare_key((const byte *)outKeyRand, outKeyLen, &connection->chatSocket.outKey);
	gs_prepare_key((const byte *)inKeyRand, inKeyLen, &connection->chatSocket.inKey);
	connection->chatSocket.secure = 1;
	if (connection->loginType != 0)
	{
		ciSendLogin(chat);
	}
	else if (connection->fillInUserCallback)
	{
		ciSocketSend(&connection->chatSocket, "USRIP");
	}
	else
	{
		ciSendNickAndUser(chat);
	}
}
