#pragma once

#include <SimpleIni.h>

#define INI_NAME "mod_limit_fix.ini"

struct Settings
{
	HMODULE hnd;
	HANDLE dbg;
	DWORD iMaxHnd;
	BOOL bVerboseLog;
	BOOL bDebug;
};

Settings settings;

void InitSettings()
{
	char iniPath[MAX_PATH];
	GetModuleFileNameA(settings.hnd, iniPath, MAX_PATH);
	strcpy_s((char*)(strrchr(iniPath, '\\') + 1), MAX_PATH, INI_NAME);

	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(iniPath);

	settings.iMaxHnd = ini.GetOrCreate(
		"Settings", "iMaxHandles", 2048,
		"; This is the maximum number of file handles the game may open.\n"
		"; Leave this at 2048 unless the fix does not work.\n"
		"; If that is the case, try reducing the number in decrements of 256.\n"
		"; Reducing it unnecessarily will not lead to performance gains!\n"
	);

	settings.bVerboseLog = ini.GetOrCreate(
		"Logging", "bVerbose", 0,
		"; This will cause logging to enter verbose mode.\n"
		"; This can be useful to identify why the plugin is not working.\n"
		"; This only affects the log file.\n"
	);

	settings.bDebug = ini.GetOrCreate(
		"Logging", "bDebug", 0,
		"; Activate this if you are experiencing any issues while ingame.\n"
		"; This will log information to the game's console.\n"
		"; Logging only begins once ingame.\n"
	);

	ini.SaveFile(iniPath, 0);
}
