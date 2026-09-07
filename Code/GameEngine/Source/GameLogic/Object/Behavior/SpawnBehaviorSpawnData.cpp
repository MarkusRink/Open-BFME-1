// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: the three SpawnBehaviorModuleData members that write the spawn
// block -- the run of INI fields a modder fills in to say what a structure
// spawns, how many, and when.
//
//   ?setSpawnData@        0x0061A860, 83 bytes
//   ?resetSpawnData@      0x0061AB60, 68 bytes
//   ?resetSpawnDataFull@  0x0061B100, 85 bytes
//
// Set it, clear it, clear it harder. resetSpawnDataFull is resetSpawnData plus
// two fields further up the class -- the flag at +0xA8 and the pointer at +0xB4
// it rebuilds -- which is the only thing that distinguishes them and was not
// visible while they sat in two files.
//
// The three named the SAME seven members three different ways. setSpawnData
// called them m_spawnNumber / m_startNumber / m_replaceDelay / m_oneShot /
// m_reclaimOrphans / m_names / m_requireSpawner; the two resets called the same
// offsets m_spawnNumberData / m_spawnStartNumberData / m_spawnReplaceDelayData /
// m_isOneShotData / m_canReclaimOrphans / m_spawnTemplateNameData /
// m_spawnedRequireSpawner. One set of names below, the resets' -- they say what
// the field is rather than what the setter's argument was called.
//
// The member at +0xD4 is where the merge actually adds knowledge. setSpawnData
// modelled it as `Rva0076F980Mid`, twelve opaque bytes with a copy constructor;
// both resets modelled the same twelve bytes as three pointers -- begin, end,
// capacity -- with a clear() that calls erase over the range. It is a vector,
// and the "opaque copyable thing" was its copy constructor seen from outside.
//
// The class name Rva0076F980Mid has to stay even so, because it is inside a
// ledger row's own mangled name:
//   ?setSpawnData@SpawnBehaviorModuleData@@QAEXABVRva0076F980Mid@@IIIEEE@Z
// Respelling the class would rename that row out of existence. So the placeholder
// name keeps the three real fields, which is the most this file can do without
// touching the ledger.
//
// (The class itself is not one of the phantom ModuleData names: three of its
// methods are byte-matched at real addresses and it carries the class name in
// three pinned mangled symbols, so the grouping rests on those rather than on a
// shared nested-struct name.)

void *bfmeMakeBNG(void *one, void *two);

// Twelve bytes: a begin/end/capacity vector, under TWO placeholder names that are
// both load-bearing and cannot be collapsed into one.
//
//   ?erase@SpawnBehaviorModuleDataMemberA@@QAEXPAI0@Z is the callee the two
//   resets reach through clear(), so that name has to own erase.
//   ?setSpawnData@SpawnBehaviorModuleData@@QAEXABVRva0076F980Mid@@IIIEEE@Z is a
//   LEDGER ROW NAME, so the member's type has to be spelled Rva0076F980Mid.
//
// Deriving the second from the first gives each name the member it owns while
// keeping one class and one twelve-byte layout. It is the same shape as the
// ??0BehaviorModule / ??1Module split in ToppleUpdateConstructors.cpp: two real
// symbols spelled on two class names, reconciled by putting them on two levels
// rather than by choosing between them.
class SpawnBehaviorModuleDataMemberA
{
public:
	void erase(unsigned int *first, unsigned int *last);
	void clear(void)
	{
		erase(m_begin, m_end);
	}

	unsigned int *m_begin;
	unsigned int *m_end;
	unsigned int *m_capacity;
};

class Rva0076F980Mid : public SpawnBehaviorModuleDataMemberA
{
public:
	Rva0076F980Mid(const Rva0076F980Mid &other);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnBehavior.h
class SpawnBehaviorModuleData
{
public:
	void setSpawnData(
		const Rva0076F980Mid &names,
		unsigned int spawnNumber,
		unsigned int startNumber,
		unsigned int replaceDelay,
		unsigned char oneShot,
		unsigned char reclaimOrphans,
		unsigned char requireSpawner);
	void resetSpawnData(void);
	void resetSpawnDataFull(void);

private:
	unsigned char m_beforeFlag[0xa8];
	unsigned char m_flagA8;					// +0xA8
	unsigned char m_padA9[0xb];
	void *m_madeBNG;					// +0xB4
	unsigned char m_beforeSpawnData[0x0c];
	unsigned int m_spawnNumberData;				// +0xC4
	unsigned int m_spawnStartNumberData;			// +0xC8
	unsigned int m_spawnReplaceDelayData;			// +0xCC
	unsigned char m_isOneShotData;				// +0xD0
	unsigned char m_canReclaimOrphans;			// +0xD1
	unsigned char m_alignment[2];
	Rva0076F980Mid m_spawnTemplateNameData;			// +0xD4
	unsigned char m_beforeSpawnedRequireSpawner[8];
	unsigned char m_spawnedRequireSpawner;			// +0xE8
};

// ?setSpawnData@SpawnBehaviorModuleData@@QAEXABVRva0076F980Mid@@IIIEEE@Z
void SpawnBehaviorModuleData::setSpawnData(
	const Rva0076F980Mid &names,
	unsigned int spawnNumber,
	unsigned int startNumber,
	unsigned int replaceDelay,
	unsigned char oneShot,
	unsigned char reclaimOrphans,
	unsigned char requireSpawner)
{
	m_spawnTemplateNameData.Rva0076F980Mid::Rva0076F980Mid(names);
	m_spawnNumberData = spawnNumber;
	m_spawnStartNumberData = startNumber;
	m_spawnReplaceDelayData = replaceDelay;
	m_isOneShotData = oneShot;
	m_canReclaimOrphans = reclaimOrphans;
	m_spawnedRequireSpawner = requireSpawner;
}

// ?resetSpawnData@SpawnBehaviorModuleData@@QAEXXZ
void SpawnBehaviorModuleData::resetSpawnData(void)
{
	m_spawnTemplateNameData.clear();
	m_spawnNumberData = 0;
	m_spawnStartNumberData = 0;
	m_spawnReplaceDelayData = 0;
	m_isOneShotData = 0;
	m_canReclaimOrphans = 0;
	m_spawnedRequireSpawner = 0;
}

// ?resetSpawnDataFull@SpawnBehaviorModuleData@@QAEXXZ
// resetSpawnData plus the flag at +0xA8 and the pointer at +0xB4. The zero is
// held in a local and reused, which is what retail's single xor produces.
void SpawnBehaviorModuleData::resetSpawnDataFull(void)
{
	unsigned int z = 0;
	m_flagA8 = (unsigned char)z;
	m_madeBNG = bfmeMakeBNG((void *)z, (void *)z);
	m_spawnTemplateNameData.clear();
	m_spawnNumberData = z;
	m_spawnStartNumberData = z;
	m_spawnReplaceDelayData = z;
	m_isOneShotData = (unsigned char)z;
	m_canReclaimOrphans = (unsigned char)z;
	m_spawnedRequireSpawner = (unsigned char)z;
}
