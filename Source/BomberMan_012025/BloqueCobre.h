// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "BloqueCobre.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API ABloqueCobre : public ABloque
{
	GENERATED_BODY()
	
public:
	ABloqueCobre();

	//virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

};
