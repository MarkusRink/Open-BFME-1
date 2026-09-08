// ?bfmeAddAK@BfmeListAK@@QAEXPAX0@Z
// partial score=0.75 date=2026-09-08
// Best clean reconstruction: key lookup followed by STLport vector insertion.
// The compiler still allocates this/value/key differently from retail.
struct BfmeVectorRawAK
{
	void **m_bfmeBeginAK;
	void **m_bfmeEndAK;
	void **m_bfmeCapAK;
};

class BfmeNodeAK
{
public:
	_STL::vector<void *> m_bfmeValuesAK;
	void *m_bfmeKeyAK;
	BfmeNodeAK *m_bfmeNextAK;
};

class BfmeListAK
{
public:
	void bfmeAddAK(void *key, void *value)
	{
		BfmeNodeAK *n = m_bfmeRootAK;
		m_bfmeHeadAK = n;
		while (n != 0) {
			if (n->m_bfmeKeyAK == key)
				break;
			n = n->m_bfmeNextAK;
		}
		if (n != 0) {
			n->m_bfmeValuesAK.push_back(value);
			return;
		}
		n = (BfmeNodeAK *)::operator new(0x14);
		BfmeVectorRawAK *values = (BfmeVectorRawAK *)n;
		values->m_bfmeBeginAK = 0;
		values->m_bfmeEndAK = 0;
		values->m_bfmeCapAK = 0;
		n->m_bfmeKeyAK = key;
		n->m_bfmeNextAK = 0;
		n->m_bfmeValuesAK.push_back(value);
		n->m_bfmeNextAK = m_bfmeRootAK;
		m_bfmeRootAK = n;
	}

	BfmeNodeAK *m_bfmeHeadAK;
	BfmeNodeAK *m_bfmeRootAK;
};
