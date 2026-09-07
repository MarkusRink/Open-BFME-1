// ?d_00993510@@YAXXZ
// partial score=0.85 date=2026-09-08
struct lua_State;

extern "C" void *__cdecl lua_touserdata(lua_State *L, int index);
extern "C" void __cdecl lua_settop(lua_State *L, int index);
extern "C" const char *__cdecl luaL_check_lstr(lua_State *L, int narg, int *len);

__declspec(dllimport) void *__cdecl bfmeFopenVIF(const char *name, const char *mode);

int __cdecl bfmeAttachVIF(void *handle, int mode);

int __cdecl bfmeLuaAppendVIF(lua_State *L)
{
	void *handle = lua_touserdata(L, -1);

	lua_settop(L, -2);

	void *file = bfmeFopenVIF(luaL_check_lstr(L, 1, 0), "a");

	return bfmeAttachVIF(handle, 1);
}
