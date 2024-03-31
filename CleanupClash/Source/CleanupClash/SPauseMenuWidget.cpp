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
	
	FString ResumeImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/Play.PNG");
	FName ResumeBrushName = FName(*ResumeImagePath);
	FString ToTitleImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/Quit.PNG");
	FName ToTitleBrushName = FName(*ToTitleImagePath);

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
					// ...PAUSE BUTTONS
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						// ...HORIZONTAL BOX
						SNew(SHorizontalBox)
						// ...RESUME BUTTON
							+ SHorizontalBox::Slot()
							.Padding(ButtonPadding)
							[
								SNew(SButton)
									.OnClicked(this, &SPauseMenuWidget::OnResumeClicked)
									[
										SNew(SImage)
											.Image(new FSlateDynamicImageBrush(
												ResumeBrushName,
												FVector2D(200.0f, 200.0f)))
									]
							]
							// ...TO TITLE BUTTON
							+ SHorizontalBox::Slot()
							.Padding(ButtonPadding)
							[
								SNew(SButton)
									.OnClicked(this, &SPauseMenuWidget::OnToTitleClicked)
									[
										SNew(SImage)
											.Image(new FSlateDynamicImageBrush(
												ToTitleBrushName,
												FVector2D(200.0f, 200.0f)))
									]
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