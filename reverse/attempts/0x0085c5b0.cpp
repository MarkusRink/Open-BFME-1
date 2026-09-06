// _AsciiToUCS2String
// partial score=0.85 date=2026-09-06
extern "C" int AsciiToUCS2String(const char *theAsciiString, unsigned short *theUCS2String)
{
	int length = 0;
	const char *p = theAsciiString;
	if (!p)
	{
		*theUCS2String = 0;
		return 1;
	}
	while (*p)
	{
		*theUCS2String = (unsigned char)*p;
		theUCS2String++;
		p++;
		length++;
	}
	*theUCS2String = 0;
	return length + 1;
}
