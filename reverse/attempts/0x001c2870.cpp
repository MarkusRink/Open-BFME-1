// ?notEquals@Rva001C2870Arr@@QBE_NPBU1@@Z
// partial score=0.85 date=2026-09-06
// ?notEquals@Rva001C2870Arr@@QBE_NPBU1@@Z
// Address-derived: compare 10 consecutive ints against another instance's 10
// ints, returning true if any differ.
struct Rva001C2870Arr
{
	int v[10];

	bool notEquals(const Rva001C2870Arr* other) const;
};

bool Rva001C2870Arr::notEquals(const Rva001C2870Arr* other) const
{
	for (unsigned i = 0; i < 10; ++i)
	{
		if (v[i] != other->v[i])
			return !!1;
	}
	return !!0;
}
