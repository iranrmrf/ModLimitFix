#pragma once

// 0C
class Setting
{
public:
	Setting();
	virtual ~Setting();

	virtual void Unk_01(void);

	enum EType	{
		kSetting_Bool = 0,
		kSetting_c,
		kSetting_h,
		kSetting_Integer,
		kSetting_Unsigned,
		kSetting_Float,
		kSetting_String,
		kSetting_r,
		kSetting_a,
		kSetting_Other
	};
	union Info {
		UInt32		uint;
		int			i;
		float		f;
		char		* str;
	};

	// void		** vtbl				// 00
	Info		data;				// 04
	char		* name;				// 08

	UInt32 GetType();
	bool Get(double& out);
	bool Set(double newVal);
};

// 120
class GameSettingCollection			// derived from SettingCollection
{
public:
	GameSettingCollection();
	virtual ~GameSettingCollection();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);

	// void				** vtbl							// 000
	UInt32				unk004[(0x10C - 0x004) >> 2];	// 004
	NiTMapBase<Setting>	settingMap;						// 10C BSTCaseInsensitiveStringMap
	UInt8				unk11C;							// 11C
	UInt8				pad11D[3];

	bool GetGameSetting(char* settingName, Setting** out);
	static GameSettingCollection * GetSingleton();
};

STATIC_ASSERT(sizeof(GameSettingCollection) == 0x120);

// 114
// actually 2 classes used: IniSettingCollection and IniPrefSettingCollection. Layouts are the same
class IniSettingCollection
{
public:
	IniSettingCollection();
	virtual ~IniSettingCollection();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);

	// void				** vtbl				// 000
	char				iniPath[0x100];		// 004
	UInt32				unk104;				// 104
	UInt32				unk108;				// 108
	tList<Setting>		settings;			// 10C;

	static IniSettingCollection * GetIniSettings();
	static IniSettingCollection * GetIniPrefs();
};

STATIC_ASSERT(sizeof(IniSettingCollection) == 0x114);

bool GetIniSetting(const char* settingName, Setting** out);
