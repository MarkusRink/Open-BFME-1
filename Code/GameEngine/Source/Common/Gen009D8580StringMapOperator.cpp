// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1

#include <hash_map>
#include <string>
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct BfmeStringNode
{
	BfmeStringNode *next;
	_STL::string key;
	int value;
};

typedef _STL::pair<const _STL::string, int> BfmeStringPair;

struct BfmeCharRange
{
	const char *begin;
	const char *end;
};

class Gen009D7B80
{
public:
	__declspec(noinline) BfmeStringNode *find(const _STL::string *key) const;
	BfmeStringPair *bfmeInsert(const BfmeStringPair *value);
	int &operator[](const _STL::string &key);
	__forceinline int &insertDefault(const BfmeStringPair &pair)
	{
		return bfmeInsert(&pair)->second;
	}

private:
	unsigned int m_pad;
	BfmeStringNode **m_begin;
	BfmeStringNode **m_end;
	BfmeStringNode **m_capacity;
	unsigned int m_count;
};

int &Gen009D7B80::operator[](const _STL::string &key)
{
	BfmeStringNode *node = find(&key);
	return node == 0 ? insertDefault(BfmeStringPair(key, 0)) : node->value;
}
