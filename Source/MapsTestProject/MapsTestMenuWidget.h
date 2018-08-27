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

protected:

	UFUNCTION(BlueprintCallable, Category="UnrealMaps")
	void HandleCreateMapButtonClick();
	
	UFUNCTION(BlueprintCallable, Category = "UnrealMaps")
	void HandleShowMapButtonClick();

	UFUNCTION(BlueprintCallable, Category = "UnrealMaps")
	void HandleHideMapButtonClick();

	UFUNCTION(BlueprintCallable, Category = "UnrealMaps")
	void HandleDismissMapButtonClick();

private:

	/**
	* Create dummy map options structure with hardcoded values
	*/
	FGoogleMapOptions InitMapOptions();

	/**
	* Get bounds of specified widget
	* @return - pair of vectors with widget bounds (key - widget position in viewport, value - widget size)
	*/
	TPair<FVector2D, FVector2D> GetWidgetBounds(UWidget* widget);

	/** Reference to map view interface */
	TScriptInterface<IUnrealMapsViewInterface> MapView;

	/** 
	* Flag indicating if there is existing map view (used to allow only one map view in demo level).
	* Can be removed to allow creation of multiple map views.
	*/
	bool IsMapViewExist;

	UFUNCTION()
	void OnMapViewReady();
};
