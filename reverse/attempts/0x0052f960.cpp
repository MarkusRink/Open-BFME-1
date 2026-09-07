// ??$__unguarded_partition@PAUS4SortElem12@@U1@US4Cmp00531FA0@@@_STL@@YAPAUS4SortElem12@@PAU1@0U1@US4Cmp00531FA0@@Z
// partial score=0.98 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc

// Open-BFME5: _STL::__unguarded_partition<S4SortElem12 *, S4SortElem12,
// S4Cmp00531FA0>, retail 0x0052F960, 365 bytes.  The neighboring
// __linear_insert and __partial_sort bodies identify the twelve-byte record
// and its pointer, descending-key, case-insensitive-name comparator.

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);

extern const char g_bfmeEmptyAscii[];

template <class T>
class StringBase
{
private:
	struct Header
	{
		int m_bfmeRefCount;
		unsigned short m_bfmeLength;
		unsigned short m_bfmeCapacity;
		T m_bfmeData[1];
	};

	Header *m_bfmeData;

public:
	int compareNoCase(const StringBase<T> &other) const
	{
		const int otherLength = other.m_bfmeData
			? other.m_bfmeData->m_bfmeLength : 0;
		const char *otherText = other.m_bfmeData
			? (const char *)&other.m_bfmeData->m_bfmeData[0]
			: g_bfmeEmptyAscii;
		const int thisLength = m_bfmeData
			? m_bfmeData->m_bfmeLength : 0;
		const char *thisText = m_bfmeData
			? (const char *)&m_bfmeData->m_bfmeData[0]
			: g_bfmeEmptyAscii;
		const int length = thisLength < otherLength
			? thisLength : otherLength;
		int result = _memicmp(thisText, otherText, length);
		if (result == 0)
			result = thisLength - otherLength;
		return result;
	}
};

struct S4Named0052E880
{
	int m_bfmeUnused;
	StringBase<char> m_bfmeName;
};

struct S4SortElem12
{
	S4Named0052E880 *m_bfmeObj;
	int m_bfmeKey;
	int m_bfmeThird;
};

struct S4Cmp00531FA0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		if (left.m_bfmeKey == right.m_bfmeKey)
		{
			if (left.m_bfmeObj != 0)
			{
				if (right.m_bfmeObj == 0)
					goto retFalse;
				return left.m_bfmeObj->m_bfmeName.compareNoCase(
					right.m_bfmeObj->m_bfmeName) < 0;
			}
			if (right.m_bfmeObj == 0)
			{
retFalse:
				return false;
			}
			return true;
		}
		return left.m_bfmeKey > right.m_bfmeKey;
	}
};

namespace _STL
{

template <class ForwardIter1, class ForwardIter2>
inline void iter_swap(ForwardIter1 left, ForwardIter2 right)
{
	S4SortElem12 temporary = *left;
	*left = *right;
	*right = temporary;
}

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true)
	{
		while (comp(*first, pivot))
			++first;
		--last;
		while (comp(pivot, *last))
			--last;
		if (!(first < last))
			return first;
		iter_swap(first, last);
		++first;
	}
}

template S4SortElem12 *__unguarded_partition<S4SortElem12 *, S4SortElem12,
	S4Cmp00531FA0>(S4SortElem12 *, S4SortElem12 *, S4SortElem12,
	S4Cmp00531FA0);

}
