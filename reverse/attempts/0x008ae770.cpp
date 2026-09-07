// ?aptCallWithBias@@YAPAVAptValue@@PAXH@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: int toInteger(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
struct Rva008AE770Stack { void invoke(void* self, int zero, void* self2, AptValue* target, int biased, AptValue* extra); };
extern Rva008AE770Stack Rva008AE770TheStack;
AptValue* aptCallWithBias(void* self, int argc)
{
	AptValue* first = g_bfmeArr1233[g_bfmeCount1233 - 2];
	AptValue* second = g_bfmeArr1233[g_bfmeCount1233 - 1];
	AptValue* third = argc >= 3 ? g_bfmeArr1233[g_bfmeCount1233 - 3] : 0;
	Rva008AE770TheStack.invoke(self, 0, self, second, first->toInteger() + 0x4000, third);
	return g_bfmeFallbackDB;
}
