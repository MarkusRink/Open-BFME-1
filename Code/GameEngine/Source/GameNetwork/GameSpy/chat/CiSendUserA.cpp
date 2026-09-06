// _ciSendUserA
// cl: /DNDEBUG /MD
// GameSpy Chat SDK chatMain.c body (gap at 0x00860280), ported as a C++ ABI
// slice: sends the IRC USER registration line from the connection fields.

typedef void *CHAT;

typedef struct ciConnection
{
	int connected;
	char reserved0[0x1C - 4];
	char chatSocket[1];
	char reserved1[0x3AC - 0x1D];
	char name[1];
	char reserved2[0x42C - 0x3AD];
	char user[1];
	char reserved3[0x774 - 0x42D];
	char server[1];
} ciConnection;

extern "C" void ciSocketSendf(void *socket, const char *format, ...);

extern "C" void ciSendUserA(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	ciSocketSendf(&connection->chatSocket, "USER %s %s %s :%s",
		connection->user, "127.0.0.1", connection->server, connection->name);
}
