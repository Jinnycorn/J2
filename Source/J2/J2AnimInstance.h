// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "J2AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class J2_API UJ2AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	float Speed;

    
};
