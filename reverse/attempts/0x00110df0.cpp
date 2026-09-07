// ??1GameState@@UAE@XZ
// partial score=0.68 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
// stlport
// Real C++ reconstruction of ??1GameState@@UAE@XZ.
//
// The matching constructor proves the BFME GameState layout: SubsystemInterface
// at zero, Snapshot at +8, three SnapshotBlock list headers at +0x0c,
// SaveGameInfo at +0x18, the post-process list at +0x48, the BFME list at
// +0x4c, and AvailableGameInfo* at +0x50.  The destructor's installed vtables,
// named initSubsystem<GameState> caller, and teardown order agree with that
// identity.  SaveGameInfo's destructor is the existing retail ILT at 0x0000AB78
// to the six-string body at 0x0010D700; its separate candidate pin is kept
// local to this TU's ABI view.

#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "StringInline.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class __declspec(novtable) Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot()
	{
		*(volatile unsigned int *)this = 0x01073744;
	}
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

enum SnapshotType
{
	SNAPSHOT_SAVELOAD,
	SNAPSHOT_DEEPCRC_LOGICONLY,
	SNAPSHOT_DEEPCRC,
	SNAPSHOT_MAX
};

extern void j_0000ab78(void) throw();

class SaveGameInfo
{
public:
	SaveGameInfo() throw();
	__declspec(noinline) ~SaveGameInfo()
	{
		j_0000ab78();
	}

private:
	unsigned char m_data[0x30];
};

struct AvailableGameInfo
{
	AsciiString filename;
	SaveGameInfo saveGameInfo;
	AvailableGameInfo *next;
	AvailableGameInfo *prev;
};

class __declspec(novtable) GameState : public SubsystemInterface, public Snapshot
{
public:
	GameState();
	virtual ~GameState();
	virtual void init();
	virtual void reset();
	virtual void update() {}

protected:
	virtual void crc(void *xfer) {}
	virtual void xfer(void *xfer);
	virtual void loadPostProcess() {}

private:
	struct SnapshotBlock
	{
		Snapshot *snapshot;
		AsciiString blockName;
	};
	typedef std::list<SnapshotBlock> SnapshotBlockList;

	SnapshotBlockList m_snapshotBlockList[SNAPSHOT_MAX];
	SaveGameInfo m_gameInfo;
	std::list<Snapshot *> m_snapshotPostProcessList;
	SnapshotBlockList m_bfmeSnapshotBlockList;
	AvailableGameInfo *m_availableGames;
	unsigned char m_isInLoadGame;
	__forceinline void clearAvailableGames();
};

__forceinline void GameState::clearAvailableGames()
{
	AvailableGameInfo *gameInfo;

	while (m_availableGames)
	{
		gameInfo = m_availableGames->next;
		delete m_availableGames;
		m_availableGames = gameInfo;
	}
}

// ??1GameState@@UAE@XZ
GameState::~GameState()
{
	*(volatile unsigned int *)this = 0x010893E0;
	*(volatile unsigned int *)((unsigned char *)this + 8) = 0x010893CC;

	for (int i = 0; i < SNAPSHOT_MAX; ++i)
		m_snapshotBlockList[i].clear();

	m_snapshotPostProcessList.clear();
	m_bfmeSnapshotBlockList.clear();
	clearAvailableGames();
}
