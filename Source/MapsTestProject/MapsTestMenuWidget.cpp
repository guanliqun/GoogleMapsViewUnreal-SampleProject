// Copyright (c) 2018 Nineva Studios

#include "MapsTestMenuWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "GoogleMapsViewBlueprintLibrary.h"

void UMapsTestMenuWidget::HandleCreateMapButtonClick()
{
	if (IsMapViewExist)
	{
		return;
	}

	MapView = UGoogleMapsViewBlueprintLibrary::CreateMapsView();
	if (!MapView.GetObject()->IsValidLowLevel())
	{
		return;
	}

	// set up map view flag
	IsMapViewExist = true;

	// sign up for map view events
	MapView->GetCallbackProxy()->OnMapReadyDynamicDelegate.AddDynamic(this, &UMapsTestMenuWidget::OnMapViewReady);

	auto MapViewArea = WidgetTree->FindWidget(FName("MapViewArea"));
	if (MapViewArea)
	{
		// obtain map view area position and size
		auto WidgetBounds = GetWidgetBounds(MapViewArea);

		// show map view
		MapView->Show(WidgetBounds.Key.X, WidgetBounds.Key.Y, WidgetBounds.Value.X, WidgetBounds.Value.Y, InitMapOptions());
	}	
}

void UMapsTestMenuWidget::HandleShowMapButtonClick()
{
	if (!MapView.GetObject()->IsValidLowLevel())
	{
		return;
	}

	MapView->SetVisible(true);
}

void UMapsTestMenuWidget::HandleHideMapButtonClick()
{
	if (!MapView.GetObject()->IsValidLowLevel())
	{
		return;
	}

	MapView->SetVisible(false);
}

void UMapsTestMenuWidget::HandleDismissMapButtonClick()
{
	if (!MapView.GetObject()->IsValidLowLevel())
	{
		return;
	}

	MapView->Dismiss();

	// reset map view flag
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

	GoogleMapOtions.MapType = GoogleMapType::GMTNormal;

	GoogleMapOtions.MaxZoomPreference = 16.0f;
	GoogleMapOtions.MinZoomPreference = 1.0f;	

	return GoogleMapOtions;
}

TPair<FVector2D, FVector2D> UMapsTestMenuWidget::GetWidgetBounds(UWidget* widget)
{
	TPair<FVector2D, FVector2D> Bounds;

	auto SizeBoxRoot = WidgetTree->FindWidget(FName("SizeBoxRoot"));
	if (SizeBoxRoot)
	{
		// calculate coefficient to adjust widget position and size for high res screens
		FVector2D NativeScreenSize = UGoogleMapsViewBlueprintLibrary::GetNativeScreenSize();
		FVector2D SizeBoxSize = SizeBoxRoot->GetDesiredSize();

		auto MinScreenDimension = FMath::Min(NativeScreenSize.X, NativeScreenSize.Y);
		auto MinSizeBoxDimension = FMath::Min(SizeBoxSize.X, SizeBoxSize.Y);

		float ScaleCoefficient = MinScreenDimension / MinSizeBoxDimension;

		// obtain widget position and size
		const FGeometry& Geometry = widget->GetCachedGeometry();
		FVector2D LocalSize = Geometry.GetLocalSize();

		FVector2D LocalCoordinate(0.0f, 0.0f);
		FVector2D PixelPosition;
		FVector2D ViewportPosition;

		USlateBlueprintLibrary::LocalToViewport(GetWorld(), Geometry, LocalCoordinate, PixelPosition, ViewportPosition);

		Bounds.Key.X = ViewportPosition.X * ScaleCoefficient;
		Bounds.Key.Y = ViewportPosition.Y * ScaleCoefficient;
		Bounds.Value.X = LocalSize.X * ScaleCoefficient;
		Bounds.Value.Y = LocalSize.Y * ScaleCoefficient;

		UE_LOG(LogTemp, Warning, TEXT("GOOGLEMAPSVIEW => X = %f, Y = %f, W = %f, H = %f"), Bounds.Key.X, Bounds.Key.Y, Bounds.Value.X, Bounds.Value.Y);
	}

	return Bounds;
}

void UMapsTestMenuWidget::OnMapViewReady()
{
	// Check logs to make sure that this callback works
	UE_LOG(LogTemp, Warning, TEXT("GOOGLEMAPSVIEW => MAP VIEW READY CALLBACK"));
}
