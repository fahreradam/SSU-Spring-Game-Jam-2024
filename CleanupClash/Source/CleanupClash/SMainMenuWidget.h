// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */

class SMainMenuWidget : public SCompoundWidget
{
	// GENERATED_BODY()

public:
	// ...a system for passing information to the HUD
	SLATE_BEGIN_ARGS(SMainMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMainHUD>, OwningHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnPlayClicked() const;
	FReply OnQuitClicked() const;

	// ...the HUD that created/stores this widget
	// ...not a reference because its a weak pointer
	TWeakObjectPtr<class AMainHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
