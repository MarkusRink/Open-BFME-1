// ?clearChainAndStats@Rva000CE400Owner@@QAEXXZ
// partial score=0.8 date=2026-09-06
struct Rva000CE400Node { virtual ~Rva000CE400Node(); int m_4; int m_8; Rva000CE400Node* m_next; };
struct Rva000CE400Stats { int m_0; int m_4; int m_8; int m_c; int m_10; int m_14; };
struct Rva000CE400Owner {
	char m_pad[0x54];
	Rva000CE400Node* m_head;
	char m_pad2[0x74 - 0x58];
	Rva000CE400Stats m_statsA;
	Rva000CE400Stats m_statsB;
	void clearChainAndStats();
};
void Rva000CE400Owner::clearChainAndStats()
{
	while (m_head) {
		Rva000CE400Node* next = m_head->m_next;
		delete m_head;
		m_head = next;
	}
	m_statsA.m_0 = 0; m_statsA.m_4 = 0; m_statsA.m_8 = 0; m_statsA.m_c = 0; m_statsA.m_10 = 0; m_statsA.m_14 = 0;
	m_statsB.m_0 = 0; m_statsB.m_4 = 0; m_statsB.m_8 = 0; m_statsB.m_c = 0; m_statsB.m_10 = 0; m_statsB.m_14 = 0;
}
