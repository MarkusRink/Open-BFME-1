// ?notEquals@Rva002DB3F0Vec6@@QBE_NPBU1@@Z
// partial score=0.85 date=2026-09-06
// ?notEquals@Rva002DB3F0Vec6@@QBE_NPBU1@@Z
// Address-derived: compare 6 consecutive ints against another instance's 6
// ints, returning true if any differ. Same shape family as 0x001C2870 (10
// ints) / 0x001C2920 (3 ints) -- retail wraps each return in a redundant
// xor-ecx/test-al/sete-cl/mov-al,cl bool-normalisation idiom this cl folds
// away for 0/1 literals.
struct Rva002DB3F0Vec6
{
	int v[6];

	bool notEquals(const Rva002DB3F0Vec6* other) const;
};

bool Rva002DB3F0Vec6::notEquals(const Rva002DB3F0Vec6* other) const
{
	for (unsigned i = 0; i < 6; ++i)
	{
		if (v[i] != other->v[i])
			return true;
	}
	return false;
}
