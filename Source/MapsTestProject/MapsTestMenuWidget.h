// Copyright (c) 2018 Nineva Studios

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UnrealMapsViewInterface.h"
#include "GoogleMapOptions.h"
#include "MapsTestMenuWidget.generated.h"

UCLASS()
class MAPSTESTPROJECT_API UMapsTestMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="UnrealMaps")
	void HandleCreateMapButtonClick();
	
	UFUNCTION(BlueprintCallable, Category = "UnrealMaps")
	void HandleShowMapButtonClick();

	UFUNCTION(BlueprintCallable, Category = "UnrealMaps")
	void HandleHideMapButtonClick();

	UFUNCTION(BlueprintCallable, Category = "UnrealMaps")
	void HandleDismissMapButtonClick();

private:

	FGoogleMapOptions InitMapOptions();

	TScriptInterface<IUnrealMapsViewInterface> MapView;

	bool IsMapViewExist;
};
