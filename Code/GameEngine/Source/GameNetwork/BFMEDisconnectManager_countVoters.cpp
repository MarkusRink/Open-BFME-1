// cl: /DNDEBUG /MD /EHsc

// Retail 0x0066BB60, BFMEDisconnectManager::countVoters(void *connectionManager).
//
// Same predicate triple as DisconnectManager::getVotesNeededToKick (0x0066BBC0),
// without skipping the slot under vote. The last predicate is called even when
// the connection-manager pointer is null, matching the retail join point.

typedef int Int;

typedef bool Bool;

class ConnectionManager
{
public:
	Bool isPlayerConnected(Int slot);
	Bool _bfme_slotIsLocalOrLive(Int slot);
};

class BFMEDisconnectManager
{
public:
	Int countVoters(void *connectionManager);
};

class BFMEConnectionManager : public ConnectionManager
{
public:
	Bool isPlayerInGame(Int slot);
};

Int BFMEDisconnectManager::countVoters(void *connectionManager)
{
	BFMEConnectionManager *manager = (BFMEConnectionManager *)connectionManager;
	Int voters = 0;
	for (Int slot = 0; slot < 8; ++slot)
	{
		if ((unsigned int)slot >= 8)
			continue;
		if (manager && !manager->isPlayerConnected(slot))
			continue;
		if (manager && !manager->_bfme_slotIsLocalOrLive(slot))
			continue;
		if (!manager->isPlayerInGame(slot))
			++voters;
	}
	return voters;
}
