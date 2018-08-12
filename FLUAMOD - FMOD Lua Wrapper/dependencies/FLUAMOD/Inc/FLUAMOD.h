#pragma once
//Lua Base Functionallity
#include "LuaObject.h"

//FMOD API
#include <fmod.hpp>
#include <fmod_errors.h>
using namespace FMOD;

#include <string>

class FLUAMOD :	public LuaObject
{
public:
	
	//Default constructor
	FLUAMOD();
	
	//FLUAMOD(const char * aFilePath);

	~FLUAMOD() {};

	bool PlaySound();
	bool PlaySound(std::string soundFile);


	//Registered function - function pointer of "PlaySound"
	static int LuaPlaySound(lua_State * luaState);

	//static int LuaSetSound(lua_State * luaState);

	
	//F_System Functions
	FMOD::System * FMOD_System() { return F_System; }
		
private:
	
	//FMOD Setup Defaults
	bool Setup_FMOD();

	//FMOD enum error codes returned from every function;
	FMOD_RESULT F_Result;
	
	//class System;
	System * F_System;
	
	/*- FMOD Classes -*/

		//class ChannelControl;
		//class Channel;
		//class ChannelGroup;
		ChannelControl * F_ChannelControl;
		Channel * F_Channel;
		ChannelGroup * F_ChannelGroup;

		//class Sound;
		//class SoundGroup;
		Sound * F_Sound;
		SoundGroup * F_SoundGroup;

		//class DSP;
		//class DSPConnection;
		DSP * F_DSP;
		DSPConnection * F_DSPConnection;

		//class Geometry;
		//class Reverb3D;
		Geometry * F_Geometry;
		Reverb3D * F_Reverb3D;
	

};

