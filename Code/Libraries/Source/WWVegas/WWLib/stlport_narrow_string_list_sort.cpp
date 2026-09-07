// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: _STL::list<_STL::basic_string<char> >::sort helper at retail
// RVA 0x0037F960, 394 bytes. The W3D dependency scanner calls list::sort and
// list::unique at 0x0037FCB0, which identifies this body as the STLport sort
// instantiation used for its filename list.

#define _STLP_NO_EXCEPTIONS 1

#include <list>

namespace _STL
{

template <class CharT>
class char_traits
{
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string(const basic_string &other);
	~basic_string();

	bool operator<(const basic_string &other) const;

private:
	char *m_start;
	char *m_finish;
	char *m_end_of_storage;
	unsigned char m_padding[0xcc];
};

typedef basic_string<char, char_traits<char>, allocator<char> > BfmeStdString;

template <>
__declspec(noinline)
void _List_base<BfmeStdString, allocator<BfmeStdString> >::clear()
{
	_List_node<BfmeStdString> *__cur =
		(_List_node<BfmeStdString> *)this->_M_node._M_data->_M_next;
	while (__cur != this->_M_node._M_data) {
		_List_node<BfmeStdString> *__tmp = __cur;
		__cur = (_List_node<BfmeStdString> *)__cur->_M_next;
		_Destroy(&__tmp->_M_data);
		this->_M_node.deallocate(__tmp, 1);
	}
	this->_M_node._M_data->_M_next = this->_M_node._M_data;
	this->_M_node._M_data->_M_prev = this->_M_node._M_data;
}

template void _S_sort<BfmeStdString, allocator<BfmeStdString>, less<BfmeStdString> >(
	list<BfmeStdString, allocator<BfmeStdString> > &,
	less<BfmeStdString>);

}
