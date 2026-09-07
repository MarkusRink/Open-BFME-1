// ??0LaserFXNugget@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the 32-byte LaserFXNugget constructor at 0x00429460.
//
// FXList's Laser parser at 0x0042C090 constructs a C8-byte LaserFXNugget,
// calls FXNugget's 225-byte base constructor, installs vtable 0x010F3438,
// and initializes the +0xB4/+0xB8 Laser fields.  The standalone constructor
// at 0x00429460 performs that derived initialization; the old W3DOverlord
// name was a false identity on the same byte range.

extern unsigned char bfme_LaserFXNugget_vtable;

class FXNugget
{
public:
	void *volatile m_vtable;
	char m_baseFields[0xB0];
	FXNugget();
};

class LaserFXNugget : public FXNugget
{
public:
	volatile unsigned int m_fieldB4;
	volatile bool m_fieldB8;

	LaserFXNugget();
};

LaserFXNugget::LaserFXNugget()
{
	unsigned int zero = 0;
	m_vtable = &bfme_LaserFXNugget_vtable;
	m_fieldB4 = zero;
	m_fieldB8 = static_cast<bool>( zero );
}
