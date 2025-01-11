// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GroundMaterialComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UGroundMaterialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGroundMaterialComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void WriteToRenderTarget();
	void TransformToTexture(FVector2D Size, FVector2D& ReturnValue, FVector2D& ReturnValue2);
	
	UPROPERTY(EditAnywhere)
	float OutlineDraw = 1.0f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextureRenderTarget2D> RTDraw;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> RenderMaterial;
};
