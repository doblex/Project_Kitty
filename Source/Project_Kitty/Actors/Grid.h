// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "Grid.generated.h"

enum class EArrowDirection : uint8;
class AArrow;


USTRUCT(BlueprintType)
struct FCellCol
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<ACell*> ColCells;
};


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
	int CellDimension = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector OffsetUp = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector OffsetDown = FVector(0.0f, 0.0f, 0.0f);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ACell> CellActor;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AArrow> ArrowCell;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FCellCol> Cells;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<AArrow*> Arrows;

public:	
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void RotateUp();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void GenerateGrid();
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void EmptyGrid();
	
	UFUNCTION(BlueprintCallable)
	void RotateColumn(int index, EArrowDirection Direction);
};
