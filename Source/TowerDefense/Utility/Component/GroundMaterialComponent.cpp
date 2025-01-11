// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Component/GroundMaterialComponent.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine/Canvas.h"

// Sets default values for this component's properties
UGroundMaterialComponent::UGroundMaterialComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGroundMaterialComponent::BeginPlay()
{
	Super::BeginPlay();
    //UKismetRenderingLibrary::ClearRenderTarget2D(this, RTDraw);
    WriteToRenderTarget();
	
}


// Called every frame
void UGroundMaterialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGroundMaterialComponent::WriteToRenderTarget()
{
    if (RTDraw == nullptr || RenderMaterial == nullptr)
        return;

    UCanvas* Canvas;
    FVector2D Size;
    FDrawToRenderTargetContext Context;

    // Äµ¹ö½º ÃÊ±âÈ­ ¹× ·»´õ Å¸°Ù ÁØºñ
    UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, RTDraw, Canvas, Size, Context);

    if (Canvas)
    {
        FVector2D ScreenPosition;
        FVector2D ScreenSize;
        TransformToTexture(Size, ScreenPosition, ScreenSize);

        FVector2D CoordinatePosition = FVector2D::ZeroVector;
        FVector2D CoordinateSize(1.0f, 1.0f);
        float Rotation = 0.0f;
        FVector2D PivotPoint(0.5f, 0.5f);

        Canvas->K2_DrawMaterial(RenderMaterial, ScreenPosition, ScreenSize, CoordinatePosition, CoordinateSize, Rotation, PivotPoint);

        UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(GetWorld(), Context);
    }
}

void UGroundMaterialComponent::TransformToTexture(FVector2D Size, FVector2D& ReturnValue, FVector2D& ReturnValue2)
{
    FVector Origin, BoxExtent;
    GetOwner()->GetActorBounds(false, Origin, BoxExtent);
    FVector ActorScale = GetOwner()->GetActorScale();
    float OutlineDrawValue = FMath::Min(BoxExtent.X, BoxExtent.Y) / 10000.0f * Size.X * OutlineDraw;
    //ReturnValue2.X = OutlineDrawValue * ActorScale.X * 2;
   // ReturnValue2.Y = OutlineDrawValue;

    ReturnValue2.X = BoxExtent.X / 10000.0f * Size.X * OutlineDraw;
    ReturnValue2.Y = BoxExtent.Y / 10000.0f * Size.Y * OutlineDraw;

    //ReturnValue = FVector2D((GetOwner()->GetActorLocation() + 10000.0 + GetOwner()->GetActorLocation() / 2.0f) / 20000.0f * Size.X - (OutlineDrawValue / 2.0f));

    //ReturnValue = FVector2D((GetOwner()->GetActorLocation() + 10000.0 ) / 20000.0f * Size.X - (OutlineDrawValue / 2.0f));
    ReturnValue.X = (GetOwner()->GetActorLocation().X + 10000.0) / 20000.0f * Size.X - (ReturnValue2.X / 2.0f);
    ReturnValue.Y = (GetOwner()->GetActorLocation().Y + 10000.0) / 20000.0f * Size.Y - (ReturnValue2.Y / 2.0f);
    return;
}
