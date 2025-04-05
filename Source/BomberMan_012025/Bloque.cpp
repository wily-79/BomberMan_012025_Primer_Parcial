// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABloque::ABloque()
{
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MallaBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
    //RootComponent = MeshComp;
    MallaBloque->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaBloque(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

    if (ObjetoMallaBloque.Succeeded())
    {
        MallaBloque->SetStaticMesh(ObjetoMallaBloque.Object);

        MallaBloque->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }

    FloatSpeed = 5.0f;
    RotationSpeed = 3.0f;

    bPuedeMoverse = FMath::RandBool();
    TipoMovimiento = -1;
    FloatSpeed = 100.0f;
    bPuedeMoverse = false;
    DireccionMovimientoX = 1;
    DireccionMovimientoY = 1;
    DireccionMovimientoZ = 1;
}

void ABloque::BeginPlay()
{
    Super::BeginPlay();
    PosicionInicial = GetActorLocation();
}

void ABloque::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bPuedeMoverse)
    {
        FVector Pos = GetActorLocation();
        float Movimiento = FloatSpeed * DeltaTime;
        float RangoMax = 300.0f;

        switch (TipoMovimiento)
        {
        case 0:
            if (FMath::Abs(Pos.X - PosicionInicial.X) >= RangoMax)
                DireccionMovimientoX *= -1;
            Pos.X += DireccionMovimientoX * Movimiento;
            break;

        case 1:
            if (FMath::Abs(Pos.Y - PosicionInicial.Y) >= RangoMax)
                DireccionMovimientoY *= -1;
            Pos.Y += DireccionMovimientoY * Movimiento;
            break;

        case 2:
            if (FMath::Abs(Pos.Z - PosicionInicial.Z) >= RangoMax)
                DireccionMovimientoZ *= -1;
            Pos.Z += DireccionMovimientoZ * Movimiento;
            break;
        }

        SetActorLocation(Pos);
    }
}


/*

 Bloque.cpp
 #include "Bloque.h"
 #include "Components/StaticMeshComponent.h"
 #include "UObject/ConstructorHelpers.h"

 ABloque::ABloque()
 {
     PrimaryActorTick.bCanEverTick = true;

     MallaBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
     RootComponent = MallaBloque;

     static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMalla(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
     if (ObjetoMalla.Succeeded())
     {
         MallaBloque->SetStaticMesh(ObjetoMalla.Object);
     }

     TipoMovimiento = -1;
     FloatSpeed = 100.0f;
     bPuedeMoverse = false;
     DireccionMovimientoX = 1;
     DireccionMovimientoY = 1;
     DireccionMovimientoZ = 1;
 }

 void ABloque::BeginPlay()
 {
     Super::BeginPlay();
     PosicionInicial = GetActorLocation();
 }

 void ABloque::Tick(float DeltaTime)
 {
     Super::Tick(DeltaTime);

     if (bPuedeMoverse)
     {
         FVector Pos = GetActorLocation();
         float Movimiento = FloatSpeed * DeltaTime;
         float RangoMax = 300.0f;

         switch (TipoMovimiento)
         {
         case 0:
             if (FMath::Abs(Pos.X - PosicionInicial.X) >= RangoMax)
                 DireccionMovimientoX *= -1;
             Pos.X += DireccionMovimientoX * Movimiento;
             break;

         case 1:
             if (FMath::Abs(Pos.Y - PosicionInicial.Y) >= RangoMax)
                 DireccionMovimientoY *= -1;
             Pos.Y += DireccionMovimientoY * Movimiento;
             break;

         case 2:
             if (FMath::Abs(Pos.Z - PosicionInicial.Z) >= RangoMax)
                 DireccionMovimientoZ *= -1;
             Pos.Z += DireccionMovimientoZ * Movimiento;
             break;
         }

         SetActorLocation(Pos);
     }
 }

*/

