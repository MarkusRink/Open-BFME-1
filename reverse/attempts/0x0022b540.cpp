// ?clearList@Rva0022B540Owner@@QAEXXZ
// partial score=0.35 date=2026-09-06
// ?clearList@Rva0022B540Owner@@QAEXXZ

namespace _STL {

template<int a, int b> class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};

}

struct Rva0022B540Node { Rva0022B540Node* m_next; Rva0022B540Node* m_prev; void* m_data; };
struct Rva0022B540Obj { unsigned char m_pad[0x214]; int m_flag214; };
struct Rva0022B540Logic { void deregister(void* obj); };

extern "C" void j_0002a05e();
extern Rva0022B540Logic* TheBfmeGameLogic0022B540;

struct Rva0022B540Owner
{
	unsigned char m_pad0[0xe4];
	Rva0022B540Node* m_list;

	void clearList();
};

void Rva0022B540Owner::clearList()
{
	typedef void (Rva0022B540Owner::*Fn)();
	union { void (*raw)(); Fn member; } fn;
	fn.raw = j_0002a05e;
	(this->*fn.member)();

	Rva0022B540Node* node = m_list->m_next;

	while (node != m_list) {
		Rva0022B540Obj* obj = (Rva0022B540Obj*)node->m_data;
		Rva0022B540Node* next = node->m_next;
		obj->m_flag214 = 0;
		TheBfmeGameLogic0022B540->deregister(obj);

		_STL::__node_alloc<1, 0>::_M_deallocate(node, 0xc);
		node = next;
	}

	m_list->m_next = m_list;
	m_list->m_prev = m_list;
}
