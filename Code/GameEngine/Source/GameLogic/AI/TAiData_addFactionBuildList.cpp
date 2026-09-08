// cl: /DNDEBUG /MD /EHsc
// Open-BFME: TAiData::addFactionBuildList at retail 0x0014BE10.
// AI::newOverride and Rva0014C090::parseDefinition call its retail ILT.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

extern const char Rva006A16B0Empty[];

struct BfmeAsciiStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class BfmeRetailAsciiString
{
public:
	int compare(const BfmeRetailAsciiString &other) const
	{
		int rightLength = other.m_data ? other.m_data->m_length : 0;
		const char *right = other.m_data ? other.m_data->m_text : Rva006A16B0Empty;
		int leftLength = m_data ? m_data->m_length : 0;
		const char *left = m_data ? m_data->m_text : Rva006A16B0Empty;
		int length = leftLength < rightLength ? leftLength : rightLength;
		int result = memcmp(left, right, length);
		if (result != 0)
			return result;
		return leftLength - rightLength;
	}

	bool operator==(const BfmeRetailAsciiString &other) const
	{
		return compare(other) == 0;
	}

private:
	BfmeAsciiStringData *m_data;
};

class BuildListInfo
{
public:
	virtual ~BuildListInfo();

	void deleteInstance()
	{
		delete this;
	}
};

class AISideBuildList
{
public:
	virtual ~AISideBuildList();

	void deleteInstance()
	{
		delete this;
	}

	BfmeRetailAsciiString m_side;
	BuildListInfo *m_buildList;
	AISideBuildList *m_next;
};

class TAiData
{
public:
	void addFactionBuildList(AISideBuildList *buildList);

private:
	unsigned char m_padding[0xf0];
	AISideBuildList *m_sideBuildLists;
};

void TAiData::addFactionBuildList(AISideBuildList *buildList)
{
	AISideBuildList *info = m_sideBuildLists;
	while (info)
	{
		if (buildList->m_side == info->m_side)
		{
			if (info->m_buildList)
				info->m_buildList->deleteInstance();
			info->m_buildList = buildList->m_buildList;
			buildList->m_buildList = 0;
			buildList->m_next = 0;
			buildList->deleteInstance();
			return;
		}
		info = info->m_next;
	}
	buildList->m_next = m_sideBuildLists;
	m_sideBuildLists = buildList;
}
