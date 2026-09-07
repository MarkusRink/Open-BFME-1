// ?rva00197430PairLess@@YA_NPBURva00197430Pair@@0@Z
// partial score=0.85 date=2026-09-06
// ?rva00197430PairLess@@YA_NPBURva00197430Pair@@0@Z
// Address-derived: classic std::pair<AsciiString,AsciiString>::operator<
// shape -- compare first fields both ways, then break ties on the second
// field, all through the already-pinned AsciiString::compare thunk at
// 0x000220C5.
class AsciiString
{
public:
	int compare(const AsciiString& other) const;

private:
	void* m_data;
};

struct Rva00197430Pair
{
	AsciiString first;
	AsciiString second;
};

bool rva00197430PairLess(const Rva00197430Pair* a, const Rva00197430Pair* b)
{
	if (a->first.compare(b->first) < 0)
		goto isLess;
	if (b->first.compare(a->first) < 0)
		goto notLess;
	if (a->second.compare(b->second) < 0)
		goto isLess;
	goto notLess;
isLess:
	return true;
notLess:
	return false;
}
