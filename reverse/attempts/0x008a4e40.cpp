// ?aptRound@@YAPAVAptValue@@PAXH@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: float toNumber(); };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
extern const float BfmeZeroRange;
extern const float g_bfmeK1253;
AptValue* __cdecl Rva008B6D70MakeValue(int value);
AptValue* aptRound(void* self, int argc)
{
	if (argc <= 0)
		return g_bfmeFallbackDB;
	float d = g_bfmeArr1233[g_bfmeCount1233 - 1]->toNumber();
	if (d > BfmeZeroRange)
		return Rva008B6D70MakeValue((int)(d + g_bfmeK1253));
	return Rva008B6D70MakeValue((int)(d - g_bfmeK1253));
}
