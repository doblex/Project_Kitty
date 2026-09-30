// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Project_Kitty/Enums/ArrowDirection.h"
#include "Arrow.h"

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
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrid::GenerateGrid()
{
    if (!CellActor)
    {
        return;
    }
    
    if (!ArrowCell)
    {
        return;
    }

    EmptyGrid();
    
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    for (int32 Row = 0; Row < Rows; ++Row)
    {
       FCellCol CellRow = FCellCol();

        AArrow* NewDownArrow = GetWorld()->SpawnActor<AArrow>(
            ArrowCell,
            GetActorLocation() + FVector(Row * CellDimension * 100.0f + OffsetDown.X, 0.0f + OffsetDown.Y, -100 * CellDimension + OffsetDown.Z),
            FRotator(-180, 0, 0),
            SpawnParams
            );
        
        NewDownArrow->AttachToActor(
                this,
                FAttachmentTransformRules::KeepWorldTransform
                );
        
        NewDownArrow->SetColumn(Row);
        NewDownArrow->SetDirection(EArrowDirection::Down);
        
        Arrows.Add(NewDownArrow);
        
        for (int32 Column = 0; Column < Columns; ++Column)
        {
            ACell* NewCell = GetWorld()->SpawnActor<ACell>(
                CellActor,
                GetActorLocation() + FVector(Row * CellDimension * 100.0f, 0.0f, Column * CellDimension * 100.0f),
                FRotator::ZeroRotator,
                SpawnParams
            );

            if (!NewCell)
            {
                continue;
            }
            
            NewCell->SetActorScale3D(FVector(CellDimension));

            NewCell->AttachToActor(
                this,
                FAttachmentTransformRules::KeepWorldTransform
            );

            CellRow.ColCells.Add(NewCell);
        }
        
        AArrow* NewUpArrow = GetWorld()->SpawnActor<AArrow>(
            ArrowCell,
            GetActorLocation() + FVector(Row * CellDimension * 100.0f + OffsetUp.X, 0.0f + OffsetUp.Y, Columns * CellDimension * 100 + OffsetUp.Z),
            FRotator::ZeroRotator,
            SpawnParams
            );
        
        NewUpArrow->AttachToActor(
                this,
                FAttachmentTransformRules::KeepWorldTransform
                );
        
        NewUpArrow->SetColumn(Row);
        NewUpArrow->SetDirection(EArrowDirection::Up);
        
        Arrows.Add(NewUpArrow);

        Cells.Add(CellRow);
    }
}

void AGrid::EmptyGrid()
{
    for (int i = Arrows.Num() - 1 ; i >= 0; --i)
    {
        Arrows[i]->Destroy();
    }
    
    for (int i = 0; i < Cells.Num(); ++i)
    {
        for (int j = 0; j < Cells[i].ColCells.Num(); ++j)
        {
            Cells[i].ColCells[j]->Destroy();
        }
    }
}

void AGrid::RotateColumn(int index, EArrowDirection Direction)
{
    if (index < 0 || index >= Columns) return;
    
    TArray<ACell*> ColCells = Cells[index].ColCells;;
    
    if (Direction == EArrowDirection::Down)
    {   
        Algo::Reverse(ColCells);
    }
    
    FVector firstPos = ColCells[0]->GetActorLocation();

    for (int i = 0; i < ColCells.Num() - 1 ; ++i)
    {
        ColCells[i]->SetActorLocation(ColCells[i + 1]->GetActorLocation());
    }
    
    ColCells.Last()->SetActorLocation(firstPos);
    
}

