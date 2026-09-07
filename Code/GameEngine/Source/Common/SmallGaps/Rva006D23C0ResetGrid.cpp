// ?resetGrid@Rva006D23C0Owner@@QAEXXZ
void __cdecl d_006ccdb0();
class BfmeThingBKF { public: void bfmeGoBKF(); };
struct Rva006D23C0GlobalData { char m_pad[0x38]; bool m_38; char m_pad2[0x44 - 0x39]; bool m_44; };
extern Rva006D23C0GlobalData* TheWritableGlobalData;
struct Rva006D23C0Cell { char m_bytes[0xc4]; };
struct Rva006D23C0Owner {
	char m_pad[0x30d8];
	Rva006D23C0Cell* m_cells;
	int m_30dc;
	int m_width;
	int m_height;
	void resetGrid();
};
void Rva006D23C0Owner::resetGrid()
{
	d_006ccdb0();
	TheWritableGlobalData->m_38 = false;
	TheWritableGlobalData->m_44 = false;
	for (int x = 0; x < m_width; ++x) {
		for (int y = 0; y < m_height; ++y)
			((BfmeThingBKF*)&m_cells[y * m_width + x])->bfmeGoBKF();
	}
}
