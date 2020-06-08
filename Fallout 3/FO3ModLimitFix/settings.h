#pragma once

#include <types.h>

#include <SimpleIni.h>

#define INI_NAME "mod_limit_fix.ini"

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
		"; Reducing it unnecessarily will not lead to performance gains!"
		);

	settings.bDebug = ini.GetOrCreate(
		"Logging", "bDebug", 0,
		"; This will enter debug mode.\n"
		"; All stack activity will be logged into mod_limit_fix.log\n"
		"; Leaving this on will lead to a decrease in performance and a large log file!"
		);

	ini.SaveFile(iniPath, 0);
}
