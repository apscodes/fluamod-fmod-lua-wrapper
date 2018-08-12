#pragma once

//Additional Includes
#include <string>
using namespace std;


//Lua Base Functionallity
#include "LuaObject.h"

//FMOD API
#include <fmod.hpp>
#include <fmod_errors.h>
using namespace FMOD;

class FLUAMOD :	public LuaObject
{
public:
	
	//*! Default constructor
	FLUAMOD();
	~FLUAMOD() {};

	//*! Registered function - function pointer of "PlaySound"
	static int LuaPlaySound(lua_State * L);
	
	//*! C++ Functions for the LuaPlaySound()
	/*- Return bool for a successful execution of the function -*/
	bool PlaySound();
	bool PlaySound(string soundFile);
	bool PlaySound(string soundFile, float playBackFrequency);

	//*! F_System Functions
	FMOD::System * FMOD_System() { return F_System; }
		
private:
	
	//*! FMOD Setup Defaults
	bool Setup_FMOD();

	//*! FMOD enum error codes returned from every function;
	FMOD_RESULT F_Result;
	
	//*! FMOD System;
	System * F_System;
	
	/*- FMOD Classes -*/
	ChannelControl * F_ChannelControl;
	Channel * F_Channel;
	ChannelGroup * F_ChannelGroup;

	Sound * F_Sound;
	SoundGroup * F_SoundGroup;

	DSP * F_DSP;
	DSPConnection * F_DSPConnection;

	Geometry * F_Geometry;
	Reverb3D * F_Reverb3D;
};
	


