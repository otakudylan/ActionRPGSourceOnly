// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

/** Module interface for this game's loading screens */
class IActionRPGLoadingScreenModule : public IModuleInterface
{
public:
	/** Loads the module so it can be turned on */
	/**
	 * inline函数直接在当前frame展开函数代码，省掉了入栈和出栈的代码，所以会执行速度会快一些。
	 * static是以前C的用法.目的是让该关键字标识的函数只在本地文件可见,同一个程序的其它文件是不可见该函数的.换句话说,就算你其它文件里包含了同名同参数表的函数定义的话,也是不会引起函数重复
定义的错误的.因为static是仅在当前文件可见.
	 */
	static inline IActionRPGLoadingScreenModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IActionRPGLoadingScreenModule>("ActionRPGLoadingScreen");
	}

	/** Kicks off the loading screen for in game loading (not startup) */
	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) = 0;

	/** Stops the loading screen */
	virtual void StopInGameLoadingScreen() = 0;
};
