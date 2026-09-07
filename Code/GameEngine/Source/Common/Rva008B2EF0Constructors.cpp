// cl: /DNDEBUG /MD /EHsc
// Address-derived interfaces: original class and argument types are unresolved.
class Rva00899F00Base {
public:
    Rva00899F00Base(unsigned int argument0, unsigned int argument1);
    virtual void rva008991B0();
private:
    // The base constructor reaches +0x1F; no larger extent is assumed.
    unsigned char m_unknown04[0x1c];
};

class Rva008B2EF0 : public Rva00899F00Base {
public:
    __declspec(noinline) Rva008B2EF0(unsigned int argument0, unsigned int argument1);
private:
    unsigned int m_value20;
    unsigned int m_value24;
};

class Rva008B38D0 : public Rva008B2EF0 {
public:
    Rva008B38D0(unsigned int argument0);
};

Rva008B2EF0::Rva008B2EF0(unsigned int argument0, unsigned int argument1)
    : Rva00899F00Base(argument0, 8), m_value20(argument1), m_value24(0) {}

Rva008B38D0::Rva008B38D0(unsigned int argument0)
    : Rva008B2EF0(0x21, argument0) {}
