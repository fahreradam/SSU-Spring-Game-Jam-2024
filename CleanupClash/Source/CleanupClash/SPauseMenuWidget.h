// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class SPauseMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPauseMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ALevelHUD>, OwningHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnResumeClicked() const;
	FReply OnToTitleClicked() const;

	TWeakObjectPtr<class ALevelHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
