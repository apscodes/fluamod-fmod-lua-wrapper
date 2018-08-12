#pragma once
#include <lua.hpp>

/*- X -*/

class LuaObject
{

public:

	/*	
	*	Setting the lua state of 'L'
	*	Opening the default libraries for Lua
	*	Setting the this pointer reference as 'self' 
	*/
	LuaObject();
	/*- X -*/
	~LuaObject() {};
		
	/*- Loading the lua script via the scripts file path -*/
	bool LoadScript(const char* luaSFilePath);
			
	/*- Adding a function to the lua stack via a name and a function pointer -*/
	void RegisterLuaFunction(const char* szFuncName, lua_CFunction fcnFunction); 
	
	/*- Calling a function from the stack based on the argCount and returnCount -*/
	bool CallFunction(int argCount, int returnCount);
	
	/*- Binding a reference 'self' to the lua state -*/
	static void SetPointerVar(lua_State* pState, const char* pVarName, void* vpVal); 

	/*- Getting a reference to itself via the current lua state and pointer reference as 'self' -*/
	static void* GetPointerVar(lua_State* pState, const char* pVarName); 
	
	/*- Pushing a float value to the lua stack -*/
	void PushFloat(float fValue); 
	
	/*- Removing a float value from the lua stack -*/
	float PopFloat(); 
	
	/*- Adding a function to the lua stack -*/
	void PushFunction(const char* szFunction);

private:
	
	/*- Main Lua State -*/
	lua_State* L;
};

