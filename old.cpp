#include <Windows.h>
#include "Rlua.h" // Your address file name
#include <sstream>

namespace Commands
{
	void WalkSpeed(DWORD RL) // Change "DWORD" to lua_State if using wrapper.
	{
		r_lua_getglobal(RL, "game");
		r_lua_getfield(RL, -1, "Players");
		r_lua_getfield(RL, -1, "LocalPlayer");
		r_lua_getfield(RL, -1, "Character");
		r_lua_getfield(RL, -1, "Humanoid");
		r_lua_pushnumber(RL, 100);
		r_lua_setfield(RL, -2, "WalkSpeed");
	}

	void LowGravity(DWORD RL)
	{
		r_lua_getglobal(RL, "game");
		r_lua_getfield(RL, -1, "Workspace");
		r_lua_pushnumber(RL, 50);
		r_lua_setfield(RL, -2, "Gravity");
	}

	void PrintIdentity(DWORD RL)
	{
		r_lua_getglobal(RL, "printidentity");
		r_lua_pcall(RL, 1, 1, 0);
	}

	void ForceField(DWORD RL)
	{
		r_lua_getglobal(RL, "game");
		r_lua_getfield(RL, -1, "Players");
		r_lua_getfield(RL, -1, "LocalPlayer");
		r_lua_getfield(RL, -1, "Character");
		r_lua_getglobal(RL, "Instance");
		r_lua_getfield(RL, -1, "new");
		r_lua_pushstring(RL, "ForceField");
		r_lua_pushvalue(RL, -4);
		r_lua_pcall(RL, 2, 0, 0);
	}
}

static std::vector<std::string> SplitArguments(std::string string)
{
	std::vector<std::string> elements;
	std::stringstream start(string);
	std::istream_iterator<std::string> begin(start);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vectorStrings(begin, end);
	return vectorStrings;
}

int ExecuteCommand(std::string script, DWORD rL) // Im not sure if this works, didnt test.
{
	const char* cmd = r_lua_tostring(rL, -1); // add tostring bruh.
	if (cmd == "forcefield()")
	{
		Commands::ForceField(rL);
	}
	else if (cmd == "printidentity()")
	{
		Commands::PrintIdentity(rL);
	}
	else if (cmd == "walkspeed()")
	{
		Commands::WalkSpeed(rL);
	}
	return rL;
}
