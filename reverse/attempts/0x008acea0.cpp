// ?aptForwardTyped008ACEA0@@YAPAVAptValue@@PAXH@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class Rva8CCCE0Value;
extern AptValue* g_bfmeFallbackDB;
void rva8CCCE0ResolveValue(void* a, void* b, Rva8CCCE0Value* c, Rva8CCCE0Value** out);
struct Rva008ACEA0Sink { void accept(Rva8CCCE0Value* value); };
struct Rva008ACEA0Holder { char m_pad[0x50]; char m_sinkBody[0x24]; Rva008ACEA0Sink m_sink; };
struct Rva008ACEA0Link { char m_pad[0x4c]; Rva008ACEA0Holder* m_holder; };
class Rva8CCCE0Value { public: int m_0; unsigned int m_type : 6; unsigned int m_mid : 9; unsigned int m_owned : 1; unsigned int m_rest : 16; char m_pad[0x4c - 8]; Rva008ACEA0Link* m_link; };
AptValue* aptForwardTyped008ACEA0(void* self, int argc)
{
	Rva8CCCE0Value* value = 0;
	rva8CCCE0ResolveValue(self, 0, (Rva8CCCE0Value*)self, &value);
	if (value) {
		int type = value->m_type;
		if (type >= 0xc && type <= 0x13 && value->m_owned)
			value->m_link->m_holder->m_sink.accept(value);
	}
	return g_bfmeFallbackDB;
}
