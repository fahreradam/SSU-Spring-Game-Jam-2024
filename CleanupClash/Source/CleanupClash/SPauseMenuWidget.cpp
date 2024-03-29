// Fill out your copyright notice in the Description page of Project Settings.


#include "SPauseMenuWidget.h"
#include "MainHUD.h"
#include "GameFramework/PlayerController.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SPauseMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FText PauseText = LOCTEXT("PauseText", "Pause");
	const FText ResumeText = LOCTEXT("ResumeGame", "Resume");
	const FText ToTitleText = LOCTEXT("ToTitleOption", "To Title");

	ChildSlot[
		SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
					.ColorAndOpacity(FColor::Black)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				// ...VERTICAL BOX
				SNew(SVerticalBox)
					// ...PAUSE TEXT
					+ SVerticalBox::Slot()
					[
						SNew(STextBlock)
							.Text(PauseText)
							.Justification(ETextJustify::Center)
					]
					// ...RESUME BUTTON
					+ SVerticalBox::Slot()
					[
						SNew(SButton)
							.OnClicked(this, &SPauseMenuWidget::OnResumeClicked)
							[
								SNew(STextBlock)
									.Text(ResumeText)
									.Justification(ETextJustify::Center)
							]
					]
					// ...TO TITLE BUTTON
					+ SVerticalBox::Slot()
					[
						SNew(SButton)
							.OnClicked(this, &SPauseMenuWidget::OnToTitleClicked)
							[
								SNew(STextBlock)
									.Text(ToTitleText)
									.Justification(ETextJustify::Center)
							]
					]
			]
	];
}

FReply SPauseMenuWidget::OnResumeClicked() const
{
	if (OwningHUD.IsValid())
	{
		// ...logic for resuming the game
	}
	return FReply::Handled();
}

FReply SPauseMenuWidget::OnToTitleClicked() const
{
	if (OwningHUD.IsValid())
	{
		// ...logic for returning to the title screen
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE