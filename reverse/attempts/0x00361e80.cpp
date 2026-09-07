// ?d_00361e80@@YAXXZ
// partial score=0.95 date=2026-09-08
struct Rva002E5FF0Str
{
	Rva002E5FF0Str(const Rva002E5FF0Str &other);
	~Rva002E5FF0Str();

	void *m_bfmeDataEAS;
};

extern Rva002E5FF0Str Rva01336E50Str;

class BfmeElemEAS
{
public:
	Rva002E5FF0Str bfmeNameEAS();

	unsigned char m_bfmeBodyEAS[0x58];
};

class BfmeVecEAS
{
public:
	Rva002E5FF0Str bfmeGetEAS(int index);

	unsigned char m_bfmeHeadEAS[0x18];
	BfmeElemEAS *m_bfmeBeginEAS;
	BfmeElemEAS *m_bfmeEndEAS;
};

Rva002E5FF0Str BfmeVecEAS::bfmeGetEAS(int index)
{
	if (index < 0 ||
		(unsigned int)index >= (unsigned int)(m_bfmeEndEAS - m_bfmeBeginEAS))
		return Rva01336E50Str;

	return m_bfmeBeginEAS[index].bfmeNameEAS();
}
