// ?rva00891E00ReleaseChain@@YAXXZ
// partial score=0.9 date=2026-09-06
// ?rva00891E00ReleaseChain@@YAXXZ
// Straight-line teardown sequence: twelve unconditional calls to already-named
// (or already-dumped) release/globals-teardown routines, no branching, no args.
extern void rva008B8B80ReleaseAll();
extern void d_008b61d0();
extern void rva008A4630ReleaseGlobals();
extern void rva008A47B0ReleaseGlobals();
extern void bfmeGo1062B();
extern void rva008A48D0ReleaseGlobals();
extern void bfmeGo1083A();
extern void bfmeGo1082C();
extern void bfmeGo1082B();
extern void rva008B2BD0ReleaseGlobals();
extern void d_008acac0();
extern void rva008A98B0ReleaseAll();
extern void Rva008A4AA0Invoke();

void rva00891E00ReleaseChain()
{
	rva008B8B80ReleaseAll();
	d_008b61d0();
	rva008A4630ReleaseGlobals();
	rva008A47B0ReleaseGlobals();
	bfmeGo1062B();
	rva008A48D0ReleaseGlobals();
	bfmeGo1083A();
	bfmeGo1082C();
	bfmeGo1082B();
	rva008B2BD0ReleaseGlobals();
	d_008acac0();
	rva008A98B0ReleaseAll();
	Rva008A4AA0Invoke();
}
