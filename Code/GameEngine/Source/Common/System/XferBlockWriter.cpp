// cl: /DNDEBUG /MD /O2 /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
// Signed 32-bit storage is chosen for this reconstructed file-position interface;
// retail's original int-versus-long template spelling is unresolved.
class XferBlockPositionStack : private std::vector<int>
{
public:
    typedef int position_type;
    __declspec(noinline) void pushPosition(const position_type &position);
};

// Keep the retail call boundary while exposing the vendor body to its caller.
void XferBlockPositionStack::pushPosition(const position_type &position)
{
    std::vector<int>::push_back(position);
}
