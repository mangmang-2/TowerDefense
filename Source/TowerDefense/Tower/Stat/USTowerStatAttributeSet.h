// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "USTowerStatAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChange);

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUSTowerStatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UUSTowerStatAttributeSet();

	ATTRIBUTE_ACCESSORS(UUSTowerStatAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UUSTowerStatAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UUSTowerStatAttributeSet, Damage);

protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Damage;

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	FOnHealthChange OnHealthChange;
};
