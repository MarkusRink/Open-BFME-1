// cl: /DNDEBUG /MD /EHs-c-

extern void ji_00afd528();

typedef int (__stdcall *AviStreamWrite)( void *stream, long start,
	long samples, void *buffer, long bytes, long flags,
	long *samples_written, long *bytes_written );

class BfmeThingTXA
{
public:
	void bfmeDtorTXA();

	void *m_bfmeVft;
	int m_bfmeImageSize;
	int m_bfmeCount;
	void *m_bfmeBuf;
	int m_bfmeReserved0;
	int m_bfmeReserved1;
	void *m_bfmeB;
	void *m_bfmeA;
};

// ?bfmeDtorTXA@BfmeThingTXA@@QAEXXZ
void BfmeThingTXA::bfmeDtorTXA()
{
	if( m_bfmeA != 0 && m_bfmeBuf != 0 )
	{
		register int frame = 0;
		if( m_bfmeReserved1 > 0 )
		{
			int (__cdecl *format)( char *, const char *, ... ) =
				*(int (__cdecl **)( char *, const char *, ... ))0x0135948C;
			void (__stdcall *print)( const char * ) =
				*(void (__stdcall **)( const char * ))0x01358EA8;
			char error[ 0x100 ];
			for( ; frame < m_bfmeReserved1; ++frame )
			{
				int result = ((AviStreamWrite)ji_00afd528)( m_bfmeA,
					m_bfmeReserved0 + frame, 1,
					(char *)m_bfmeBuf + m_bfmeImageSize * frame,
					m_bfmeImageSize, 0x10, 0, 0 );
				if( result != 0 )
				{
					format( error, "avi write error %x/%d\n", result, result );
					print( error );
				}
			}
		}
	}

	int count = m_bfmeReserved1;
	m_bfmeReserved0 += count;
	m_bfmeReserved1 = 0;
}
