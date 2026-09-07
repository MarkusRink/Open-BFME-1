// ?dispatchByKind@@YG_NPAURva00346300Item@@@Z
// partial score=0.85 date=2026-09-06
struct Rva00346300Item { int m_0; unsigned int m_kind; };
struct Rva00346300Handler {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual void s6(); virtual void s7(); virtual void s8();
	virtual bool handle(Rva00346300Item* item);
};
extern Rva00346300Handler* Rva00346300TheHandler;
bool __stdcall Rva00346300Kind1(Rva00346300Item* item);
bool __stdcall Rva00346300Kind2(Rva00346300Item* item);
bool __stdcall Rva00346300Kind4(Rva00346300Item* item);
bool __stdcall dispatchByKind(Rva00346300Item* item)
{
	switch (item->m_kind) {
	case 0:
		return false;
	case 1:
		return Rva00346300Kind1(item);
	case 2:
		return Rva00346300Kind2(item);
	case 3:
		return true;
	case 4:
		return Rva00346300Kind4(item);
	default:
		return Rva00346300TheHandler->handle(item);
	}
}
