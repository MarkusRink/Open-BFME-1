// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ
// partial score=0.9 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

struct CRITICAL_SECTION
{
	unsigned char m_data[0x1c];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class CountedAsset
{
public:
	virtual void releaseSlot(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void slot3(void);
	virtual void slot4(void);
	virtual void slot5(void);
	virtual void slot6(void);
	virtual void slot7(void);
	virtual void slot8(void);
	virtual void slot9(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual CountedAsset *slot13(void);

	void Release_Ref(void)
	{
		releaseSlot();
	}
};

class AssetReference
{
public:
	AssetReference(void) : m_object(0) {}
	AssetReference(CountedAsset *object) : m_object(object) {}

	CountedAsset *m_object;
};

class CriticalSectionLock
{
public:
	CriticalSectionLock(void) : m_lock(0)
	{
	}

	void acquire(int lock)
	{
		EnterCriticalSection((CRITICAL_SECTION *)lock);
		m_lock = lock;
	}

	~CriticalSectionLock(void)
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_lock);
	}

	int m_lock;
};

struct AssetEntry
{
	AssetEntry *m_next;
	unsigned int m_index;
	CountedAsset *m_asset;
};

struct AssetEntryList
{
	unsigned char m_unused[4];
	AssetEntry **m_begin;
	AssetEntry **m_end;
};

class AssetRegistry
{
public:
	AssetReference Get_Current_Asset(void);
	CountedAsset *required(void)
	{
		return *(CountedAsset **)((char *)this + 0x1e8);
	}

private:
	unsigned char m_padding_00[0x2c];
	CRITICAL_SECTION m_lock;
	unsigned char m_padding_48[0x10];
	AssetEntry *m_current;
	AssetEntryList *m_entries;
	unsigned char m_padding_60[0x188];
	CountedAsset *m_required;
};

// ?Get_Current_Asset@AssetRegistry@@QAE?AVAssetReference@@XZ
AssetReference AssetRegistry::Get_Current_Asset(void)
{
	CriticalSectionLock lock;
	lock.acquire((int)&m_lock);

	while (m_current)
	{
		AssetEntry *entry = m_current;
		CountedAsset *asset = entry->m_asset;
		if (m_current->m_next)
		{
			m_current = m_current->m_next;
		}
		else
		{
			AssetEntry **begin = m_entries->m_begin;
			AssetEntry **end = m_entries->m_end;
			unsigned int count = (unsigned int)(end - begin);
			unsigned int index = m_current->m_index % count;
			++index;
			while (index < count && begin[index] == 0)
				++index;
			m_current = index < count ? begin[index] : 0;
		}

		if (required() == 0 || asset->slot13() == required())
		{
			return AssetReference(asset);
		}

	}

	return AssetReference();
}
