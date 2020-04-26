#pragma once

// B0
class EffectSetting : public TESForm
{
public:
	EffectSetting();
	~EffectSetting();

	// bases
	TESModel			model;			// 018
	TESDescription		description;	// 030
	TESFullName			fullName;		// 038
	TESIcon				icon;			// 044

};



class ActiveEffect
{
public:
	ActiveEffect();
	~ActiveEffect();
};

class ValueModifierEffect : public ActiveEffect
{
public:
	ValueModifierEffect();
	~ValueModifierEffect();
};

class AssociatedItemEffect : public ActiveEffect
{
public:
	AssociatedItemEffect();
	~AssociatedItemEffect();
};

class CommandEffect : public ActiveEffect
{
public:
	CommandEffect();
	~CommandEffect();
};

class AbsorbEffect : public ValueModifierEffect
{
public:
	AbsorbEffect();
	~AbsorbEffect();
};

class BoundItemEffect : public AssociatedItemEffect
{
public:
	BoundItemEffect();
	~BoundItemEffect();
};

class CalmEffect : public ValueModifierEffect
{
public:
	CalmEffect();
	~CalmEffect();
};

class ChameleonEffect : public ValueModifierEffect
{
public:
	ChameleonEffect();
	~ChameleonEffect();
};

class CommandCreatureEffect : public CommandEffect
{
public:
	CommandCreatureEffect();
	~CommandCreatureEffect();
};

class CommandHumanoidEffect : public CommandEffect
{
public:
	CommandHumanoidEffect();
	~CommandHumanoidEffect();
};

class ConcussionEffect : public ActiveEffect
{
public:
	ConcussionEffect();
	~ConcussionEffect();
};

class CureEffect : public ActiveEffect
{
public:
	CureEffect();
	~CureEffect();
};

class DarknessEffect : public ValueModifierEffect
{
public:
	DarknessEffect();
	~DarknessEffect();
};

class DemoralizeEffect : public ActiveEffect
{
public:
	DemoralizeEffect();
	~DemoralizeEffect();
};

class DetectLifeEffect : public ValueModifierEffect
{
public:
	DetectLifeEffect();
	~DetectLifeEffect();
};

class DisintegrateArmorEffect : public ActiveEffect
{
public:
	DisintegrateArmorEffect();
	~DisintegrateArmorEffect();
};

class DisintegrateWeaponEffect : public ActiveEffect
{
public:
	DisintegrateWeaponEffect();
	~DisintegrateWeaponEffect();
};

class DispelEffect : public ActiveEffect
{
public:
	DispelEffect();
	~DispelEffect();
};

class FrenzyEffect : public ValueModifierEffect
{
public:
	FrenzyEffect();
	~FrenzyEffect();
};

class InvisibilityEffect : public ValueModifierEffect
{
public:
	InvisibilityEffect();
	~InvisibilityEffect();
};

class LightEffect : public ActiveEffect
{
public:
	LightEffect();
	~LightEffect();
};

class LockEffect : public ActiveEffect
{
public:
	LockEffect();
	~LockEffect();
};

class NightEyeEffect : public ValueModifierEffect
{
public:
	NightEyeEffect();
	~NightEyeEffect();
};

class OpenEffect : public ActiveEffect
{
public:
	OpenEffect();
	~OpenEffect();
};

class ParalysisEffect : public ValueModifierEffect
{
public:
	ParalysisEffect();
	~ParalysisEffect();
};

class ReanimateEffect : public ActiveEffect
{
public:
	ReanimateEffect();
	~ReanimateEffect();
};

class ScriptEffect : public ActiveEffect
{
public:
	ScriptEffect();
	~ScriptEffect();
};

class ShieldEffect : public ValueModifierEffect
{
public:
	ShieldEffect();
	~ShieldEffect();
};

class SummonCreatureEffect : public AssociatedItemEffect
{
public:
	SummonCreatureEffect();
	~SummonCreatureEffect();
};

class SunDamageEffect : public ActiveEffect
{
public:
	SunDamageEffect();
	~SunDamageEffect();
};

class TelekinesisEffect : public ValueModifierEffect
{
public:
	TelekinesisEffect();
	~TelekinesisEffect();
};

class TurnUndeadEffect : public ActiveEffect
{
public:
	TurnUndeadEffect();
	~TurnUndeadEffect();
};

class ValueAndConditionsEffect : public ValueModifierEffect
{
public:
	ValueAndConditionsEffect();
	~ValueAndConditionsEffect();
};

class VampirismEffect :: public ActiveEffect
{
public:
	VampirismEffect();
	~VampirismEffect();
};
