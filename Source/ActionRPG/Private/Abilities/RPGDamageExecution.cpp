// Copyright Epic Games, Inc. All Rights Reserved.

#include "Abilities/RPGDamageExecution.h"
#include "Abilities/RPGAttributeSet.h"
#include "AbilitySystemComponent.h"

struct RPGDamageStatics
{
	/**
	 * 捕捉声明宏会向UE4编辑器注册信息，使Gameplay效果可以使用项目中的执行。
	 * 对于每个捕捉到的属性，当前活动临时修饰符列表是与其Gameplay标记一起被捕捉的。
	 */
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	RPGDamageStatics()
	{
		// Capture the Target's DefensePower attribute. Do not snapshot it, because we want to use the health value at the moment we apply the execution.
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DefensePower, Target, false);

		// Capture the Source's AttackPower. We do want to snapshot this at the moment we create the GameplayEffectSpec that will execute the damage.
		// (imagine we fire a projectile: we create the GE Spec when the projectile is fired. When it hits the target, we want to use the AttackPower at the moment
		// the projectile was launched, not when it hits).
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, AttackPower, Source, true);

		// Also capture the source's raw Damage, which is normally passed in directly via the execution
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, Damage, Source, true);
	}
};

static const RPGDamageStatics& DamageStatics()
{
	static RPGDamageStatics DmgStatics;
	return DmgStatics;
}

URPGDamageExecution::URPGDamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().DefensePowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().AttackPowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void URPGDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// --------------------------------------
	//	Damage Done = Damage * AttackPower / DefensePower
	//	If DefensePower is 0, it is treated as 1.0
	// --------------------------------------

	float DefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DefensePowerDef, EvaluationParameters, DefensePower);
	if (DefensePower == 0.0f)
	{
		DefensePower = 1.0f;
	}

	float AttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackPowerDef, EvaluationParameters, AttackPower);

	float Damage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage);

	float DamageDone = Damage * AttackPower / DefensePower;
	if (DamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, DamageDone));
	}
}