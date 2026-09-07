// ?applyUpgradeIfAllowed@Rva00256240Inner@@QAEXH@Z
// partial score=0.9 date=2026-09-06
class Object;
class GameLogic { public: Object* bfmeFind1011(int id); };
extern GameLogic* TheBfmeGameLogic;
struct Rva00256240Upgrade;
struct Rva00256240Center { Rva00256240Upgrade* findUpgrade(void* name); };
extern Rva00256240Center* Rva00256240TheUpgradeCenter;
struct Rva00256240Def { char m_pad[0x8]; char m_gate[0x2c]; char m_upgradeName[1]; bool allows(void* ctx, int arg); };
struct Rva00256240Ctx { char m_pad[0x78]; int m_objectId; };
class Object { public: bool canApply(Rva00256240Upgrade* u); void apply(Rva00256240Upgrade* u); };
struct Rva00256240Inner { void applyUpgradeIfAllowed(int arg); };
struct Rva00256240Outer { Rva00256240Def* m_def; Rva00256240Ctx* m_ctx; int m_8; Rva00256240Inner m_inner; };
void Rva00256240Inner::applyUpgradeIfAllowed(int arg)
{
	Rva00256240Outer* outer = (Rva00256240Outer*)((char*)this - 0xc);
	if (((Rva00256240Def*)outer->m_def->m_gate)->allows(outer->m_ctx, arg)) {
		Object* obj = TheBfmeGameLogic->bfmeFind1011(outer->m_ctx->m_objectId);
		if (obj) {
			Rva00256240Upgrade* u = Rva00256240TheUpgradeCenter->findUpgrade(outer->m_def->m_upgradeName);
			if (u && obj->canApply(u))
				obj->apply(u);
		}
	}
}
