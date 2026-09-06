// ?clear@Rva001DDD60List@@QAEXXZ
struct Rva001DDD60Node { virtual ~Rva001DDD60Node(); Rva001DDD60Node* m_next; };
struct Rva001DDD60List { int m_0; Rva001DDD60Node* m_head; Rva001DDD60Node* m_tail; int m_count; void clear(); };
void Rva001DDD60List::clear()
{
	while (m_head) {
		Rva001DDD60Node* next = m_head->m_next;
		delete m_head;
		m_head = next;
		--m_count;
	}
	m_head = 0;
	m_tail = 0;
	m_count = 0;
}
