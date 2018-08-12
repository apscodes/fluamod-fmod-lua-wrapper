#include "FLUAMOD.h"
#include <cassert>

FLUAMOD::FLUAMOD()
{
	//*! Early exit if this fails
	if (!Setup_FMOD())
		return;

	//*! Successful setup of FMOD Default Settings
	printf("FMOD Setup\n");

	//*! Add the PlaySound keyword to a dictionary with the function
	//*! attached to the keyword.
	RegisterLuaFunction("PlaySound", LuaPlaySound);
}
 
//*! Default PlaySound - No Args
bool FLUAMOD::PlaySound()
{
	//*! Create a sound
	F_Result = F_System->createSound("./audio/powerup.wav", FMOD_DEFAULT, 0, &F_Sound);

	//*! Check status
	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		//*! Early exit
		return false;
	}
 
	//*! Test Sound
	F_Result = F_System->playSound(F_Sound, F_ChannelGroup, false, &F_Channel);

	//*! Check status
	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		//*! Early Exit
		return false;
	}
	
	return true;
}

//*! Overriden PlaySound - One Args
bool FLUAMOD::PlaySound(std::string soundFile)
{
	//Create a sound
	F_Result = F_System->createSound(soundFile.c_str(), FMOD_DEFAULT, 0, &F_Sound);

	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}

	//F_Result = F_Sound->setMusicSpeed(0.1f);
	//printf("Changed the speed of the music track");

	//if (F_Result != FMOD_OK)
	//{
	//	printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
	//	return false;
	//}

	//Test Sound
	F_Result = F_System->playSound(F_Sound, F_ChannelGroup, false, &F_Channel);

	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}

	return true;
}

//*! Overriden PlaySound - Two Args
bool FLUAMOD::PlaySound(std::string soundFile, float playBackFrequency)
{
	//Create a sound
	F_Result = F_System->createSound(soundFile.c_str(), FMOD_DEFAULT, 0, &F_Sound);

	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}
	
	//F_Result = F_Sound->setMode(FMOD_LOOP_NORMAL);
	////Loop once and stop
	//F_Result = F_Sound->setLoopCount(1);
	
	F_Result = F_Sound->setDefaults(playBackFrequency, 0);
	
	//---F_Result = F_Channel->setFrequency(playBackFrequency);
	//printf("Changed the speed of the music track, %d", playBackFrequency);

	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}

	//Test Sound
	F_Result = F_System->playSound(F_Sound, F_ChannelGroup, false, &F_Channel);

	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}


	return true;
}

//*! Lua Access point
int FLUAMOD::LuaPlaySound(lua_State * L)
{
	//*! Create a FLUAMOD Object holfing the data of a LuaObject, then casted to a FLUAMOD Object
	FLUAMOD* flua = (FLUAMOD*)GetPointerVar(L, "self");
 
	//*! How many args were passed into the PlaySound function call
	switch (lua_gettop(L))
	{
	//*! No arrguments
	case 0:
	{
		if (!flua->PlaySound())
		{
			printf("Failed to play default sound.");
		}
		break;
	}
	//*! One Argument
	case 1:
	{
		//*! Is the arg a file name
		assert(lua_isstring(L, 1));

		//*! Construct a file path for the sound file
		const char * filePath = "./audio/";
		const char * soundFile = lua_tostring(L, 1);

		//*! Compile the two parts for the sound file path
		std::string result = filePath;
		result += soundFile;

		//*! Get the filename string off the Lua Stack
		lua_pop(L, 1);

		//*! Play the sound with the compiled sound file path
		if (!flua->PlaySound(result))
		{
			//*! If the sound failed to play
			printf("Failed to play custom sound.");
		}
		break;
	}

	//*! Two Arguments
	case 2:
	{
		assert(lua_isstring(L, 1));//is the arg a file name
		assert(lua_isnumber(L, 2));//is the arg a number (float)

		const char * filePath = "./audio/";
		const char * soundFile = lua_tostring(L, 1);

		float playBackFrequency = lua_tonumber(L, 2);

		lua_pop(L, 2);

		string result = filePath;
		result += soundFile;

		if (!flua->PlaySound(result, playBackFrequency))
		{
			printf("Failed to play custom sound.");
		}

		break;
	}
	//*! Three Arguments
	case 3:
	{
		//?Futher expantion
		break;
	}
	//*! More Arguments entered than implemented
	default:
		printf("More Arguments entered than implemented.");
		break;
	}
	return 0;
}

 

 

bool FLUAMOD::Setup_FMOD()
{	
	F_System = NULL;
	F_Result = FMOD::System_Create(&F_System);
	
	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}

	//Create
	F_Result = F_System->init(512, FMOD_INIT_NORMAL, 0);

	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}
 
	//Create a channel group
	F_Result = F_System->createChannelGroup("Main", &F_ChannelGroup);
	
	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}
 
	//Get the first channel
	F_Result = F_System->getChannel(0, &F_Channel);

	if (F_Result != FMOD_OK)
	{
		printf("FMOD Error! (%d), %s\n", F_Result, FMOD_ErrorString(F_Result));
		return false;
	}
 
	return true;
}
