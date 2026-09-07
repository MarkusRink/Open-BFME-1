// ?bfmeSpawnCW@BfmeHostCW@@QAEXPBD@Z (identity unknown)
// partial score=0.94 date=2026-09-07
// 93/97. The temporary form below gives retail's SEH prologue exactly and the
// temporary lands in the dead parameter home slot as retail has it. The 4-byte
// gap is the argument: retail recomputes the address
//   lea ecx,[esp+0x10] / push ecx
// where MSVC reuses the constructor's return value (`push eax`), since the
// ctor hands back `this` in eax.
// The fork, and both halves are individually reachable but not together:
//   * a TEMPORARY gives retail's prologue but the eax reuse -> 93
//   * a NAMED local, or a lifetime-extended `const T &`, gives the other SEH
//     prologue form ([[seh-prologue-has-two-forms]]) and a real local slot ->
//     97 bytes but a dozen diffs
// Also tried: declaring the callee to take a POINTER and passing
// `&BFMERetailAsciiString(name)` (MSVC allows it) -- still 93, same reuse.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufCW;

private:
	void releaseBuffer();
};

class ParticleSystemManager
{
public:
	void bfmeStopCW(const BFMERetailAsciiString &name);
};

extern ParticleSystemManager *TheParticleSystemManager;

class BfmeHostCW
{
public:
	void bfmeSpawnCW(const char *name);
	void bfmeStartCW();
};

void BfmeHostCW::bfmeSpawnCW(const char *name)
{
	bfmeStartCW();

	TheParticleSystemManager->bfmeStopCW(BFMERetailAsciiString(name));
}
