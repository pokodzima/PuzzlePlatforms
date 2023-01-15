// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> UserWidgetBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	
	MenuClass = UserWidgetBPClass.Class;
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!MenuClass)
	{
		return;
	}
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);

	if (!Menu)
	{
		return;
	}

	Menu->AddToViewport();
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (UEngine* Engine = GetEngine())
	{
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
	}

	if (UWorld* World = GetWorld())
	{
		World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonMap?listen");
	}
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (UEngine* Engine = GetEngine())
	{
		Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	}

	if (APlayerController* PlayerController = GetFirstLocalPlayerController())
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
