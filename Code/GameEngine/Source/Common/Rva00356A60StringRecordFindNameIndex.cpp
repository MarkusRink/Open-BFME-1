// The second BFME string-record table has the same 20-byte record and
// eight-byte AsciiString layout as the first table.  Retail 0x00356A60 is
// its matching sorted name-index search; this TU keeps the recovered owner
// identity separate while preserving the proven inline comparison shape.

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct Rva00356A60AsciiStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	const char *str() const
	{
		return m_data ? &m_data->m_text[0] : g_bfmeEmptyAscii;
	}

	int compare(const AsciiString &other) const
	{
		int thatLength = other.getLength();
		const char *thatText = other.str();
		int selfLength = getLength();
		const char *selfText = str();
		int result = memcmp(selfText, thatText,
			(unsigned int)(selfLength < thatLength ? selfLength : thatLength));
		if (result != 0)
			return result;
		return selfLength - thatLength;
	}

	Rva00356A60AsciiStringData *m_data;
};

struct Rva00356A60Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359530StringRecordTable
{
private:
	int findNameIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00356A60Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

int Rva00359530StringRecordTable::findNameIndex(AsciiString *name)
{
	int low = 0;
	int *begin = m_nameIndexesBegin;
	int high = m_nameIndexesEnd - begin;
	if (high > 0)
	{
		Rva00356A60Record *records = m_records;
		while (high > low)
		{
			int middle = (low + high) >> 1;
			Rva00356A60Record *record = &records[begin[middle]];
			AsciiString *recordName =
				(AsciiString *)((char *)record + 8);
			int comparison = name->compare(*recordName);
			if (comparison == 0)
				return middle;
			if (comparison < 0)
				high = middle;
			else
				low = middle + 1;
		}
	}

	return low;
}
