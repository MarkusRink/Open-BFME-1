// _chatInviteUserA
// cl: /DNDEBUG /MD
// GameSpy Chat SDK chatMain.c body (gap at 0x008614E0), ported as a C++ ABI slice
// after ChatChangeNickA.cpp.

typedef void *CHAT;

typedef struct ciConnection
{
	int connected;
	char reserved0[0x1C - 4];
	char chatSocket[1];
} ciConnection;

extern "C" void ciSocketSendf(void *socket, const char *format, ...);

extern "C" void chatInviteUserA(CHAT chat, const char *channel, const char *user)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected)
		return;

	ciSocketSendf(&connection->chatSocket, "INVITE %s %s", user, channel);
}
