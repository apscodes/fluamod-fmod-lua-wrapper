#include "LuaObject.h"
#include <iostream>
using namespace std;

LuaObject::LuaObject()
{
	L = luaL_newstate();
	luaL_openlibs(L); 
	// Pass the "self" pointer to lua so that it can be used in scripts 
	SetPointerVar(L, "self", this);
}

		
///loading a lua script into the project
bool LuaObject::LoadScript(const char * luaSFilePath)
{
	int status = luaL_dofile(L, luaSFilePath);				//Loads in the Lua Script File from FilePath
	
	if (status)												//If no Lua Script was found
	{
		cout << "No file found at : " << luaSFilePath << lua_tostring(L, -1) << endl;
		return false;
	}
	
	//Run the Init function in the script
	//Start by putting the function on the Lua Stack
	lua_getglobal(L, "Start");

	//Call the function
	status = lua_pcall(L, 0, 0, NULL);

	if (status)												//Error for a function that doesn't exist
	{
		cout << "Couldn't run a function called : " << lua_tostring(L, -1) << endl;
	}

	return true;
}

///Registering a function to the lua stack using a function pointer
void LuaObject::RegisterLuaFunction(const char * szFuncName, lua_CFunction fcnFunction)
{
	lua_register(L, szFuncName, fcnFunction);
}

///Get the function from the stack
bool LuaObject::CallFunction(int argCount, int returnCount)
{
	if (!lua_isfunction(L, -(argCount + 1)	)	)	
	{
		cout << "LuaObject::CallFunction - function is not in the correct position on the stack" << endl;
		return false;
	}

	int status = lua_pcall(L, argCount, returnCount, NULL);

	if (status)												//Failed attempt at calling the funtion
	{
		cout << "Couldn't run the function : " << lua_tostring(L, -1) << endl;
		return false;
	}

	return true;											
}


///Set the reference that lua is being used on.
void LuaObject::SetPointerVar(lua_State * pState, const char * pVarName, void * vpVal)
{
	lua_pushlightuserdata(pState, vpVal);
	lua_setglobal(pState, pVarName);
}


///Get a reference to the object that lua is being used on.
void * LuaObject::GetPointerVar(lua_State * pState, const char * pVarName)
{
	lua_getglobal(pState, pVarName);

	if (lua_isuserdata(pState, -1) == false)
	{
		cout << "LuaObject::GetPointerVar: Variable is not a pointer" << endl;
		return nullptr;
	}
	else
	{
		void* vpVal = (void*)lua_topointer(pState, -1);
		lua_pop(pState, 1);
		return vpVal;
	}

	return nullptr;
}

///Adding a float to the lua stack
void LuaObject::PushFloat(float fValue)
{
	if (lua_isnumber(L, -1) == false)
	{
		int stackSize = lua_gettop(L);
		cout << "LuaObject::PopFloat: Variable is not a number" << endl;
	}
	else
	{
		lua_pushnumber(L, (LUA_NUMBER)fValue);
	}
}

///Take a float from the lua stack
float LuaObject::PopFloat()
{
	if (lua_isnumber(L, -1) == false)
	{
		int stackSize = lua_gettop(L);
		cout << "LuaObject::PopFloat: Variable is not a number" << endl;
		return 0.0f;
	}
	else
	{
		float fVal = (float)lua_tonumber(L, -1);
		lua_pop(L, 1);
		return fVal;
	}

}

///Add a function to the lua stack
void LuaObject::PushFunction(const char * szFunction)
{
	lua_getglobal(L, szFunction);

	if (lua_isfunction(L, -1) == false)
	{
		cout << "LuaObject::PushFunction: variable is not a function" << endl;
	}
}
