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
 * 它用于能力系统，具体请参阅ARPG的Gameplay能力中描述的能力系统。
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
	 * # const函数
	 * 在设计类的时候，一个原则就是对于不改变数据成员的成员函数都要在后面加 const，
	 * 而对于改变数据成员的成员函数不能加 const。所以 const 关键字对成员函数的行为作了更加明确的限定：
	 *（1）有 const 修饰的成员函数（指 const 放在函数参数表的后面，而不是在函数前面或者参数表内），
	 * 只能读取数据成员，不能改变数据成员；没有 const 修饰的成员函数，对数据成员则是可读可写的。
	 *（2）除此之外，在类的成员函数后面加 const 还有什么好处呢？
	 * 那就是常量（即 const）对象可以调用 const 成员函数，而不能调用非const修饰的函数。
	 */
	int32 GetDefaultAbilityLevel() const;

	/** Version of function in AbilitySystemGlobals that returns correct type */
	static URPGAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

};