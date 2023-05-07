// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnLevel.h"

#include "BaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"


// Sets default values
ASpawnLevel::ASpawnLevel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnLevel::BeginPlay()
{
	Super::BeginPlay();

	SpawnLevel(true);
	SpawnLevel(false);
	SpawnLevel(false);
	SpawnLevel(false);



}

// Called every frame
void ASpawnLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnLevel::SpawnLevel(bool IsFirst)
{
    SpawnLocation = FVector(0.0f, 1000.0f, 0.0f);
    SpawnRotation = FRotator(0, 90, 0);

    if (!IsFirst)
    {
        ABaseLevel* LastLevel = LevelList.Last();
        SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
    }

    static TArray<TSubclassOf<ABaseLevel>> LevelArray = { Level1, Level2, Level3, Level4, Level5, Level6, Level7, Level8, Level9, Level10 };
    int32 RandomIndex = FMath::RandRange(0, LevelArray.Num() - 1);

    if (RandomIndex == LevelArray.Num())
    {
        return;
    }

    ABaseLevel* NewLevel = GetWorld()->SpawnActor<ABaseLevel>(LevelArray[RandomIndex], SpawnLocation, SpawnRotation, SpawnInfo);

    if (NewLevel && NewLevel->GetTrigger())
    {
        NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ASpawnLevel::OnOverlapBegin);

        LevelList.Add(NewLevel);

        if (LevelList.Num() > 5)
        {
            LevelList.RemoveAt(0);
        }
    }
}


void ASpawnLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel(false);
}

