// Fill out your copyright notice in the Description page of Project Settings.


#include "SPauseMenuWidget.h"
#include "LevelHUD.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/Layout/SBackgroundBlur.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SPauseMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f);
	// ...image paths
	FString PauseTitleImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/PauseTitle.PNG");
	FName PauseTitleBrushName = FName(*PauseTitleImagePath);
	FString ControllerSchemeImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/ControllerScheme.PNG");
	FName ControllerSchemeBrushName = FName(*ControllerSchemeImagePath);
	FString ResumeImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/Play.PNG");
	FName ResumeBrushName = FName(*ResumeImagePath);
	FString ToTitleImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/Quit.PNG");
	FName ToTitleBrushName = FName(*ToTitleImagePath);

	ChildSlot[
		SNew(SOverlay)
			// ...BLUR BACKGROUND
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBackgroundBlur)
					.BlurStrength(5)
			]
			// ...PAUSE IMAGE
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SImage)
					.Image(new FSlateDynamicImageBrush(
						PauseTitleBrushName,
						FVector2D(1100, 728.75)))
			]
			// ...CONTROL SCHEME
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
					.Image(new FSlateDynamicImageBrush(
						ControllerSchemeBrushName,
						FVector2D(1100, 728.75)))
			]
			// ...VERTICAL BOX
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				// ...VERTICAL BOX
				SNew(SVerticalBox)
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
									.ButtonColorAndOpacity(FColor::Transparent)
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
									.ButtonColorAndOpacity(FColor::Transparent)
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