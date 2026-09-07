// ?Rva007F7350Thunk@@YAXPAHPAX@Z
void d_007f72d0();

struct Rva007F72D0Obj
{
	void dump( int value );
};

typedef void( Rva007F72D0Obj::*Rva007F72D0MemFn )( int );

union Rva007F72D0Cast
{
	void *raw;
	Rva007F72D0MemFn fn;
};

void Rva007F7350Thunk( int value, Rva007F72D0Obj *obj )
{
	Rva007F72D0Cast u;
	u.raw = (void *)d_007f72d0;
	(obj->*u.fn)( value );
}
