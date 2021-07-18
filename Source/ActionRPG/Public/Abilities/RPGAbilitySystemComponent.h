// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "AbilitySystemComponent.h"
#include "Abilities/RPGAbilityTypes.h"
#include "RPGAbilitySystemComponent.generated.h"

class URPGGameplayAbility;

/**
 * Subclass of ability system component with game-specific data
 * Most games will need to make a game-specific subclass to provide utility functions
 * 
 * ����������ϵͳ�����������ARPG��Gameplay����������������ϵͳ��
 */
UCLASS()
class ACTIONRPG_API URPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Constructors and overrides
	URPGAbilitySystemComponent();

	/** Returns a list of currently active ability instances that match the tags */
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<URPGGameplayAbility*>& ActiveAbilities);

	/** Returns the default level used for ability activations, derived from the character */
	/**
	 * # const����
	 * ��������ʱ��һ��ԭ����Ƕ��ڲ��ı����ݳ�Ա�ĳ�Ա������Ҫ�ں���� const��
	 * �����ڸı����ݳ�Ա�ĳ�Ա�������ܼ� const������ const �ؼ��ֶԳ�Ա��������Ϊ���˸�����ȷ���޶���
	 *��1���� const ���εĳ�Ա������ָ const ���ں���������ĺ��棬�������ں���ǰ����߲������ڣ���
	 * ֻ�ܶ�ȡ���ݳ�Ա�����ܸı����ݳ�Ա��û�� const ���εĳ�Ա�����������ݳ�Ա���ǿɶ���д�ġ�
	 *��2������֮�⣬����ĳ�Ա��������� const ����ʲô�ô��أ�
	 * �Ǿ��ǳ������� const��������Ե��� const ��Ա�����������ܵ��÷�const���εĺ�����
	 */
	int32 GetDefaultAbilityLevel() const;

	/** Version of function in AbilitySystemGlobals that returns correct type */
	static URPGAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

};