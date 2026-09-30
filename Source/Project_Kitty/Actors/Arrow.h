// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_Kitty/Enums/ArrowDirection.h"
#include "Arrow.generated.h"

UCLASS()
class PROJECT_KITTY_API AArrow : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int _ColumnIndex;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EArrowDirection _Direction;
	
public:
	// Sets default values for this actor's properties
	AArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetColumn(int ColumnIndex);
	void SetDirection(EArrowDirection Direction);
};
