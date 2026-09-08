// ?bfmeUpdateBD@Rva000BD610Host@@QAEXXZ (identity unknown)
// partial score=0.75 date=2026-09-08
// Clean reconstruction of the 34-byte helper call at retail 0x000BD610.
// The callee is a method on the context stored at host+8; the result replaces
// host+0x0c.  The one-byte local is passed by address and the final argument is
// the literal zero visible in the retail push sequence.
class Rva000BD610Context
{
public:
	int bfmeUpdateBD(int first, int second, char *flag, int value);
};

class Rva000BD610Host
{
public:
	void bfmeUpdateBD();

	unsigned char m_prefix[8];
	Rva000BD610Context *m_context;
	int m_result;
};

void Rva000BD610Host::bfmeUpdateBD()
{
	char flag;
	m_result = m_context->bfmeUpdateBD(m_result, m_result, &flag, 0);
}
