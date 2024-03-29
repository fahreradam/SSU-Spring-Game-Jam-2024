// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "MainHUD.h"
#include "GameFramework/PlayerController.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	// ...get a reference to the owning hud passed in
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);

	const FText TitleText = LOCTEXT("GameTitle", "Cleanup Clash");
	const FText PlayText = LOCTEXT("PlayGame", "Play");
	const FText QuitText = LOCTEXT("QuitGame", "Quit Game");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	// ...where we construct our UI
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

					// ...TITLE TEXT
					+ SVerticalBox::Slot()
					[
						SNew(STextBlock)
							.Font(TitleTextStyle)
							.Text(TitleText)
							.Justification(ETextJustify::Center)
					]

					// ...PLAY BUTTON
					+ SVerticalBox::Slot()
					.Padding(ButtonPadding)
					[
						SNew(SButton)
							.OnClicked(this, &SMainMenuWidget::OnPlayClicked)
							[
								SNew(STextBlock)
									.Font(ButtonTextStyle)
									.Text(PlayText)
									.Justification(ETextJustify::Center)
							]
					]

					// ...QUIT BUTTON
					+ SVerticalBox::Slot()
					.Padding(ButtonPadding)
					[
						SNew(SButton)
							.OnClicked(this, &SMainMenuWidget::OnQuitClicked)
							[
								SNew(STextBlock)
									.Font(ButtonTextStyle)
									.Text(QuitText)
									.Justification(ETextJustify::Center)
							]
					]
			]
	];
}

FReply SMainMenuWidget::OnPlayClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveMenu(true);
	}
	return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
