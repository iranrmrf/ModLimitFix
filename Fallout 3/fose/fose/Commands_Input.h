#pragma once

#include "CommandTable.h"
#include "ParamInfos.h"

#define DEFINE_INPUT(name, alias, desc) DEFINE_CMD_ALT(name, alias, desc, 0, 1, kParams_OneInt)

DEFINE_CMD_COND(IsKeyPressed, return if a dx scancode is down or up, 0, kParams_OneInt);
DEFINE_INPUT(TapKey, tk, Fakes a key press for one frame);
DEFINE_INPUT(HoldKey, hk, Fakes a key press indefinately);
DEFINE_INPUT(ReleaseKey, rk, Releases a key held down by HoldKey);
DEFINE_INPUT(DisableKey, dk, Prevents a player from using a key);
DEFINE_INPUT(EnableKey, ek, Reenables a key previously disabled with DisableKey);
DEFINE_CMD_ALT(GetNumKeysPressed, gnkp, Returns how many keyboard keys are currently being held down, 0, 0, 0);
DEFINE_INPUT(GetKeyPress, gkp, Returns the scancode of the nth key which is currently being held down);
DEFINE_CMD_ALT(GetNumMouseButtonsPressed, gnmbp, Returns how many mouse buttons are currently being held down, 0, 0, 0);
DEFINE_INPUT(GetMouseButtonPress, gmbp, Returns the code of the nth mouse button which is currently being held down);

DEFINE_COMMAND(GetControl, Returns the key assigned to a control, 0, 1, kParams_OneInt);
DEFINE_COMMAND(GetAltControl, Returns the mouse button assigned to a control, 0, 1, kParams_OneInt);

DEFINE_INPUT(MenuTapKey, mtk, Fakes a key press for one frame in menu mode);
DEFINE_INPUT(MenuHoldKey, mhk, Fakes a key press indefinately in menu mode);
DEFINE_INPUT(MenuReleaseKey, mrk, 	Releases a key held down by MenuHoldKey);
DEFINE_INPUT(DisableControl, dc, disables the key and button bound to a control);
DEFINE_INPUT(EnableControl, ec, enables the key and button assigned to a control);
DEFINE_INPUT(TapControl, tc, taps the key or mouse button assigned to control);
DEFINE_COMMAND(SetControl, assigns a new keycode to the specified keyboard control, 0, 2, kParams_TwoInts);
DEFINE_COMMAND(SetAltControl, assigns a new mouse button code to the specified mouse control, 0, 2, kParams_TwoInts);
DEFINE_COMMAND(SetIsControl, sets a key as a custom control, 0, 2, kParams_TwoInts);
DEFINE_COMMAND(IsControl, returns 1 if key is a game control or 2 if a custom control, 0, 1, kParams_OneInt);
DEFINE_COMMAND(IsKeyDisabled, returns 1 if the key has been disabled by a script, 0, 1, kParams_OneInt);
DEFINE_COMMAND(IsControlDisabled, returns 1 if the control has been disabled by a script, 0, 1, kParams_OneInt);
DEFINE_CMD_COND(IsControlPressed, returns 1 if the control is pressed, 0, kParams_OneInt);

// not brought forward for FOSE yet
//DEFINE_INPUT(MoveMouseX, mmx, "Fakes a mouse movement n pixels along the x axis");
//DEFINE_INPUT(MoveMouseY, mmy, "Fakes a mouse movement n pixels along the y axis");
//DEFINE_CMD_ALT(SetMouseSpeedX, smsx, "Moves the mouse n pixels per second along the x axis", 0, 1, kParams_OneFloat);
//DEFINE_CMD_ALT(SetMouseSpeedY, smsy, "Moves the mouse n pixels per second along the y axis", 0, 1, kParams_OneFloat);
//DEFINE_CMD_ALT(DisableMouse, dm, "Disables mouse x/y axis movement", 0, 0, 0);
//DEFINE_CMD_ALT(EnableMouse, em, "Enables the mouse after it has been disabled by DisableMouse", 0, 0, 0);
//DEFINE_INPUT(IsKeyPressed3, ikp3, "returns true if key/button pressed, even when disabled");
//DEFINE_INPUT(HammerKey, hmk, "Fakes key presses in alternate frames");
//DEFINE_INPUT(AHammerKey, ahmk, 	"Fakes key presses in alternate frames");
//DEFINE_INPUT(UnhammerKey, uhmk, "Releases a key being hammered by HammerKey or AHammerKey");
// Control commands - not implemented
//DEFINE_INPUT(OnKeyDown, okd, "returns true each time the key is depressed");
//DEFINE_INPUT(OnControlDown, ocd, "returns true each time the key or button assigned to control is depressed");

//DEFINE_COMMAND(GetCursorPos, "returns the x coordinate of the mouse cursor", 0, 1, kParams_Axis);
