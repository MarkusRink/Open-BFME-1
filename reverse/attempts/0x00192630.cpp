// ?d_00192630@@YAXXZ
// partial score=0.9 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc-
// BFME writes the nested LibraryMapLists and LibraryMaps chunks from this record array.

class AsciiString
{
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void closeDataChunk();
	void writeInt(int value);
	void writeAsciiString(const AsciiString &value);
};

struct LibraryMaps
{
	char unused[0xc];
	AsciiString *first;
	AsciiString *last;
	AsciiString *capacity;
};

class LibraryMapLists
{
private:
	char unused[0x28];
	int count;
	LibraryMaps lists[1];

public:
	void writeDataChunk(DataChunkOutput &output);
};

void LibraryMapLists::writeDataChunk(DataChunkOutput &output)
{
	int index;
	LibraryMaps *cursor;
	LibraryMaps *list;
	AsciiString *value;
	output.openDataChunk("LibraryMapLists", 1);
	int listCount = count;
	index = 0;
	if (listCount > 0)
	{
		cursor = lists;
		do
		{
			output.openDataChunk("LibraryMaps", 1);
			if (index < 0 || index >= count)
				list = 0;
			else
				list = cursor;
			output.writeInt(list->last - list->first);
			for (value = list->first; value != list->last; ++value)
				output.writeAsciiString(*value);
			output.closeDataChunk();
			++cursor;
			++index;
		} while (index < listCount);
	}
	output.closeDataChunk();
}
