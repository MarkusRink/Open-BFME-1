// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport

#include <string>

typedef void *PEER;
typedef int Int;
typedef unsigned int UnsignedInt;

enum RoomType
{
	GroupRoom,
	StagingRoom
};

class PeerThreadClass
{
public:
	Int lookupStatForPlayer(RoomType, const char *, const char *);
};

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	AsciiString(const char *);
	~AsciiString() { releaseBuffer(); }
	void format(AsciiString, ...);
	const char *str() const { return m_text ? m_text + 8 : ""; }

private:
	void releaseBuffer();
	char *m_text;
};

extern void peerGetPlayerInfoNoWait(PEER, const char *, UnsignedInt *, Int *);
extern void peerGetPlayerFlags(PEER, const char *, RoomType, Int *);

class PeerResponse
{
public:
	int peerResponseType;

	std::string groupRoomName;
	std::string nick;
	std::string oldNick;
	std::wstring text;
	std::string locale;
	std::string stagingServerGameOptions;
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;
	std::string stagingRoomPlayerNames[8];
	std::string command;
	std::string commandOptions;

	union
	{
		struct
		{
			Int profileID;
			Int wins;
			Int losses;
			int roomType;
			Int flags;
			UnsignedInt IP;
			Int rankPoints;
			Int side;
			Int preorder;
			char unknown[0x20c];
			Int rank1v1;
			Int rank2v2;
			Int lastLadder;
		} player;
		int words[143];
	};
};

typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];

class PeerRequest;

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread(void) = 0;
	virtual void endThread(void) = 0;
	virtual bool isThreadRunning(void) = 0;
	virtual bool isConnected(void) = 0;
	virtual bool isConnecting(void) = 0;
	virtual void addRequest(const PeerRequest &) = 0;
	virtual bool getRequest(PeerRequest &) = 0;
	virtual void addResponse(const PeerResponse &) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

static void getPlayerInfo(PeerThreadClass *thread,
	PEER peer, const char *nick, Int &id, UnsignedInt &ip, std::string &locale,
	Int &wins, Int &losses, Int &rankPoints, Int &side, Int &preorder,
	RoomType roomType, Int &flags, Int &rank1v1, Int &rank2v2,
	Int &lastLadder)
{
	if (!thread || !nick)
		return;
	peerGetPlayerInfoNoWait(peer, nick, &ip, &id);
	Int localeIndex = thread->lookupStatForPlayer(roomType, nick, "b_locale");
	AsciiString tmp;
	tmp.format("%d", localeIndex);
	locale = tmp.str();
	wins = thread->lookupStatForPlayer(roomType, nick, "b_wins");
	losses = thread->lookupStatForPlayer(roomType, nick, "b_losses");
	rankPoints = thread->lookupStatForPlayer(roomType, nick, "b_points");
	side = thread->lookupStatForPlayer(roomType, nick, "b_side");
	preorder = thread->lookupStatForPlayer(roomType, nick, "b_pre");
	rank1v1 = thread->lookupStatForPlayer(roomType, nick, "b_rank1v1");
	rank2v2 = thread->lookupStatForPlayer(roomType, nick, "b_rank2v2");
	lastLadder = thread->lookupStatForPlayer(roomType, nick, "b_lastLadder");
	flags = 0;
	peerGetPlayerFlags(peer, nick, roomType, &flags);
}

#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=?j_00042069@@YAXXZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=?j_00044733@@YAXXZ")

#pragma optimize("y", on)
void playerChangedNickCallback(PEER peer, RoomType roomType,
	const char *oldNick, const char *newNick, void *param)
{
	PeerResponse resp;
	resp.peerResponseType = 12;
	resp.nick = newNick;
	resp.oldNick = oldNick;
	resp.player.roomType = roomType;

	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
		return;

	getPlayerInfo(t, peer, newNick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		roomType, resp.player.flags, resp.player.rank1v1,
		resp.player.rank2v2, resp.player.lastLadder);
	TheGameSpyPeerMessageQueue->addResponse(resp);
}
#pragma optimize("y", off)
