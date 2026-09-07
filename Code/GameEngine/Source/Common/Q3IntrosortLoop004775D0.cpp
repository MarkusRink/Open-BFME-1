// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: the 16-byte STLport __introsort_loop called by the matched
// Rva00477960 driver.  The retail body inlines median-of-three over the first
// integer, copies the trailing GameSpyGroupRoom handle, then calls the partition,
// recursive-loop, and partial-sort thunks recorded below.

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &other);
	~GameSpyGroupRoom() {}

private:
	void *m_data;
};

struct Q3SortElem16
{
	Q3SortElem16(const Q3SortElem16 &other) : m_a(other.m_a),
		m_b(other.m_b), m_c(other.m_c), m_d(other.m_d) {}

	int m_a;
	int m_b;
	int m_c;
	GameSpyGroupRoom m_d;
};

struct Q3SortCompare
{
	void *m_state;

	__forceinline bool operator()(const Q3SortElem16 &left,
		const Q3SortElem16 &right) const
	{
		return left.m_a < right.m_a;
	}
};

Q3SortElem16 *Q3Partition004775D0(Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16, Q3SortCompare);
void Q3IntrosortLoop004775D0(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *,
	int, Q3SortCompare);
void Q3PartialSort004775D0(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *,
	int, Q3SortCompare);

#pragma comment(linker, "/alternatename:?Q3Partition004775D0@@YAPAUQ3SortElem16@@PAU1@0U1@UQ3SortCompare@@@Z=?j_00034f95@@YAXXZ")
#pragma comment(linker, "/alternatename:?Q3IntrosortLoop004775D0@@YAXPAUQ3SortElem16@@00HUQ3SortCompare@@@Z=?j_0000aebb@@YAXXZ")
#pragma comment(linker, "/alternatename:?Q3PartialSort004775D0@@YAXPAUQ3SortElem16@@00HUQ3SortCompare@@@Z=?j_00032501@@YAXXZ")

static __forceinline const Q3SortElem16 *Q3SortElem16Median(
	const Q3SortElem16 *a, const Q3SortElem16 *b,
	const Q3SortElem16 *c, const Q3SortCompare &comp)
{
	if (comp(*a, *b))
	{
		if (comp(*b, *c))
			return b;
		if (comp(*a, *c))
			return c;
		return a;
	}
	if (comp(*a, *c))
		return a;
	if (comp(*b, *c))
		return c;
	return b;
}

// ?Gen004775D0@@YAXPAUQ3SortElem16@@00HUQ3SortCompare@@@Z
void Gen004775D0(Q3SortElem16 *first, Q3SortElem16 *last,
	Q3SortElem16 *, int depthLimit, const Q3SortCompare comp)
{
	while ((last - first) > 16)
	{
		if (depthLimit == 0)
		{
			Q3PartialSort004775D0(first, last, last, 0, comp);
			return;
		}

		--depthLimit;
		Q3SortElem16 *cut = Q3Partition004775D0(first, last,
			*Q3SortElem16Median(first, first + (last - first) / 2,
				last - 1, comp), comp);
		Q3IntrosortLoop004775D0(cut, last,
			(Q3SortElem16 *)0, depthLimit, comp);
		last = cut;
	}
}
