#include "Commands_Input.h"
#include "GameForms.h"

#include <set>
#include <map>
#include <ctime>
//#include "Commands_Console.h"

// 32	spacebar
// 48	0
// ...
// 57	9
// 65	A
// ...
// 90	Z
// 160	left shift
// 161	right shift
// 162	left control
// 163	right control

#include "GameAPI.h"

#include "Hooks_DirectInput8Create.h"
#include <shlobj.h>
#include "GameOSDepend.h"
//#include "StringVar.h"
//#include "GameMenus.h"
//#include "GameTiles.h"
#include "GameObjects.h"
#include <string>

static bool IsKeycodeValid(UInt32 id)		{ return (id < kMaxMacros - 2) && (id != 0xFF); }

enum {
	kControlType_Keyboard,
	kControlType_Mouse,
	kControlType_Joystick
};

UInt32 GetControl(UInt32 whichControl, UInt32 type)
{
	OSInputGlobals* globs = *g_OSInputGlobals;
	if (whichControl >= globs->kMaxControlBinds)
		return 0xFF;

	switch (type)
	{
	case kControlType_Keyboard:
		return globs->keyBinds[whichControl];
	case kControlType_Mouse:
		{
		UInt32 button = globs->mouseBinds[whichControl];
		if (button != 0xFF)
			button += 0x100;
		return button;
		}
	case kControlType_Joystick:
		return globs->joystickBinds[whichControl];
	default:
		return 0xFF;
	}
}

void SetControl(UInt32 whichControl, UInt32 type, UInt32 keycode)
{
	OSInputGlobals* globs = *g_OSInputGlobals;
	if (whichControl >= globs->kMaxControlBinds)
		return;

	UInt8* binds = (type == kControlType_Mouse) ? globs->mouseBinds : globs->keyBinds;
	keycode = (keycode >= 0x100) ? keycode - 0x100 : keycode;

	// if specified key already used by another control, swap with the new one
	for (UInt32 i = 0; i < OSInputGlobals::kMaxControlBinds; i++)
	{
		if (binds[i] == keycode)
		{
			binds[i] = binds[whichControl];
			break;
		}
	}

	binds[whichControl] = keycode;
}	

bool IsControl(UInt32 key)
{
	OSInputGlobals* globs = *g_OSInputGlobals;
	UInt8* binds = key >= 0x100 ? globs->mouseBinds : globs->keyBinds;
	key = key >= 0x100 ? key - 0x100 : key;

	for (UInt32 i = 0; i < OSInputGlobals::kMaxControlBinds; i++)
		if (binds[i] == key)
			return true;

	return false;
}

// Following is used to translate scan codes to virtual key codes
// only used to determine if a key disabled by DisableKey is being pressed
#define VK_TABLE_SIZE 212
#define NOKEY 0xFF

//MapVirtualKey() doesn't map arrowpad keys/some numpad keys
//macro isn't pretty but shortens a long switch block
#define DX2VK(keyConstant) case DIK_ ## keyConstant: vkCode = VK_ ## keyConstant; break;

static UInt8 ScancodeToVirtualKey(UINT dx){
	if (dx >= VK_TABLE_SIZE) 
		return NOKEY;

	UInt8 vkCode = NOKEY;
	HKL kbLayout = GetKeyboardLayout(0);
	vkCode = MapVirtualKeyEx(dx, 3, kbLayout);
	if (!vkCode)
	{
		switch (dx)
		{
			DX2VK(DIVIDE);
			DX2VK(RCONTROL);
			DX2VK(RMENU);
			DX2VK(HOME);
			DX2VK(PRIOR);
			DX2VK(UP);
			DX2VK(DOWN);
			DX2VK(LEFT);
			DX2VK(RIGHT);
			DX2VK(END);
			DX2VK(NEXT);
			DX2VK(INSERT);
			DX2VK(DELETE);

			case DIK_NUMPADENTER:
				vkCode = VK_SEPARATOR;
				break;
			default:
				vkCode = NOKEY;
		}
	}

	return vkCode;
}

static bool IsDisabledKeyPressed(UINT keyCode)
{
	if (keyCode < 255)
	{
		keyCode = ScancodeToVirtualKey(keyCode);
		if (!(keyCode == NOKEY))
			return (GetAsyncKeyState(keyCode) & 0x8000) ? true : false;
		else
			return false;
	}
	else
		return DI_data.IsKeyPressed(keyCode);
}

bool Cmd_IsKeyPressed_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if (ExtractArgs(EXTRACT_ARGS, &keycode))
		return Cmd_IsKeyPressed_Eval(thisObj, (void*)keycode, 0, result);

	return true;
}

bool Cmd_IsKeyPressed_Eval(COMMAND_ARGS_EVAL)
{
	*result = DI_data.IsKeyPressed((UInt32)arg1);
	return true;
}

bool Cmd_TapKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(ExtractArgs(EXTRACT_ARGS, &keycode)) 
		DI_data.TapKey(keycode);

	return true;
}

bool Cmd_HoldKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(ExtractArgs(EXTRACT_ARGS, &keycode))
		DI_data.SetKeyHeldState(keycode, true);

	return true;
}

bool Cmd_ReleaseKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(ExtractArgs(EXTRACT_ARGS, &keycode))
		DI_data.SetKeyHeldState(keycode, false);

	return true;
}

bool Cmd_DisableKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(ExtractArgs(EXTRACT_ARGS, &keycode))
		DI_data.SetKeyDisableState(keycode, true);

	return true;
}

bool Cmd_EnableKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(ExtractArgs(EXTRACT_ARGS, &keycode)) 
		DI_data.SetKeyDisableState(keycode, false);

	return true;
}

bool Cmd_IsKeyDisabled_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 keycode = 0;

	if (ExtractArgs(EXTRACT_ARGS, &keycode))
		*result = DI_data.IsKeyDisabled(keycode) ? 1 : 0;

	return true;
}

bool Cmd_GetNumKeysPressed_Execute(COMMAND_ARGS)
{
	DWORD count=0;
	for(DWORD d=0; d < 256; d++) 
		if(IsKeycodeValid(d) && DI_data.IsKeyPressed(d)) 
			count++;

	*result = count;
	if (IsConsoleMode())
		Console_Print("keysPressed: %d", count);

	return true;
}

bool Cmd_GetKeyPress_Execute(COMMAND_ARGS)
{
	*result = -1;
	UInt32 count=0;
	if(!ExtractArgs(EXTRACT_ARGS, &count))
		return true;

	for(DWORD d = 0; d < 256; d++) 
		if (IsKeycodeValid(d) && DI_data.IsKeyPressed(d) && (!count--)) 
		{
			*result = d;
			break;
		}

	return true;
}

bool Cmd_GetNumMouseButtonsPressed_Execute(COMMAND_ARGS)
{
	DWORD count=0;
	//Include mouse wheel? Probably not...

	for(DWORD d = 256; d < kMaxMacros -2; d++)
		if (IsKeycodeValid(d) && DI_data.IsKeyPressed(d)) 
			count++;

	*result = count;
	if (IsConsoleMode())
		Console_Print("buttonsPressed: %d", count);

	return true;
}

bool Cmd_GetMouseButtonPress_Execute(COMMAND_ARGS)
{
	*result = -1;
	UInt32 count=0;

	if(!ExtractArgs(EXTRACT_ARGS, &count)) 
		return true;

	for(DWORD d = 256; d < kMaxMacros - 2; d++)
		if (DI_data.IsKeyPressed(d) && (!count--))
		{
		*result = d;
		break;
		}

	return true;
}

static enum {
	kKeyState_Disabled =			1 << 0,
	kKeyState_PreviouslyPressed =	1 << 1,
	kKeyState_Tapped =				1 << 2,
	kKeyState_Pressed =				1 << 3
};

/*
bool Cmd_GetKeyState_Eval(COMMAND_ARGS_EVAL)
{
	UInt32 key = 0;
	UInt32 ignoreMask = 0;	// states to ignore
	UInt32 resultMask = 0;
	bool bPressed = false;

	// set of key events reported to scripts (stored by refID)
	static std::map<UInt32, set::set<UInt32> > keyEvents;

	*result = 0;

	if (ExtractArgs(EXTRACT_ARGS, &key, &ignoreMask))
	{
		bPressed = DI_Data.IsKeyPressed(key);
		// is disabled
		if (DI_data.IsKeyDisabled(key))
		{
			if (ignoreMask & kKeyState_Disabled)
				return true;		// ignore disabled keys
			else if (IsDisabledKeyPressed(key))
			{
				resultMask &= (kKeyState_Disabled);
				bPressed = true;
			}
		}

		if (!bPressed)
		{
			if (keyEvents.find(scriptObj->refID) != keyEvents.end())
			{
				std::set<UInt32> * keys = &keyEvents[scriptObj->refID];
				if (keys->find(key) != keys->end())
					keys->erase(key);
			}

			return true;
		}

		// is tapped?
		if (DI_Data.IsKeyTapped(key))
		{
			if (ignoreMask & kKeyStates_Tapped)
				return true;
			else
				resultMask &= kKeyStates_Tapped;
		}

		// was pressed previous frame?

		// is pressed?
		if (DI_Data.IsKeyPressed(key))
		{
			// is tapped?
			if (DI_Data.IsKeyTapped(key))
				resultMask &=
*/

////////////////////////////////////
// Menu versions of input functions
///////////////////////////////////

bool Cmd_MenuTapKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &keycode))
		return true;

    if(keycode<256) 
		DI_data.TapKey(keycode);

	return true;
}

bool Cmd_MenuHoldKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(ExtractArgs(EXTRACT_ARGS, &keycode) && keycode < 256) 
		DI_data.SetKeyHeldState(keycode, true);

	return true;
}

bool Cmd_MenuReleaseKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(ExtractArgs(EXTRACT_ARGS, &keycode) && keycode < 256)
		DI_data.SetKeyHeldState(keycode, false);

	return true;
}

//////////////////////////
// Controls
/////////////////////////

static bool disabledControls[OSInputGlobals::kMaxControlBinds] = { false };

bool SetControlDisableState_Execute(COMMAND_ARGS, bool bDisable)
{
	*result = 0;
	UInt32	ctrl = 0;

	if(ExtractArgs(EXTRACT_ARGS, &ctrl))
	{
		if (ctrl < OSInputGlobals::kMaxControlBinds)
		{
			disabledControls[ctrl] = bDisable;
			DI_data.SetKeyDisableState(GetControl(ctrl, kControlType_Keyboard), bDisable);
			DI_data.SetKeyDisableState(GetControl(ctrl, kControlType_Mouse), bDisable);
		}
	}

	return true;
}

bool Cmd_DisableControl_Execute(COMMAND_ARGS)
{
	return SetControlDisableState_Execute(PASS_COMMAND_ARGS, true);
}

bool Cmd_EnableControl_Execute(COMMAND_ARGS)
{
	return SetControlDisableState_Execute(PASS_COMMAND_ARGS, false);
}

bool Cmd_IsControlDisabled_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 ctrl = 0;

	if (ExtractArgs(EXTRACT_ARGS, &ctrl) && ctrl < OSInputGlobals::kMaxControlBinds)
		*result = disabledControls[ctrl] ? 1 : 0;

	return true;
}

bool Cmd_GetControl_Execute(COMMAND_ARGS)
{
	UInt32 whichControl = 0;
	*result = -1;

	if (!ExtractArgs(EXTRACT_ARGS, &whichControl))
		return true;

	UInt8 ctrl = GetControl(whichControl, kControlType_Keyboard);
	*result = (ctrl == 0xFF) ? -1 : ctrl;

	if (IsConsoleMode())
		Console_Print("GetControl %d >> %.0f", whichControl, *result);

	return true;
}

bool Cmd_GetAltControl_Execute(COMMAND_ARGS)
{
	UInt32 whichControl = 0;
	*result = -1;

	if (!ExtractArgs(EXTRACT_ARGS, &whichControl))
		return true;

	UInt8 ctrl = GetControl(whichControl, kControlType_Mouse);
	*result = (ctrl == 0xFF) ? -1 : ctrl;

	if (IsConsoleMode())
		Console_Print("GetAltControl %d >> %.0f", whichControl, *result);

	return true;
}

bool Cmd_IsControlPressed_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;

	UInt32 ctrl = (UInt32)arg1;
	UInt32 keycode = GetControl(ctrl, kControlType_Keyboard);

	if (keycode !=0xFF && DI_data.IsKeyPressed(keycode))
		*result = 1;
	else
	{
		keycode = GetControl(ctrl, kControlType_Mouse);
		if (keycode != 0xFF && DI_data.IsKeyPressed(keycode))
			*result = 1;
	}

	return true;
}

bool Cmd_IsControlPressed_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 ctrl = 0;

	if (ExtractArgs(EXTRACT_ARGS, &ctrl))
		return Cmd_IsControlPressed_Eval(thisObj, (void*)ctrl, 0, result);

	return true;
}
		
bool Cmd_TapControl_Execute(COMMAND_ARGS)
{
	//returns false if control is not assigned
	*result = 0;
	UInt32 ctrl = 0;
	UInt32 keycode = 0;

	if (ExtractArgs(EXTRACT_ARGS, &ctrl))
	{
		keycode = GetControl(ctrl, kControlType_Mouse);
		if (!IsKeycodeValid(keycode))
			keycode = GetControl(ctrl, kControlType_Keyboard);

		if (IsKeycodeValid(keycode))
		{
			*result = 1;
			DI_data.TapKey(keycode);
		}
	}

	return true;
}

bool Cmd_SetControl_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 key = 0;
	UInt32 ctrl = 0;

	if (ExtractArgs(EXTRACT_ARGS, &ctrl, &key))
		SetControl(ctrl, kControlType_Keyboard, key);

	return true;
}

bool Cmd_SetAltControl_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 key = 0;
	UInt32 ctrl = 0;

	if (ExtractArgs(EXTRACT_ARGS, &ctrl, &key))
		SetControl(ctrl, kControlType_Mouse, key);

	return true;
}

// lets scripters register user-defined controls to help avoid conflicts
// key = key/button code, data = set of mod indices of mods which have registered key as a custom control
typedef std::map< UINT, std::set<UInt8> > RegisteredControlMap;
static RegisteredControlMap registeredControls;

bool Cmd_SetIsControl_Execute(COMMAND_ARGS)
{
	// registers or unregisters a key for a particular mod
	UInt32 key = 0;
	UInt32 bIsControl = 1;
	UInt8 modIndex = scriptObj->GetModIndex();
	*result = 0;

	if (ExtractArgs(EXTRACT_ARGS, &key, &bIsControl) && key < kMaxMacros)
	{
		if (bIsControl)
			registeredControls[key].insert(modIndex);
		else
			registeredControls[key].erase(modIndex);
	}

	return true;
}

// returns 1 if game-assigned control, 2 is custom mod control, 3 if both, 0 otherwise
bool Cmd_IsControl_Execute(COMMAND_ARGS)
{
	UInt32 key = 0;
	*result = 0;

	if (!ExtractArgs(EXTRACT_ARGS, &key))
		return true;

	// check game controls
	*result = IsControl(key) ? 1 : 0;

	// check mod custom controls
	if (registeredControls[key].size())
		*result += 2;

	return true;
}

// don't think anyone ever actually used these in Oblivion
#if 0
bool Cmd_HammerKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &keycode)) return true;
	if(keycode%256==255&&keycode<2048) keycode=255+(keycode+1)/256;
    if(IsKeycodeValid(keycode)) DI_data.HammerStates[keycode]=0x80;

	return true;
}

bool Cmd_AHammerKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &keycode)) return true;
	if(keycode%256==255&&keycode<2048) keycode=255+(keycode+1)/256;
    if(IsKeycodeValid(keycode)) DI_data.AHammerStates[keycode]=0x80;

	return true;
}

bool Cmd_UnhammerKey_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32	keycode = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &keycode)) return true;
	if(keycode%256==255&&keycode<2048) keycode=255+(keycode+1)/256;
	if(IsKeycodeValid(keycode)) {
		DI_data.HammerStates[keycode]=0x00;
		DI_data.AHammerStates[keycode]=0x00;
	}

	return true;
}

bool Cmd_MoveMouseX_Execute(COMMAND_ARGS)
{
	*result = 0;
	int pixels = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &pixels)) return true;
    DI_data.MouseXMov+=pixels;

	return true;
}

bool Cmd_MoveMouseY_Execute(COMMAND_ARGS)
{
	*result = 0;
	int pixels = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &pixels)) return true;
    DI_data.MouseYMov+=pixels;

	return true;
}


bool Cmd_SetMouseSpeedX_Execute(COMMAND_ARGS)
{
	*result = 0;
	float speed = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &speed)) return true;
    DI_data.MouseXSpeed=speed;

	return true;
}

bool Cmd_SetMouseSpeedY_Execute(COMMAND_ARGS)
{
	*result = 0;
	float speed = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &speed)) return true;
    DI_data.MouseYSpeed=speed;

	return true;
}

bool Cmd_DisableMouse_Execute(COMMAND_ARGS)
{
	*result=0;
    DI_data.MouseDisable=true;

	return true;
}

bool Cmd_EnableMouse_Execute(COMMAND_ARGS)
{
	*result=0;
    DI_data.MouseDisable=false;

	return true;
}
#endif

// TODO: clean this up
#if 0
#define VK_TABLE_SIZE 212
#define NOKEY 0xFF

//MapVirtualKey() doesn't map arrowpad keys/some numpad keys
//macro isn't pretty but shortens a long switch block
#define DX2VK(keyConstant) case DIK_ ## keyConstant: vkCode = VK_ ## keyConstant; break;

static UInt8 _dx2vk(UINT dx){
	if (dx >= VK_TABLE_SIZE) 
		return NOKEY;

	UInt8 vkCode = NOKEY;
	HKL kbLayout = GetKeyboardLayout(0);
	vkCode = MapVirtualKeyEx(dx, 3, kbLayout);
	if (!vkCode)
	{
		switch (dx)
		{
			DX2VK(DIVIDE);
			DX2VK(RCONTROL);
			DX2VK(RMENU);
			DX2VK(HOME);
			DX2VK(PRIOR);
			DX2VK(UP);
			DX2VK(DOWN);
			DX2VK(LEFT);
			DX2VK(RIGHT);
			DX2VK(END);
			DX2VK(NEXT);
			DX2VK(INSERT);
			DX2VK(DELETE);

			case DIK_NUMPADENTER:
				vkCode = VK_SEPARATOR;
				break;
			default:
				vkCode = NOKEY;
		}
	}

	return vkCode;
}

static bool _isKeyPressed(UINT keyCode)
{
	if (keyCode < 255)	//use IsKeyPressed
	{
		keyCode = _dx2vk(keyCode);
		if (!(keyCode == NOKEY))		return (GetAsyncKeyState(keyCode) & 0x8000) ? true : false;
	}
	else	//use IsKeyPressed2
	{
		//code below recognizes 255 and 256 for LMB - intentional?
		if (keyCode % 256 == 255 && keyCode < 2048)	keyCode = 255 + (keyCode + 1) / 256;
		if (keyCode < kMaxMacros)	return DI_data.LastBytes[keyCode] ? true : false;
	}

	return false;
}

bool Cmd_IsKeyPressed3_Execute(COMMAND_ARGS)
{
	*result = 0;
	UINT keyCode = NOKEY;
	if (!ExtractArgs(EXTRACT_ARGS, &keyCode)) return true;
	if (_isKeyPressed(keyCode))	*result = 1;
	return true;
}
#endif
