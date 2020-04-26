#pragma once

#include <string>
#include <vector>

#include "fose/PluginAPI.h"

class PluginManager
{
public:
	PluginManager();
	~PluginManager();

	bool	Init(void);
	void	DeInit(void);

	PluginInfo *	GetInfoByName(const char * name);
	PluginInfo *	GetInfoFromHandle(PluginHandle handle);
	PluginInfo *	GetInfoFromBase(UInt32 baseOpcode);
	const char *	GetPluginNameFromHandle(PluginHandle handle);

	UInt32			GetNumPlugins(void);
	UInt32			GetBaseOpcode(UInt32 idx);
	PluginHandle	LookupHandleFromBaseOpcode(UInt32 baseOpcode);
	PluginHandle	LookupHandleFromName(const char* pluginName);
	PluginHandle	LookupHandleFromPath(const char* pluginPath);

	static bool			RegisterCommand(CommandInfo * _info);
	static bool			RegisterTypedCommand(CommandInfo * _info, CommandReturnType retnType);
	static void			SetOpcodeBase(UInt32 opcode);
	static void *		QueryInterface(UInt32 id);
	static PluginHandle	GetPluginHandle(void);
	static const char *	GetFalloutDir();

	static bool Dispatch_Message(PluginHandle sender, UInt32 messageType, void * data, UInt32 dataLen, const char* receiver);
	static bool	RegisterListener(PluginHandle listener, const char* sender, FOSEMessagingInterface::EventCallback handler);

private:
	struct LoadedPlugin
	{
		HMODULE		handle;
		PluginInfo	info;
		UInt32		baseOpcode;

		_FOSEPlugin_Query	query;
		_FOSEPlugin_Load	load;
		char path[MAX_PATH];			// Added from NVSE
	};

	bool	FindPluginDirectory(void);
	bool	InstallPlugin(std::string pluginPath);
	void	InstallPlugins(void);

	const char *	SafeCallQueryPlugin(LoadedPlugin * plugin, const FOSEInterface * fose);
	const char *	SafeCallLoadPlugin(LoadedPlugin * plugin, const FOSEInterface * fose);

	const char *	CheckPluginCompatibility(LoadedPlugin * plugin);

	typedef std::vector <LoadedPlugin>	LoadedPluginList;

	std::string			m_pluginDirectory;
	LoadedPluginList	m_plugins;

	static LoadedPlugin		* s_currentLoadingPlugin;
	static PluginHandle		s_currentPluginHandle;
};

extern PluginManager	g_pluginManager;

extern CommandInfo kCommandInfo_IsPluginInstalled;
extern CommandInfo kCommandInfo_GetPluginVersion;
