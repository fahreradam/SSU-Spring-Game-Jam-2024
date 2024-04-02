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

	const FMargin ContentPadding = FMargin(250.f, 50.f);
	const FMargin ButtonPadding = FMargin(10.f);
	
	// ...image paths
	FString MainMenuImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/CleanupClashMainMenuImage.PNG");
	FName MainMenuBrushName = FName(*MainMenuImagePath);
	FString PlayImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/Play.PNG");
	FName PlayBrushName = FName(*PlayImagePath);
	FString QuitImagePath = FPaths::ProjectContentDir() + TEXT("Assets/Images/HudIcons/Quit.PNG");
	FName QuitBrushName = FName(*QuitImagePath);
	// ...screen dimensions
	FVector2D ScreenDimensions = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	// ...where we construct our UI
	ChildSlot[
		SNew(SOverlay) 
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
					.Image(new FSlateDynamicImageBrush(
						MainMenuBrushName,
						FVector2D(ScreenDimensions.X, ScreenDimensions.Y)))
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				// ...VERTICAL BOX
				SNew(SVerticalBox)
					// ...TITLE BUTTONS
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						// ...HORIZONTAL BOX
						SNew(SHorizontalBox)
							// ...PLAY BUTTON
							+ SHorizontalBox::Slot()
							.Padding(ButtonPadding)
							[
								SNew(SButton)
									.ButtonColorAndOpacity(FColor::Transparent)
									.OnClicked(this, &SMainMenuWidget::OnPlayClicked)
									[
										SNew(SImage)
											.Image(new FSlateDynamicImageBrush(
												PlayBrushName,
												FVector2D(200.0f, 200.0f)))
									]
							]
							// ...QUIT BUTTON
							+ SHorizontalBox::Slot()
							.Padding(ButtonPadding)
							[
								SNew(SButton)
									.ButtonColorAndOpacity(FColor::Transparent)
									.OnClicked(this, &SMainMenuWidget::OnQuitClicked)
									[
										SNew(SImage)
											.Image(new FSlateDynamicImageBrush(
												QuitBrushName,
												FVector2D(200.0f, 200.0f)))
									]
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
