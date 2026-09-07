// ?rva0087DE10ParseBoolGate@@YAXPAVINI@@PAXPAURva0087DE10Info@@@Z
// partial score=0.8 date=2026-09-06
// ?rva0087DE10ParseBoolGate@@YGXPAXPAX0@Z
// Address-derived: only call the already-named INI::parseBool if at least one
// 13-byte stride remains between info->m_2c and info->m_30, parsing from
// info->m_30-4.
class INI;

class INI
{
public:
	static void parseBool(INI* ini, void* instance, void* store, const void* userData);
};

struct Rva0087DE10Info
{
	unsigned char m_pad[0x2c];
	int m_2c;
	int m_30;
};

void rva0087DE10ParseBoolGate(INI* a, void* b, Rva0087DE10Info* info)
{
	int count = (info->m_30 - info->m_2c) / 36;
	if (count != 0)
		INI::parseBool(a, b, (void*)(info->m_30 - 4), 0);
}
