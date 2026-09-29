// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
    if (!CellActor)
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;




    for (int32 Row = 0; Row < Rows; ++Row)
    {
        TArray<ACell*> RowCells;

        for (int32 Column = 0; Column < Columns; ++Column)
        {
            ACell* NewCell = GetWorld()->SpawnActor<ACell>(
                CellActor,
                GetActorLocation() + FVector(Row * 100.0f, 0.0f, Column * 100.0f),
                FRotator::ZeroRotator,
                SpawnParams
            );

            if (!NewCell)
            {
                continue;
            }

            NewCell->AttachToActor(
                this,
                FAttachmentTransformRules::KeepWorldTransform
            );

            RowCells.Add(NewCell);
        }

        Cells.Add(RowCells);
    }

}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

