// Fill out your copyright notice in the Description page of Project Settings.


#include "SPauseMenuWidget.h"
#include "LevelHUD.h"
#include "GameFramework/PlayerController.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SPauseMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);

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
					.ColorAndOpacity(FColor::Transparent)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
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
					.Padding(ButtonPadding)
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
					.Padding(ButtonPadding)
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
		OwningHUD->RemovePauseMenu();
	}
	return FReply::Handled();
}

FReply SPauseMenuWidget::OnToTitleClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->ReturnToTitle();
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE