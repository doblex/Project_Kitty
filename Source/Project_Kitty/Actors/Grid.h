// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Grid.generated.h"

UCLASS()
class PROJECT_KITTY_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Rows = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Columns = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ACell> CellActor;

private:
	TArray<TArray<ACell*>> Cells;

public:	
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
