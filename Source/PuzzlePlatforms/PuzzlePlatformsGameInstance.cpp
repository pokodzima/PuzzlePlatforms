// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

void UPuzzlePlatformsGameInstance::Host()
{
	if (UEngine* Engine = GetEngine())
	{
		Engine->AddOnScreenDebugMessage(0,2, FColor::Green, TEXT("Hosting"));
	}
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (UEngine* Engine = GetEngine())
	{
		Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	}
}
