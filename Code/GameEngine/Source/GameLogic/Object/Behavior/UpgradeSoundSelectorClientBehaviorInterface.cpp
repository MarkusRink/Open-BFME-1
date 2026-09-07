// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeSoundSelectorClientBehavior's mapped-sound query.
// The secondary SoundSelectorInterface walks 0x210-byte upgrade records, tests
// the attached object against each record, and returns the mapped sound value.

typedef bool Bool;

class ModuleData
{
public:
	virtual void anchor();

	unsigned int m_tag;
};

class ClientUpdateModule
{
public:
	virtual void anchor();

	ModuleData *m_moduleData;
	void *m_drawable;
};

struct BfmeSlotSD;
struct BfmeKeySD;

class SoundSelectorInterface
{
public:
	virtual BfmeSlotSD *findMappedSound(BfmeKeySD *key) = 0;
};

class BfmeMapSD
{
public:
	BfmeSlotSD *bfmeFindSD(BfmeKeySD *key);

	BfmeSlotSD *m_header;
	char m_pad[8];
};

struct SoundUpgradeRecord
{
	char m_body[0x1fc];
	BfmeMapSD m_map;
};

class UpgradeSoundSelectorClientBehaviorModuleData : public ModuleData
{
public:
	SoundUpgradeRecord *m_start;
	SoundUpgradeRecord *m_finish;
	SoundUpgradeRecord *m_end;
};

class UpgradeSoundSelectorClientBehavior : public ClientUpdateModule,
	public SoundSelectorInterface
{
public:
	virtual BfmeSlotSD *findMappedSound(BfmeKeySD *key);
};

class Rva006083A0SoundUpgrade
{
public:
	Bool matchesObject(void *object);
};

// 0x006083A0 tests the record's upgrade mask against the attached object.
#pragma comment(linker, "/alternatename:?matchesObject@Rva006083A0SoundUpgrade@@QAE_NPAX@Z=?j_000420b9@@YAXXZ")

// The existing BfmeMapSD implementation is reached through this ILT.
#pragma comment(linker, "/alternatename:?bfmeFindSD@BfmeMapSD@@QAEPAUBfmeSlotSD@@PAUBfmeKeySD@@@Z=?j_00020e7d@@YAXXZ")

// ?findMappedSound@UpgradeSoundSelectorClientBehavior@@UAEPAUBfmeSlotSD@@PAUBfmeKeySD@@@Z
BfmeSlotSD *UpgradeSoundSelectorClientBehavior::findMappedSound(BfmeKeySD *key)
{
	UpgradeSoundSelectorClientBehaviorModuleData *data =
		(UpgradeSoundSelectorClientBehaviorModuleData *)m_moduleData;
	void *drawable = m_drawable;
	void *upgrade = *(void **)((char *)drawable + 0xfc);
	if (upgrade == 0)
		return 0;

	SoundUpgradeRecord *finish = data->m_finish;
	for (SoundUpgradeRecord *record = data->m_start; record != finish;
		record = (SoundUpgradeRecord *)((char *)record + 0x210))
	{
		if (((Rva006083A0SoundUpgrade *)record)->matchesObject(upgrade))
		{
			BfmeMapSD *map = &record->m_map;
			BfmeSlotSD *node = map->bfmeFindSD(key);
			if (node == map->m_header)
				continue;
			void *sound = (void *)((char *)node + 0x14);
			if (sound != 0)
				return (BfmeSlotSD *)sound;
		}
	}
	return 0;
}
