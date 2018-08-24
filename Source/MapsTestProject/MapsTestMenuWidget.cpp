// Copyright (c) 2018 Nineva Studios

#include "MapsTestMenuWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "UnrealMapsBlueprintLibrary.h"


void UMapsTestMenuWidget::HandleCreateMapButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("UNREALMAPS => UMapsTestMenuWidget::HandleCreateMapButtonClick()"));

	if (IsMapViewExist)
	{
		return;
	}

	MapView = UUnrealMapsBlueprintLibrary::CreateMapsView();

	if (!MapView.GetObject())
	{
		return;
	}

	IsMapViewExist = true;

	auto mavViewArea = WidgetTree->FindWidget(FName("MapViewArea"));
	if (mavViewArea)
	{
		// obtain map view area position and size
		auto geometry = mavViewArea->GetCachedGeometry();

		FVector2D LocalCoordinate(0.0f, 0.0f); FVector2D PixelPosition; FVector2D ViewportPosition;
		USlateBlueprintLibrary::LocalToViewport(GetWorld(), geometry, LocalCoordinate, PixelPosition, ViewportPosition);

		auto size = geometry.GetLocalSize();

		UE_LOG(LogTemp, Warning, TEXT("UNREALMAPS => SHOW MAP x=%f y=%f w=%f h=%f"), ViewportPosition.X, ViewportPosition.Y, size.X, size.Y);

		// show map view
		MapView->Show(ViewportPosition.X, ViewportPosition.Y, size.X, size.Y, InitMapOptions());
	}	
}

void UMapsTestMenuWidget::HandleShowMapButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("UNREALMAPS => UMapsTestMenuWidget::HandleShowMapButtonClick()"));

	if (!MapView.GetObject())
	{
		return;
	}

	MapView->SetVisible(true);
}

void UMapsTestMenuWidget::HandleHideMapButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("UNREALMAPS => UMapsTestMenuWidget::HandleHideMapButtonClick()"));

	if (!MapView.GetObject())
	{
		return;
	}

	MapView->SetVisible(false);
}

void UMapsTestMenuWidget::HandleDismissMapButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("UNREALMAPS => UMapsTestMenuWidget::HandleDismissMapButtonClick()"));

	if (!MapView.GetObject())
	{
		return;
	}

	MapView->Dismiss();

	IsMapViewExist = false;
}

FGoogleMapOptions UMapsTestMenuWidget::InitMapOptions()
{
	FGoogleMapOptions GoogleMapOtions;

	GoogleMapOtions.AmbientEnabled = false;

	// Camera position
	GoogleMapOtions.CameraPosition.Target = FLatLng{ 52.49f, 13.39f };
	GoogleMapOtions.CameraPosition.Tilt = 1.0f;
	GoogleMapOtions.CameraPosition.Zoom = 10.0f;

	// Specifies a FLatLngBounds to constrain the camera target so that when users
	// scroll and pan the map, the camera target does not move outside these bounds
	GoogleMapOtions.LatLngBounds = FLatLngBounds{ FLatLng{ 53.0f, 14.0f } , FLatLng{ 47.0f, 6.0f } };

	GoogleMapOtions.LiteMode = false;

	GoogleMapOtions.MapType = GoogleMapType::Normal;

	GoogleMapOtions.MaxZoomPreference = 16.0f;
	GoogleMapOtions.MinZoomPreference = 1.0f;	

	return GoogleMapOtions;
}
