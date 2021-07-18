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
	 * inline����ֱ���ڵ�ǰframeչ���������룬ʡ������ջ�ͳ�ջ�Ĵ��룬���Ի�ִ���ٶȻ��һЩ��
	 * static����ǰC���÷�.Ŀ�����øùؼ��ֱ�ʶ�ĺ���ֻ�ڱ����ļ��ɼ�,ͬһ������������ļ��ǲ��ɼ��ú�����.���仰˵,�����������ļ��������ͬ��ͬ������ĺ�������Ļ�,Ҳ�ǲ����������ظ�
����Ĵ����.��Ϊstatic�ǽ��ڵ�ǰ�ļ��ɼ�.
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
