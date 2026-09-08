// ?bfmeAtEndYJ@BfmeHostYJ@@QAE_NI@Z
// partial score=0.98 date=2026-09-08
namespace _STL
{

struct _Rb_tree_node_base
{
	unsigned char m_bfmeHeadYJ[0x28];
	unsigned int m_bfme28YJ;
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *n);
};

}

class BfmeHostYJ
{
public:
	bool bfmeAtEndYJ(unsigned int limit);

	_STL::_Rb_tree_node_base *m_bfme00YJ;
	_STL::_Rb_tree_node_base *m_bfme04YJ;
};

bool BfmeHostYJ::bfmeAtEndYJ(unsigned int limit)
{
	if (m_bfme04YJ == 0)
		return true;

	unsigned int v = _STL::_Rb_global<bool>::_M_decrement(m_bfme00YJ)->m_bfme28YJ;

	return v < limit;
}
