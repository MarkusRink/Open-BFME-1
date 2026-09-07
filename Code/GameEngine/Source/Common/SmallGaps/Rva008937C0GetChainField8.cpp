// ?rva008937C0GetChainField8@@YAHPAX@Z
// Address-derived: second half of the merged 62-byte window (real boundary
// 0x008937C0 size 0x1E). Look up p via the already-named dump 0x008930C0,
// then walk obj->m_50->m_c->m_8, returning 0 if obj is null.
extern void d_008930c0();

int rva008937C0GetChainField8(void* p)
{
	typedef void* (__cdecl* Fn)(void*);
	void* obj = ((Fn)d_008930c0)(p);
	if (obj)
	{
		void* c = *(void**)((char*)obj + 0x50);
		void* d = *(void**)((char*)c + 0xc);
		return *(int*)((char*)d + 8);
	}
	return 0;
}
