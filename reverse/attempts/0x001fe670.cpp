// ?bfmeCheckVE@BfmeOwnerVE@@QAEDPAVBfmeItemVE@@@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 70/71 bytes. Two findings that took the body from 59 to 70:
//   * the file needs `// cl: /QIfist` -- retail converts the float with a bare
//     `fistp`, which a plain `(int)` cast otherwise routes through __ftol2;
//   * the final test is UNSIGNED (`sbb`/`inc`, not `setge`), so write
//     `(unsigned int)limit >= (unsigned int)rounded`.
// Also settled: the math routine is a DLL import called through `ff 15`, so it
// needs `extern "C" __declspec(dllimport) double __cdecl f(double)` plus an
// `__imp__` pin, and the virtual is slot 11 on `this` with the item as its
// only argument.
// Residue: retail rounds the double to FLOAT in a stack slot and reloads it
// before the fistp (`fstp [esp+14h]` / `fld [esp+0ch]` / `fistp [esp+4]`),
// using the dead parameter slot for the float and a `push ecx` slot for the
// int; MSVC fistps the double straight out of st0 into one 8-byte frame.
// Marking the float volatile forces the round trip but costs a slot (77).
// An int return gives the 32-bit `sbb eax,eax` but loses elsewhere (69).
// cl: /QIfist
extern "C" __declspec(dllimport) double __cdecl bfmeMathVE(double value);

class BfmeItemVE
{
public:
	unsigned char m_bfmeHeadVE[0x4c];
	int m_bfmeLimitVE;
};

class BfmeOwnerVE
{
public:
	virtual void bfmeV0VE(void);
	virtual void bfmeV1VE(void);
	virtual void bfmeV2VE(void);
	virtual void bfmeV3VE(void);
	virtual void bfmeV4VE(void);
	virtual void bfmeV5VE(void);
	virtual void bfmeV6VE(void);
	virtual void bfmeV7VE(void);
	virtual void bfmeV8VE(void);
	virtual void bfmeV9VE(void);
	virtual void bfmeV10VE(void);
	virtual float bfmeComputeVE(BfmeItemVE *item);

	char bfmeCheckVE(BfmeItemVE *item);
};

char BfmeOwnerVE::bfmeCheckVE(BfmeItemVE *item)
{
	if (*(void **)((char *)this - 0x18) == 0)
		return 0;

	if (item == 0)
		return 0;

	int limit = item->m_bfmeLimitVE;
	float value = (float)bfmeMathVE(bfmeComputeVE(item));

	int rounded = (int)value;
	int result = (unsigned int)limit >= (unsigned int)rounded;

	return (char)result;
}
