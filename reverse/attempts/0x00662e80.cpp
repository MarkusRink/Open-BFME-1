// ?queueLocalCommand@BFMEConnectionManager@@QAEXPAX@Z
// partial score=0.6 date=2026-09-07
// cl: /DNDEBUG /MD /GX

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

typedef bool Bool;
typedef unsigned short UnsignedShort;

void __cdecl operator delete(void *block) throw();

enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_LOADCOMPLETE = 16,
	NETCOMMANDTYPE_TIMEOUTSTART = 17,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_FILEANNOUNCE = 20,
	NETCOMMANDTYPE_FILEPROGRESS = 21,
	NETCOMMANDTYPE_PLAYERFRAMERATIOS = 22
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg();
	virtual int getSortNumber();
	virtual void prepareForRelay();
	void attach();
	void detach();

	void setExecutionFrame(unsigned int frame) { m_executionFrame = frame; }
	unsigned int getExecutionFrame() { return m_executionFrame; }
	void setPlayerID(unsigned int playerID) { m_playerID = playerID; }
	unsigned int getPlayerID() { return m_playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	void setNetCommandType(NetCommandType type) { m_commandType = type; }
	NetCommandType getNetCommandType() { return m_commandType; }

protected:
	unsigned int m_timestamp;
	unsigned int m_executionFrame;
	unsigned int m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	int m_referenceCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFrameCommandMsg : public NetCommandMsg
{
public:
	NetFrameCommandMsg() : NetCommandMsg()
	{
		m_frame = 0;
		m_playerFrame = 0;
		m_commandCount = -1;
		m_commandType = NETCOMMANDTYPE_FRAMEINFO;
	}

	void setFrame(unsigned int frame) { m_frame = frame; }
	unsigned int getFrame() { return m_frame; }
	unsigned int getPlayerFrame() { return m_playerFrame; }
	void setPlayerFrame(unsigned int frame) { m_playerFrame = frame; }
	int getCommandCount() { return m_commandCount; }
	void setCommandCount(int count) { m_commandCount = count; }

private:
	unsigned int m_frame;
	unsigned int m_playerFrame;
	int m_commandCount;
};

class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	NetAckBothCommandMsg(NetCommandMsg *msg);
	UnsignedShort getCommandID();
	unsigned char getOriginalPlayerID();
	unsigned int getOriginalExecutionFrame() { return m_originalExecutionFrame; }
private:
	UnsignedShort m_commandID;
	unsigned char m_originalPlayerID;
	unsigned int m_originalExecutionFrame;
};

class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	NetAckStage1CommandMsg(NetCommandMsg *msg);
private:
	UnsignedShort m_commandID;
	unsigned char m_originalPlayerID;
	unsigned int m_originalExecutionFrame;
};

class NetAckStage2CommandMsg : public NetCommandMsg
{
public:
	NetAckStage2CommandMsg(NetCommandMsg *msg);
	UnsignedShort getCommandID();
	unsigned char getOriginalPlayerID();
	unsigned int getOriginalExecutionFrame() { return m_originalExecutionFrame; }
private:
	UnsignedShort m_commandID;
	unsigned char m_originalPlayerID;
	unsigned int m_originalExecutionFrame;
};

class GameMessage;
class GameMessageArgument;

// The constructor at RVA 0x00674A40 copies a GameMessage's type and arguments.
// Its 0x30-byte allocation and field stores agree with the upstream layout.
class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg(GameMessage *msg);

private:
	int m_numArgs;
	int m_argSize;
	int m_type;
	GameMessageArgument *m_argList;
	GameMessageArgument *m_argTail;
};

Bool DoesCommandRequireACommandID(NetCommandType type);
Bool CommandRequiresDirectSend(NetCommandMsg *msg);
Bool IsCommandSynchronized(NetCommandType type);
UnsignedShort GenerateNextCommandID();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
	public:
	unsigned char getRelay() { return relay; }
	NetCommandMsg *getCommand() { return msg; }
	NetCommandRef *getNext() { return next; }
	~NetCommandRef();
	NetCommandMsg *msg;
	NetCommandRef *next;
	NetCommandRef *prev;
	unsigned char relay;
};

class NetCommandList
{
public:
	NetCommandRef *getFirstMessage() { return m_first; }
	NetCommandRef *findMessage(UnsignedShort id, unsigned char player);
	NetCommandRef *findMessage(UnsignedShort id, unsigned char player, unsigned int frame);
	void removeMessage(NetCommandRef *ref);
private:
	void *m_vtable;
	NetCommandRef *m_first;
};

class BFMENetInformPlayerLeaveFrameCommandMsg : public NetCommandMsg
{
public:
	unsigned int getLeaveFrame();
	int getLeavingPlayerID();
};

class BFMENetRequestFrameDataCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestFrameDataCommandMsg();
	void setFirstFrame(unsigned int firstFrame);
	void setLastFrame(unsigned int lastFrame);
	unsigned int getFirstFrame();
	unsigned int getLastFrame();
private:
	unsigned int m_firstFrame;
	unsigned int m_lastFrame;
};

class BFMENetRequestPlayerLeaveCommandMsg
{
public:
	int getRequestedPlayerID();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
	public:
	void processProgressComplete(int playerID);
	void timeOutGameStart();
	unsigned int getFrame() { return frame; }
	char unknown[0x3C];
	unsigned int frame;
};

extern GameLogic *TheGameLogic;

class GameClient;

struct GameClientVTable
{
	void *unknown[26];
	unsigned int (__fastcall *getFrame)(GameClient *gameClient);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	unsigned int getFrame() { return vtable->getFrame(this); }

private:
	GameClientVTable *vtable;
};

extern GameClient *TheGameClient;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char unknown[0xCB4];
	unsigned int networkRunAheadSlack;
};

extern GlobalData *TheWritableGlobalData;
extern unsigned int g_lastPacketRouterStallFrame;
extern int FRAMES_TO_KEEP;

template <class T> const T &frameMaximum(const T &a, const T &b)
{
	return b > a ? b : a;
}

template <class T> const T &frameMinimum(const T &a, const T &b)
{
	return b < a ? b : a;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FrameDataManager.h
class FrameDataManager
{
public:
	NetCommandList *getFrameCommandList(unsigned int frame);
	Bool getIsQuitting();
	unsigned int getCommandCount(unsigned int frame);
	unsigned int getFrameCommandCount(unsigned int frame);
	NetCommandRef *addNetCommandMsg(NetCommandMsg *msg);
	void setFrameCommandCount(unsigned int frame, unsigned int count);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/Connection.h
struct NetPacketAddress
{
	unsigned int ip;
	unsigned short port;
};

class Connection
{
	public:
	NetPacketAddress getAddress() { return m_address; }
	void sendNetCommandMsg(NetCommandMsg *msg, unsigned char relay);
	int m_openState;
	char m_unknown04[8];
	NetPacketAddress m_address;
	char m_unknown14[0x338];
	unsigned int m_lastHeardFrom;
};

// Retail's real ConnectionManager, named so these two bodies carry their true
// mangled names; the BFME-native helpers below keep the BFMEConnectionManager
// name because theirs are unknown.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class DisconnectManager;
class NetDisconnectChatCommandMsg;
class NetProgressCommandMsg;
class NetFileAnnounceCommandMsg;
class NetFileProgressCommandMsg;

class ConnectionManager
{
public:
	void sendLocalCommand(NetCommandMsg *msg, unsigned char relay);
	void sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay);
	int getNumPlayers();
	friend class BFMEConnectionManager;
	unsigned int getPacketRouterSlot();

private:
	void processDisconnectChat(NetDisconnectChatCommandMsg *msg);
	void processProgress(NetProgressCommandMsg *msg);
	void processFileAnnounce(NetFileAnnounceCommandMsg *msg);
	void processFileProgress(NetFileProgressCommandMsg *msg);
	char m_unknown00[4];
	Connection *m_connections[8];
	char m_unknown24[0x12004];
	unsigned int m_localSlot;
	unsigned int m_packetRouterSlot;
	char m_unknown12030[0xB4];
	FrameDataManager *m_frameData[8];
};

class BFMEConnectionManager
{
public:
	Bool isPlayerConnectedDefaultTimeout(int playerID);
	Bool isPlayerConnectedForTimeout(int playerID, unsigned int timeout);
	Bool hasPacketRouterFrameStall();
	void processRequestFrameDataCommand(void *msg);
	Bool areFrameCommandsComplete(unsigned int frame, Bool debugSpewage);
	int getFrameHeadroom();
	void processInformPlayerLeaveFrameCommand(void *msg);
	void sendFrameInfo();
	Bool processIncomingCommand(void *ref);
	void *construct();
	void init();
	void computePlayerFrameRatios();
	int isPlayerInGame(int slot);
	int isPlayerSlotActive(int slot);
	void processRequestPlayerLeaveCommand(void *msg);
	void relayCommand(void *ref);
	void update();
	void runRelayPass();
	void destroy();
	void processWrappedCommand(void *msg);
	void sendFileChunk(const char *path, int playerMask, int chunk);
	void updateFileProgress();
	void buildPlayerStatusText(void *out);
	void ackCommand(NetCommandRef *ref, NetPacketAddress *source);
	void sendGameCommand(void *msg);
	void decideCommandRelay(void *msg);
	void getPlayerNameForSlot(void *out, int slot);
	void sendPlayerLeaveCommands();
	void sendFrameInfoToPlayer(int slot);
	void sendDisconnectChatCommand(void *text);
	void sendDisconnectVoteCommand(int slot, unsigned int frame);
	void sendGameSpyStatsAuthKey(void *key);
	void sendKeepAliveCommand();
	void sendProgressCommand(int percent);
	void sendDisconnectFrameCommand();
	void sendDisconnectScreenOffCommand(int slot);
	void sendRequestPlayerLeaveCommand();
	void sendLoadCompleteCommand();
	void attachPlayersFromGameInfo(void *gameInfo);
	void resolvePlayerFromName(void *msg);
	void sendFileToPlayers(const char *path);
	void sendFileAnnouncement(const char *path, int playerMask);
	void processAck(NetCommandMsg *msg);
	void processGameSpyStatsAuthKeyCommand(void *msg);
	void processAckCommand(void *msg);
	void beginPlayerLeave(void *msg);
	void resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame);

private:
	char m_unknown00[4];
	Connection *m_connections[8];
	char m_unknown24[0x12004];
	int m_localSlot;
	int m_packetRouterSlot;
	unsigned int m_playerFrameRatios[8];
	char m_unknown12050[0xC];
	unsigned int m_frameCeiling;
	unsigned int m_playerLatestFrame[8];
	int m_playerState[8];
	unsigned int m_playerClientFrame[8];
	char m_unknown120C0[0x20];
	DisconnectManager *m_disconnectManager;
	FrameDataManager *m_frameData[8];
	NetCommandList *m_pendingCommands;
	NetCommandList *m_pendingRelays;
};


// Retail's real DisconnectManager, for the one body here whose true mangled name
// is known. Protected, to match the IAE in the decorated name.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
public:
	// Public in the reference's header, so QAE in the decorated names.
	void processDisconnectCommand(NetCommandRef *ref, ConnectionManager *conMgr);
	DisconnectManager();
	void init();
protected:
	// Protected there, so IAE.
	void processDisconnectFrame(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr);
};

class BFMEDisconnectManager
{
public:
	void update(void *conMgr);
};

void BFMEConnectionManager::ackCommand(NetCommandRef *ref, NetPacketAddress *source)
{
	NetCommandMsg *ack = 0;
	NetCommandMsg *original = ref->getCommand();
	unsigned char connected = 0;
	if (m_connections[0] != 0 && m_connections[0]->m_openState == -1) connected |= 1;
	if (m_connections[1] != 0 && m_connections[1]->m_openState == -1) connected |= 2;
	if (m_connections[2] != 0 && m_connections[2]->m_openState == -1) connected |= 4;
	if (m_connections[3] != 0 && m_connections[3]->m_openState == -1) connected |= 8;
	if (m_connections[4] != 0 && m_connections[4]->m_openState == -1) connected |= 16;
	if (m_connections[5] != 0 && m_connections[5]->m_openState == -1) connected |= 32;
	if (m_connections[6] != 0 && m_connections[6]->m_openState == -1) connected |= 64;
	if (m_connections[7] != 0 && m_connections[7]->m_openState == -1) connected |= 128;
	if ((connected & ref->getRelay()) == 0)
		ack = new NetAckBothCommandMsg(ref->getCommand());
	else
		ack = new NetAckStage1CommandMsg(ref->getCommand());
	ack->setPlayerID(m_localSlot);
	if (CommandRequiresDirectSend(original))
	{
		if (original->getPlayerID() >= 0 && original->getPlayerID() < 8)
		{
			if (m_connections[original->getPlayerID()] != 0)
				m_connections[original->getPlayerID()]->sendNetCommandMsg(ack, 1 << original->getPlayerID());
		}
	}
	else
	{
		for (unsigned char player = 0; player < 8; ++player)
		{
			if (m_connections[player] != 0 && source != 0)
			{
				NetPacketAddress address = m_connections[player]->getAddress();
				if (address.ip == source->ip && address.port == source->port)
				{
					m_connections[player]->sendNetCommandMsg(ack, 1 << player);
					return;
				}
			}
		}
		if ((unsigned int)m_packetRouterSlot < 8)
		{
			if (m_connections[m_packetRouterSlot] != 0)
				m_connections[m_packetRouterSlot]->sendNetCommandMsg(ack, 1 << m_packetRouterSlot);
			else if (m_localSlot == m_packetRouterSlot)
			{
				int playerID = original->getPlayerID();
				if ((unsigned int)playerID < 8)
				{
					if (m_connections[playerID] != 0)
						m_connections[playerID]->sendNetCommandMsg(ack, 1 << playerID);
				}
			}
		}
	}
	ack->detach();
}

