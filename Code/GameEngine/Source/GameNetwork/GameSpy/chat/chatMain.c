// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- the ciSendGetKey body from chatMain.c.
   Reconstructed from the 2007 SDK (nitrocaster/GameSpy,
   src/GameSpy/Chat/chatMain.c), whose function body is unchanged from the
   2004-vintage implementation compiled into lotrbfme.exe.  The surrounding
   declarations are local because the matching 2004 Chat headers are not in
   hand; see ../PROVENANCE.txt for the source and permission record.

   Retail identifies the body independently: its GETKEY format string is
   referenced only at 0x00861860, and the final call targets ciSocketSend at
   0x0085AC90 with &connection->chatSocket (connection + 0x1c). */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define VALID_NICK_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]\\`_^{|}-"

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef void (*ciConnectCallback)(CHAT chat, CHATBool success, int failureReason,
		void *param);

typedef void (*chatGetBasicUserInfoCallback)(CHAT chat, CHATBool success,
	const char *nick, const char *user, const char *address, void *param);

typedef struct ciCallbackGetBasicUserInfoParams
{
	CHATBool success;
	char *nick;
	char *user;
	char *address;
} ciCallbackGetBasicUserInfoParams;

typedef struct ciConnection
{
	int connected;
	CHATBool connecting;
	CHATBool disconnected;
	void *nickErrorCallback;
	unsigned char pad10[4];
	ciConnectCallback connectCallback;
	void *connectParam;
	unsigned char chatSocket;
	unsigned char pad1d[0x36c - 0x1d];
	char nick[1];
	unsigned char pad36d[0x3ac - 0x36d];
	char name[1];
	unsigned char pad3ad[0x42c - 0x3ad];
	char user[1];
	unsigned char pad42d[0x4ac - 0x42d];
	int namespaceID;
	unsigned char pad4b0[0x4f0 - 0x4b0];
	char profilernick[1];
	unsigned char pad4f1[0x774 - 0x4f1];
	char server[1];
	unsigned char pad775[0x8a8 - 0x775];
	int loginType;
} ciConnection;

void ciSocketSend(void *chatSocket, const char *buffer);
void ciSocketSendf(void *chatSocket, const char *format, ...);
void ciAddBANFilter(CHAT chat, const char *user, const char *channel);
CHATBool ciCheckFiltersForID(CHAT chat, int ID);
CHATBool ciCheckCallbacksForID(CHAT chat, int ID);
void ciAddCallback_(CHAT chat, int type, void *callback, void *params,
		void *callbackParam, int ID, void *param2, int paramsSize);
#define ciAddCallback(chat, type, callback, params, callbackParam, ID, param2) \
	ciAddCallback_(chat, type, callback, params, callbackParam, ID, param2, \
		sizeof(*(params)))
CHATBool ciGetUserBasicInfoA(CHAT chat, const char *nick,
	const char **user, const char **address);
int ciAddWHOFilter(CHAT chat, const char *user,
	chatGetBasicUserInfoCallback callback, void *param);
#define CALLBACK_GET_BASIC_USER_INFO 21

static CHATBool ciCheckForID(CHAT chat, int ID)
{
	return (CHATBool)(ciCheckFiltersForID(chat, ID) ||
		ciCheckCallbacksForID(chat, ID));
}

CHATBool ciCheckForIDAnchor(CHAT chat, int ID)
{
	return ciCheckForID(chat, ID);
}

void chatSetGlobalKeysA(CHAT chat, int num,
	const char **keys, const char **values)
{
	char buffer[512];
	const char *key;
	const char *value;
	int i;
	ciConnection *connection = (ciConnection *)chat;

	if(!connection || !connection->connected)
		return;

	if(!keys || !values)
		return;

	strcpy(buffer, "SETKEY :");
	for(i = 0 ; i < num ; i++)
	{
		key = keys[i];
		if(!key || !key[0])
			return;
		value = values[i];
		if(!value)
			value = "";
		sprintf(buffer + strlen(buffer), "\\%s\\%s", key, value);
	}

	ciSocketSend(&connection->chatSocket, buffer);
}

char *ciRandomCookie(void)
{
	static char cookie[4];
	static int nextCookie = 0;

	sprintf(cookie, "%03d", nextCookie++);
	nextCookie %= 1000;

	return cookie;
}

static void ciSendGetKey(CHAT chat,
						 const char *target,
						 const char *cookie,
						 int num,
						 const char **keys)
{
	char buffer[512];
	int len;
	int i;
	int j;
	int keyLen;
	ciConnection *connection = (ciConnection *)chat;

	assert(target && target[0]);
	assert(cookie && cookie[0]);
	assert(num >= 1);
	assert(keys);

	sprintf(buffer, "GETKEY %s %s 0 :", target, cookie);
	len = (int)strlen(buffer);

	for(i = 0 ; i < num ; i++)
	{
		if(!keys[i] || !keys[i][0])
			continue;

		keyLen = (int)strlen(keys[i]);
		if((len + keyLen + 1) >= (int)sizeof(buffer))
			return;

		buffer[len++] = '\\';
		memcpy(buffer + len, keys[i], (unsigned int)keyLen);
		for(j = len ; j < (len + keyLen) ; j++)
			if(buffer[j] == '\\')
				buffer[j] = '/';
		len += keyLen;
		buffer[len] = '\0';
	}

	ciSocketSend(&connection->chatSocket, buffer);
}

typedef void (*chatGetGlobalKeysCallback)(CHAT chat, CHATBool success,
	const char *user, int num, const char **keys, const char **values,
	void *param);

typedef void (*chatGetChannelKeysCallback)(CHAT chat, CHATBool success,
	const char *channel, const char *user, int num, const char **keys,
	const char **values, void *param);

int ciAddGETKEYFilter(CHAT chat, const char *cookie, int num,
	const char **keys, const char *channel,
	chatGetGlobalKeysCallback callback, void *param);
int ciAddGETCKEYFilter(CHAT chat, const char *cookie, int num,
	const char **keys, CHATBool channel, CHATBool getBroadcastKeys,
	chatGetChannelKeysCallback callback, void *param);
int ciAddGETCHANKEYFilter(CHAT chat, const char *cookie, int num,
	const char **keys, CHATBool getBroadcastKeys,
	chatGetChannelKeysCallback callback, void *param);
void msleep(unsigned int milliseconds);

typedef struct ciServerMessage
{
	char *message;
	char beforeCommand[16];
	char *command;
} ciServerMessage;

typedef struct ciServerMessageType
{
	const char *command;
	void (*handler)(CHAT chat, const ciServerMessage *message);
} ciServerMessageType;

extern int numServerMessageTypes;
extern ciServerMessageType serverMessageTypes[];

void ciSocketThink(void *chatSocket);
ciServerMessage *ciSocketRecv(void *chatSocket);
void ciHandleDisconnect(CHAT chat, const char *reason);
void ciFilterThink(CHAT chat);
void ciCallCallbacks(CHAT chat, int ID);

static __declspec(noinline) int ciProcessServerMessage(CHAT chat,
	const ciServerMessage *message)
{
	int i;

	for(i = 0 ; i < numServerMessageTypes ; i++)
	{
		if(_stricmp(message->command, serverMessageTypes[i].command) == 0)
		{
			if(serverMessageTypes[i].handler)
				serverMessageTypes[i].handler(chat, message);
			return 1;
		}
	}

	return 0;
}

typedef struct ciThinkConnection
{
	int connected;
	char beforeSocket[24];
	int socketOpaque;
	int connectState;
	char beforeRaw[0x7f8 - 0x24];
	void *rawCallback;
	char beforeParam[12];
	void *callbackParam;
} ciThinkConnection;

static __declspec(noinline) void ciThink(CHAT chat, int ID)
{
	ciServerMessage *message;
	ciThinkConnection *connection = (ciThinkConnection *)chat;

	if(connection->connectState == 1)
	{
		ciSocketThink(&connection->socketOpaque);
		while((message = ciSocketRecv(&connection->socketOpaque)) != 0)
		{
			if(connection->rawCallback)
			{
				struct
				{
					const char *raw;
				} params;

				params.raw = message->message;
				ciAddCallback_(chat, 0, connection->rawCallback, &params,
					connection->callbackParam, 0, 0, sizeof(params));
			}
			ciProcessServerMessage(chat, message);
		}

		if(connection->connectState == 2)
			ciHandleDisconnect(chat, "Disconnected");
	}

	ciFilterThink(chat);
	ciCallCallbacks(chat, ID);
}

void chatGetBasicUserInfoA(CHAT chat, const char *nick,
	chatGetBasicUserInfoCallback callback, void *param, int blocking)
{
	const char *user;
	const char *address;
	int ID;
	ciConnection *connection = (ciConnection *)chat;

	if(!connection || !connection->connected)
		return;

	if(ciGetUserBasicInfoA(chat, nick, &user, &address))
	{
		ciCallbackGetBasicUserInfoParams params;

		params.success = CHATTrue;
		params.nick = (char *)nick;
		params.user = (char *)user;
		params.address = (char *)address;
		ID = ciGetNextID(chat);
		ciAddCallback(chat, CALLBACK_GET_BASIC_USER_INFO, callback,
			&params, param, ID, NULL);
	}
	else
	{
		ciSocketSendf(&connection->chatSocket, "WHO %s", nick);
		ID = ciAddWHOFilter(chat, nick, callback, param);
	}

	if(blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while(ciCheckFiltersForID(chat, ID) ||
			ciCheckCallbacksForID(chat, ID));
	}
}

void chatGetGlobalKeysA(CHAT chat,
	const char *target, int num, const char **keys,
	chatGetGlobalKeysCallback callback, void *param, CHATBool blocking)
{
	char *cookie;
	const char *channel;
	int ID;
	ciConnection *connection = (ciConnection *)chat;

	if(!connection || !connection->connected)
		return;

	assert(num >= 0);
	assert(keys);

	if(!target || !target[0])
		target = connection->nick;

	cookie = ciRandomCookie();
	ciSendGetKey(chat, target, cookie, num, keys);

	if(target[0] == '#')
		channel = target;
	else
		channel = NULL;
	ID = ciAddGETKEYFilter(chat, cookie, num, keys, channel, callback, param);

	if(blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while(ciCheckForID(chat, ID));
	}
}

/* Keep the TU-local SDK helper reachable in this partial reconstruction.  In
   the complete SDK chatGetGlobalKeys calls it; retaining a caller also lets
   VC7.1 reproduce the helper's internal register argument assignment. */
void ciSendGetKeyAnchor(CHAT chat,
						const char *target,
						const char *cookie,
						int num,
						const char **keys)
{
	ciSendGetKey(chat, target, cookie, num, keys);
}

void chatSetChannelKeysA(CHAT chat,
						 const char *channel,
						 const char *user,
						 int num,
						 const char **keys,
						 const char **values)
{
	char buffer[512];
	const char *value;
	int i;
	ciConnection *connection = (ciConnection *)chat;
	if(!connection || *(int *)connection == 0)
		return;

	if(!user || !user[0])
		sprintf(buffer, "SETCHANKEY %s :", channel);
	else
		sprintf(buffer, "SETCKEY %s %s :", channel, user);
	for(i = 0 ; i < num ; i++)
	{
		value = values[i];
		if(!value)
			value = "";
		sprintf(buffer + strlen(buffer), "\\%s\\%s", keys[i], value);
	}

	ciSocketSend(&connection->chatSocket, buffer);
}

static CHATBool ciSendGetChannelKey(CHAT chat,
									const char *channel,
									const char *nick,
									const char *cookie,
									int num,
									const char **keys)
{
	char buffer[512];
	int len;
	int i;
	int j;
	int keyLen;
	CHATBool getBrocastKeys = CHATFalse;
	ciConnection *connection = (ciConnection *)chat;

	assert(channel && channel[0]);
	assert(cookie && cookie[0]);
	assert(!num || keys);

	if(!nick || !nick[0])
		sprintf(buffer, "GETCHANKEY %s %s 0 :", channel, cookie);
	else
		sprintf(buffer, "GETCKEY %s %s %s 0 :", channel, nick, cookie);
	len = (int)strlen(buffer);

	for(i = 0 ; i < num ; i++)
	{
		if(!keys[i] || !keys[i][0])
			continue;

		if(strcmp(keys[i], "b_*") == 0)
		{
			getBrocastKeys = CHATTrue;
			continue;
		}

		keyLen = (int)strlen(keys[i]);
		if((len + keyLen + 1) >= (int)sizeof(buffer))
			continue;

		buffer[len++] = '\\';
		memcpy(buffer + len, keys[i], (unsigned int)keyLen);
		for(j = len ; j < (len + keyLen) ; j++)
			if(buffer[j] == '\\')
				buffer[j] = '/';
		len += keyLen;
		buffer[len] = '\0';
	}

	if(getBrocastKeys)
	{
		if((len + 4) < (int)sizeof(buffer))
		{
			strcpy(buffer + len, "\\b_*");
			len += 4;
		}
	}

	if(!num && (!nick || !nick[0]))
	{
		strcpy(buffer + len, "*");
		len++;
	}

	ciSocketSend(&connection->chatSocket, buffer);

	return getBrocastKeys;
}

CHATBool ciSendGetChannelKeyAnchor(CHAT chat,
									 const char *channel,
									 const char *nick,
									 const char *cookie,
									 int num,
									 const char **keys)
{
	return ciSendGetChannelKey(chat, channel, nick, cookie, num, keys);
}

void chatGetChannelKeysA(CHAT chat,
						 const char *channel,
						 const char *user,
						 int num,
						 const char **keys,
						 chatGetChannelKeysCallback callback,
						 void *param,
						 CHATBool blocking)
{
	char *cookie;
	int ID;
	CHATBool getBroadcastKeys;
	ciConnection *connection = (ciConnection *)chat;

	if(!connection || !connection->connected)
		return;

	assert(num >= 0);
	assert(!num || keys);

	cookie = ciRandomCookie();
	getBroadcastKeys = ciSendGetChannelKey(chat, channel, user, cookie, num, keys);
	if(!user || !user[0])
		ID = ciAddGETCHANKEYFilter(chat, cookie, num, keys,
			getBroadcastKeys, callback, param);
	else
		ID = ciAddGETCKEYFilter(chat, cookie, num, keys,
			(CHATBool)(strcmp(user, "*") == 0), getBroadcastKeys,
			callback, param);

	if(blocking)
	{
		do
		{
			ciThink(chat, ID);
			msleep(10);
		}
		while(ciCheckFiltersForID(chat, ID) ||
			ciCheckCallbacksForID(chat, ID));
	}
}

int ciNickIsValid(const char *nick)
{
	if((NULL == nick) || ('\0' == *nick))
		return CHATFalse;

	if(isdigit(*nick) || (*nick == '-'))
		return CHATFalse;

	while(*nick != '\0')
	{
		if(NULL == strchr(VALID_NICK_CHARS, *nick++))
			return CHATFalse;
	}

	return CHATTrue;
}

void ciNickError(CHAT chat, int type, const char *nick,
		int numSuggestedNicks, char **suggestedNicks)
{
	typedef struct ciCallbackNickErrorParams
	{
		int type;
		char *nick;
		int numSuggestedNicks;
		char **suggestedNicks;
	} ciCallbackNickErrorParams;
	ciConnection *connection = (ciConnection *)chat;

	if(connection->nickErrorCallback)
	{
		ciCallbackNickErrorParams params;

		memset(&params, 0, sizeof(ciCallbackNickErrorParams));
		params.type = type;
		params.nick = (char *)nick;
		params.numSuggestedNicks = numSuggestedNicks;
		params.suggestedNicks = suggestedNicks;
		ciAddCallback(chat, 25, connection->nickErrorCallback, &params,
			connection->connectParam, 0, NULL);
	}
	else
	{
		connection->connecting = CHATFalse;

		if(connection->connectCallback != NULL)
			connection->connectCallback(chat, CHATFalse, 1,
				connection->connectParam);
	}
}

void ciSendNick(CHAT chat)
{
	const char *nick;
	ciConnection *connection = (ciConnection *)chat;

	if(connection->loginType == 0)
	{
		nick = connection->nick;
	}
	else if((connection->loginType == 2) && (connection->namespaceID == 0))
	{
		nick = connection->profilernick;
	}
	else
	{
		nick = "*";
		goto sendNick;
	}

	if(!ciNickIsValid(nick))
	{
		ciNickError(chat, 1, nick, 0, NULL);
		return;
	}

sendNick:
	ciSocketSendf(&connection->chatSocket, "NICK %s", nick);
}

void ciSendNickAndUser(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	ciSocketSendf(&connection->chatSocket, "USER %s %s %s :%s",
		connection->user,
		"127.0.0.1",
		connection->server,
		connection->name);
	ciSendNick(chat);
}

/* Two one-liners off the same connection.  chatGetNickA returns the empty
   string rather than NULL when there is no connection, and returns a pointer
   INTO the connection rather than a copy -- retail computes connection+0x36C
   and returns it, which is what fixes nick[] as an inline buffer.

   chatSendRawA's guard is the pair, not the single flag every neighbour
   tests: it goes out while still connecting, so the test is connected OR
   connecting.  It tail-jumps into ciSocketSend with the raw buffer left
   where it arrived. */

char *chatGetNickA(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!connection->connected)
		return "";

	return connection->nick;
}

void chatSendRawA(CHAT chat, const char *raw)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!chat)
		return;

	if(!connection->connected && !connection->connecting)
		return;

	ciSocketSend(&connection->chatSocket, raw);
}

void chatRetryWithNickA(CHAT chat, const char *nick)
{
	int validateNick;
	ciConnection *connection = (ciConnection *)chat;

	if(connection->connected)
		return;

	if(nick == NULL)
	{
		connection->connecting = CHATFalse;

		if(connection->connectCallback != NULL)
			connection->connectCallback(chat, CHATFalse, 1,
				connection->connectParam);

		return;
	}

	strncpy(connection->nick, nick, 64);
	connection->nick[63] = '\0';

	validateNick = ciNickIsValid(nick);
	if(!validateNick)
	{
		ciNickError(chat, 1, nick, 0, NULL);
		return;
	}

	ciSocketSendf(&connection->chatSocket, "NICK :%s", nick);
}

void chatBanUserA(CHAT chat, const char *channel, const char *user)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!connection || !connection->connected)
		return;

	ciSocketSendf(&connection->chatSocket, "WHOIS %s", user);
	ciAddBANFilter(chat, user, channel);
}
