// ?scriptPlayers002EF110AllOrMask@@YGXH@Z
// partial score=0.9 date=2026-09-06
class ScriptEngine { public: int resolvePlayerMask(int param, int flag); };
extern ScriptEngine* TheScriptEngine;
struct Rva002EE330Player { char m_pad[0x24]; int m_index; char m_pad2[0x2c - 0x28]; int m_isLocalOnly; void onScript002EF110(int flag); };
struct Rva002EE330PlayerList { char m_pad[0x10]; int m_count; Rva002EE330Player* nextFromMask(unsigned short* mask); };
extern Rva002EE330PlayerList* Rva002EE330ThePlayers;
Rva002EE330Player* __stdcall Rva002EF110GetPlayer(int index);

void __stdcall scriptPlayers002EF110AllOrMask(int param)
{
	param = TheScriptEngine->resolvePlayerMask(param, 0);
	if (!(unsigned short)param) {
		for (int i = 0; i < Rva002EE330ThePlayers->m_count; ++i) {
			Rva002EE330Player* player = Rva002EF110GetPlayer(i);
			if (!player->m_isLocalOnly)
				player->onScript002EF110(1);
		}
		return;
	}
	while ((unsigned short)param) {
		Rva002EE330Player* player = Rva002EE330ThePlayers->nextFromMask((unsigned short*)&param);
		if (player)
			player->onScript002EF110(1);
	}
}
