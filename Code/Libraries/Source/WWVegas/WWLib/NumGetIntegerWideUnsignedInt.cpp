// cl: /O2 /MD
// STLport 4.5.3 wide unsigned-int _M_do_get_integer at retail 0x008348D0.
// The 47-byte num_get wrapper at 0x008348A0 calls this body, which uses the
// wide base parser at 0x00833DE0 and the unsigned-int digit parser at 0x008349D0.

namespace _STL
{
	template <class CharT>
	class char_traits
	{
	};

	template <class CharT>
	class allocator
	{
	};

	template <class CharT, class Traits, class Alloc>
	class basic_string
	{
	public:
		CharT *m_start;
		CharT *m_finish;
		CharT *m_end_of_storage;

		bool empty() const { return m_start == m_finish; }
		const CharT *data() const { return m_start; }
		unsigned int size() const
		{
			return (unsigned int)(m_finish - m_start);
		}
	};

	typedef basic_string<char, char_traits<char>, allocator<char> > string;

	template <class CharT, class Traits>
	class istreambuf_iterator
	{
	public:
		istreambuf_iterator(void * = 0);

		bool equal(const istreambuf_iterator &other) const
		{
			if (m_buf)
				_M_getc();
			if (other.m_buf)
				other._M_getc();
			return m_eof == other.m_eof;
		}

		void _M_getc() const;

		CharT operator*() const
		{
			_M_getc();
			return m_c;
		}

		istreambuf_iterator &operator++()
		{
			m_have_c = 0;
			return *this;
		}

		void *m_buf;
		mutable CharT m_c;
		mutable unsigned char m_eof;
		mutable unsigned char m_have_c;
	};

	template <class CharT, class Traits>
	inline bool operator==(const istreambuf_iterator<CharT, Traits> &left,
		const istreambuf_iterator<CharT, Traits> &right)
	{
		return left.equal(right);
	}

	template <class CharT, class Traits>
	inline bool operator!=(const istreambuf_iterator<CharT, Traits> &left,
		const istreambuf_iterator<CharT, Traits> &right)
	{
		return !left.equal(right);
	}

	struct __false_type
	{
	};

	template <class CharT>
	class numpunct
	{
	public:
		virtual void slot_0() const;
		virtual void slot_1() const;
		virtual CharT thousands_sep() const;
	};

	class ios_base
	{
	public:
		typedef int iostate;
		static const iostate goodbit = 0;
		static const iostate eofbit = 2;
		static const iostate failbit = 4;

		const void *_M_numpunct_facet() const
		{
			return *(const void **)((const char *)this + 0x44);
		}

		const string &_M_grouping() const
		{
			return *(const string *)((const char *)this + 0x48);
		}
	};

	typedef istreambuf_iterator<unsigned short,
		char_traits<unsigned short> > WideIterator;

	template <class InputIter, class CharT>
	int _M_get_base_or_zero(InputIter &, InputIter &, ios_base &,
		CharT *);

	template <class InputIter, class Integer>
	bool __get_integer(InputIter &, InputIter &, int, Integer &, int,
		bool, char, const string &, const __false_type &);

	template <class InputIter, class Integer, class CharT>
	InputIter _M_do_get_integer(InputIter &in, InputIter &end,
		ios_base &str, ios_base::iostate &err, Integer &val, CharT *pc)
	{
		const numpunct<CharT> &punct = *(const numpunct<CharT> *)
			str._M_numpunct_facet();
		const string &grouping = str._M_grouping();
		const int base_or_zero = _M_get_base_or_zero(in, end, str, pc);
		const int got = base_or_zero & 1;
		bool result;

		if (in == end)
		{
			if (got > 0)
			{
				val = 0;
				result = true;
			}
			else
				result = false;
		}
		else
		{
			const bool negative = (base_or_zero & 2) != 0;
			const int base = base_or_zero >> 2;
			result = __get_integer(in, end, base, val, got, negative,
					punct.thousands_sep(), grouping, __false_type());
		}

		err = (ios_base::iostate)(result ? ios_base::goodbit : ios_base::failbit);
		if (in == end)
			err = (ios_base::iostate)(err | ios_base::eofbit);
		return in;
	}

	template istreambuf_iterator<unsigned short, char_traits<unsigned short> >
	_M_do_get_integer<WideIterator, unsigned int, unsigned short>(
		WideIterator &, WideIterator &, ios_base &, ios_base::iostate &,
		unsigned int &, unsigned short *);
}
