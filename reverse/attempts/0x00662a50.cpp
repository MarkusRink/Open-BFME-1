// ?isPlayerConnectedDefaultTimeout@BFMEConnectionManager@@QAE_NH@Z
// partial score=0.9 date=2026-09-07
// cl: /DNDEBUG /MD /GX
// Banked default timeout reconstruction, retail RVA 0x00662A50, 138 bytes.
typedef bool Bool;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class Connection
{
public:
 unsigned int getLastHeardFrom() { return m_lastHeardFrom; }
 char unknown[0x34C];
 unsigned int m_lastHeardFrom;
};
class GameLogic
{
public:
 unsigned int getFrame() { return frame; }
 char unknown[0x3C];
 unsigned int frame;
};
class GlobalData
{
public:
 char unknown[0xCBC];
 unsigned int networkPlayerTimeoutTime;
};
extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
// Needs DIR32 pin ?g_bfmeStartupGraceEndFrame@@3IB at RVA 0x00CEAD50.
extern const unsigned int g_bfmeStartupGraceEndFrame;
class BFMEConnectionManager
{
public:
 Bool isPlayerConnectedDefaultTimeout(int playerID);
private:
 char unknown00[4];
 Connection *m_connections[8];
 char unknown24[0x12004];
 int m_localSlot;
};
Bool BFMEConnectionManager::isPlayerConnectedDefaultTimeout(int playerID)
{
	if (playerID == m_localSlot)
		return true;
	Connection *connection = m_connections[playerID];
	if (connection)
	{
		if (!connection->m_lastHeardFrom)
			connection->m_lastHeardFrom = timeGetTime();
		else
		{
			unsigned int now = timeGetTime();
			if (TheGameLogic->getFrame() >= g_bfmeStartupGraceEndFrame)
				return TheWritableGlobalData->networkPlayerTimeoutTime < now - connection->getLastHeardFrom() ? false : true;
			return TheWritableGlobalData->networkPlayerTimeoutTime * 4 < now - connection->getLastHeardFrom() ? false : true;
		}
	}
	return true;
}

