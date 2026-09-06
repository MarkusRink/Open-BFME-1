// cl: /O2 /Ob2 /G6

// Retail frees these arrays through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0). Without the declaration cl falls back to scalar
// operator delete for the block, which is a different body at 0x00881EB0.
void __cdecl operator delete[](void *block);
typedef int Int;
typedef float Real;

class BfmeCell
{
public:
	~BfmeCell();

private:
	unsigned char m_data[0x88];
};

class BfmeCellGrid
{
public:
	void _bfme_reset();

private:
	Int m_width;
	Int m_height;
	Int m_cellCount;
	Real m_cellSize;
	Real m_offset;
	BfmeCell *m_cells;
	Int *m_cellValues;
};

void BfmeCellGrid::_bfme_reset()
{
	if (m_cells)
	{
		delete[] m_cells;
		m_cells = 0;
	}

	Int *cellValues = m_cellValues;

	m_width = 0;
	m_height = 0;
	m_cellCount = 0;
	m_offset = 0.0f;
	m_cellSize = 0.0f;

	if (cellValues)
	{
		delete[] cellValues;
		m_cellValues = 0;
	}
}
