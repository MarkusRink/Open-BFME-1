// ?parseLastEntryReal@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-09-06
class INI {
public:
	const char* getNextToken(const char* seps);
	static float scanReal(const char* token);
};
struct Rva0087F1D0Entry { int m_0; int m_4; float m_value; char m_rest[36 - 12]; };
struct Rva0087F1D0Owner {
	char m_pad[0x2c];
	Rva0087F1D0Entry* m_begin;
	Rva0087F1D0Entry* m_end;
	int size() const { return m_end - m_begin; }
	void finish();
};
void parseLastEntryReal(INI* ini, void* instance, void* store, const void* userData)
{
	Rva0087F1D0Owner* owner = (Rva0087F1D0Owner*)store;
	if (owner->size() != 0) {
		Rva0087F1D0Entry* last = owner->m_end - 1;
		last->m_value = INI::scanReal(ini->getNextToken(0));
	}
	owner->finish();
}
