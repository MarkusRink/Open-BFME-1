// ?notEquals@Rva001C2920Vec3@@QBE_NPBU1@@Z
// partial score=0.85 date=2026-09-06
// ?notEquals@Rva001C2920Vec3@@QBE_NPBU1@@Z
// Address-derived: compare 3 consecutive ints against another instance's 3
// ints, returning true if any differ. Same shape family as 0x001C2870 (10
// ints) -- see that stash for the bool-normalisation tail this reconstruction
// cannot force (retail wraps each `return` in a redundant
// xor-ecx/test-al/sete-cl/mov-al,cl idiom this cl folds away for 0/1
// literals).
struct Rva001C2920Vec3
{
	int v[3];

	bool notEquals(const Rva001C2920Vec3* other) const;
};

bool Rva001C2920Vec3::notEquals(const Rva001C2920Vec3* other) const
{
	for (unsigned i = 0; i < 3; ++i)
	{
		if (v[i] != other->v[i])
			return true;
	}
	return false;
}
