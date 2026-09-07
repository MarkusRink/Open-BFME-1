// ?allEntriesMatch@Rva00892FD0Owner@@QAE_NHH@Z
// partial score=0.85 date=2026-09-06
struct Rva00892FD0Entry { int m_0; int m_key; };
struct Rva00892FD0Owner {
	int m_count;
	int m_4;
	Rva00892FD0Entry* m_entries;
	bool allEntriesMatch(int a, int b);
};
bool Rva00892FD0Owner::allEntriesMatch(int a, int b)
{
	int n = m_count;
	for (int i = 0; i < n; ++i) {
		if (m_entries[i].m_key != a && m_entries[i].m_key != b)
			return false;
	}
	return true;
}
