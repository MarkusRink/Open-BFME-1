// ??1Gen_00471390@@UAE@XZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Destructor paired with the credited constructor at 0x00471390.  The two
// pointer ranges own virtual objects, the single pointer owns one more object,
// and the name uses the retail AsciiString release body.

namespace _STL {

template <bool Threads, int Instance>
class __node_alloc {
  static void _M_deallocate(void *memory, unsigned int bytes);

public:
  static void deallocate(void *memory, unsigned int bytes) {
    if (bytes > 128)
      ::operator delete(memory);
    else
      _M_deallocate(memory, bytes);
  }
};

}

class BfmeOwnedWB {
public:
  virtual ~BfmeOwnedWB();
};

class BFMERetailAsciiString {
public:
  __forceinline ~BFMERetailAsciiString() { releaseBuffer(); }
  void releaseBuffer();

private:
  char *m_data;
};

class BfmeEmptyWB {
public:
  __forceinline ~BfmeEmptyWB() {}
};

struct BfmePointerVectorWB {
  BfmeOwnedWB **m_start;
  BfmeOwnedWB **m_finish;
  BfmeOwnedWB **m_capacity;
};

__forceinline void releaseBfmePointerVectorWB(BfmePointerVectorWB &vector) {
  BfmeOwnedWB **start = vector.m_start;
  if (start != 0) {
    unsigned int bytes = (unsigned int)((vector.m_capacity - start) * 4);
    _STL::__node_alloc<true, 0>::deallocate(start, bytes);
  }
}

class BfmeVectorBaseWB {
public:
  __forceinline ~BfmeVectorBaseWB() {
    releaseBfmePointerVectorWB(m_second);
    BfmePointerVectorWB *first =
        (BfmePointerVectorWB *)((char *)this - 0x0c);
    releaseBfmePointerVectorWB(*first);
  }

  BfmePointerVectorWB m_second;
};

__declspec(novtable) class BfmeGuardWB {
public:
  __forceinline virtual ~BfmeGuardWB() {}
  virtual void method1() = 0;
  virtual void method2() = 0;
  virtual void method3() = 0;
  virtual void method4() = 0;

public:
  char m_padding[0x18];
  BfmePointerVectorWB m_first;
};

class Gen_00471390 : public BfmeGuardWB {
public:
  virtual ~Gen_00471390();
private:
  BfmeVectorBaseWB m_vector;
  BfmeOwnedWB *m_owned;
  int m_unused;
  BFMERetailAsciiString m_name;
  char m_tail[0x10];
};

// ??1Gen_00471390@@UAE@XZ
Gen_00471390::~Gen_00471390() {
  BfmeOwnedWB **finish = m_vector.m_second.m_finish;
  for (BfmeOwnedWB **it = m_vector.m_second.m_start; it != finish; ++it) {
    BfmeOwnedWB *owned = *it;
    if (owned)
      delete owned;
  }

  if (m_owned)
    delete m_owned;
  m_owned = 0;
}

void bfmeInvokeGen00471390Dtor(Gen_00471390 *object) {
  object->~Gen_00471390();
}
