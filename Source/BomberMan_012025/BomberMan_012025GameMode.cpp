// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberMan_012025GameMode.h"
#include "BomberMan_012025Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Bloque.h"
#include "BloqueBurbuja.h"
#include "BloqueAcero.h"
#include "BloqueConcreto.h"
#include "BloqueLadrillo.h"
#include "BloqueMadera.h"
#include "BloquePasto.h"
#include "BloqueArena.h"
#include "BloqueGrava.h"
#include "BloqueCobre.h"
#include "BloqueRoble.h"
#include "BloqueOro.h"
#include "Enemigo.h"
#include "EnemigoTerrestre.h"
#include "EnemigoAcuatico.h"
#include "EnemigoAereo.h"
#include "EnemigoSubterraneo.h"

ABomberMan_012025GameMode::ABomberMan_012025GameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

void ABomberMan_012025GameMode::BeginPlay()
{
    Super::BeginPlay();

    // Recorremos la matriz para generar los bloques
    for (int32 fila = 0; fila < aMapaBloques.Num(); ++fila)
    {
        for (int32 columna = 0; columna < aMapaBloques[fila].Num(); ++columna)
        {
            int32 valor = aMapaBloques[fila][columna];
            // Calculamos la posiciÛn del bloque
            FVector posicionBloque = FVector(
            XInicial + columna * AnchoBloque,
            YInicial + fila * LargoBloque,
            20.0f); // Z queda en 0 (altura del bloque)
            // Llamamos a la funcion para generar un bloque
            SpawnBloque(posicionBloque, valor);
            
        }
    }
    
    AsignarMovimientosAleatorios();
    
}

// Funcion para generar un bloque
void ABomberMan_012025GameMode::SpawnBloque(FVector posicionBloque, int32 tipoBloque)
{
    //ABloque* BloqueGenerado = nullptr;

    ABloque* BloqueGenerado = nullptr;
    // Elegir tipo de bloque basado en el valor
    if (tipoBloque == 10)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueOro>(ABloqueOro::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));

    }else if (tipoBloque == 9)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueRoble>(ABloqueRoble::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));

    }else if (tipoBloque == 8)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueCobre>(ABloqueCobre::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }else if (tipoBloque == 7)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueGrava>(ABloqueGrava::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }else if (tipoBloque == 6)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueArena>(ABloqueArena::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }else if (tipoBloque == 5)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloquePasto>(ABloquePasto::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }else if (tipoBloque == 4)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueAcero>(ABloqueAcero::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }else if (tipoBloque == 3)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueConcreto>(ABloqueConcreto::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }else if (tipoBloque == 2)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueLadrillo>(ABloqueLadrillo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }else if (tipoBloque == 1)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueMadera>(ABloqueMadera::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));

    }
    else if (tipoBloque == 0)
    {
        float probabilidad = FMath::RandRange(0.0f, 1.0f);
        if (probabilidad < 0.1f) // 10% de probabilidad de spawnear
        {
            float probabilidad2 = FMath::RandRange(0.0f, 1.0f);
            if(probabilidad2 < 0.25f)
            AEnemigo* enemigo =GetWorld()->SpawnActor<AEnemigo>(AEnemigoAereo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
            if(probabilidad2 < 0.5f && probabilidad2 > 0.25f)
            AEnemigo* enemigo =GetWorld()->SpawnActor<AEnemigo>(AEnemigoTerrestre::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
            if(probabilidad2 < 0.75f && probabilidad2 > 0.5f)
            AEnemigo* enemigo =GetWorld()->SpawnActor<AEnemigo>(AEnemigoAcuatico::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
            if(probabilidad2 > 0.75f)
            AEnemigo* enemigo =GetWorld()->SpawnActor<AEnemigo>(AEnemigoSubterraneo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));

        }
    }

    // Agregar el bloque al TArray si fue generado
    if (BloqueGenerado)
    {
        FVector EscalaActual = BloqueGenerado->GetActorScale3D();

        // Ajustar el valor de la altura (Z)
        EscalaActual.Z *= 2.0f; // Aumenta la altura 2 veces (puedes cambiar el valor segun desees)
        BloqueGenerado->SetActorScale3D(EscalaActual);
    }

}


void ABomberMan_012025GameMode::AsignarMovimientosAleatorios()
{
    TArray<ABloque*> Ladrillos, Maderas, Aceros, Concretos, Burbujas;

    for (ABloque* Bloque : aBloques)
    {
        if (Bloque->IsA(ABloqueLadrillo::StaticClass())) Ladrillos.Add(Bloque);
        else if (Bloque->IsA(ABloqueMadera::StaticClass())) Maderas.Add(Bloque);
        else if (Bloque->IsA(ABloqueAcero::StaticClass())) Aceros.Add(Bloque);
        else if (Bloque->IsA(ABloqueConcreto::StaticClass())) Concretos.Add(Bloque);
        else if (Bloque->IsA(ABloqueBurbuja::StaticClass())) Burbujas.Add(Bloque);
    }

    auto AsignarMovimiento = [](TArray<ABloque*>& Lista, int Tipo, int DirX, int DirY, int DirZ)
    {
        if (Lista.Num() > 0)
        {
            int i = FMath::RandRange(0, Lista.Num() - 1);
            ABloque* Bloque = Lista[i];
            Bloque->TipoMovimiento = Tipo;
            Bloque->DireccionMovimientoX = DirX;
            Bloque->DireccionMovimientoY = DirY;
            Bloque->DireccionMovimientoZ = DirZ;
            Bloque->bPuedeMoverse = true;
        }
    };

    AsignarMovimiento(Ladrillos, 0, 1, 0, 0);   // X
    AsignarMovimiento(Maderas, 1, 0, 1, 0);     // Y
    AsignarMovimiento(Aceros, 2, 0, 0, 1);      // Z
    AsignarMovimiento(Concretos, 0, -1, 0, 0);  // -X
    AsignarMovimiento(Burbujas, 1, 0, -1, 0);   // -Y
}

/*
 
 
 Gamemode.cpp
 
 
 void ABomberMan_012025GameMode::BeginPlay()
 {
 Super::BeginPlay();
 
 // Crear los bloques según el mapa
 for (int32 fila = 0; fila < aMapaBloques.Num(); ++fila)
 {
 for (int32 columna = 0; columna < aMapaBloques[fila].Num(); ++columna)
 {
 int32 valor = aMapaBloques[fila][columna];
 if (valor != 0)
 {
 FVector posicion = FVector(
 XInicial + columna * AnchoBloque,
 YInicial + fila * LargoBloque,
 20.0f);
 SpawnBloque(posicion, valor);
 }
 }
 }
 
 AsignarMovimientosAleatorios();
 
 }
 
 void ABomberMan_012025GameMode::AsignarMovimientosAleatorios()
 {
 TArray<ABloque*> Ladrillos, Maderas, Aceros, Concretos, Burbujas;
 
 for (ABloque* Bloque : aBloques)
 {
 if (Bloque->IsA(ABloqueLadrillo::StaticClass())) Ladrillos.Add(Bloque);
 else if (Bloque->IsA(ABloqueMadera::StaticClass())) Maderas.Add(Bloque);
 else if (Bloque->IsA(ABloqueAcero::StaticClass())) Aceros.Add(Bloque);
 else if (Bloque->IsA(ABloqueConcreto::StaticClass())) Concretos.Add(Bloque);
 else if (Bloque->IsA(ABloqueBurbuja::StaticClass())) Burbujas.Add(Bloque);
 }
 
 auto AsignarMovimiento = [](TArray<ABloque*>& Lista, int Tipo, int DirX, int DirY, int DirZ)
 {
 if (Lista.Num() > 0)
 {
 int i = FMath::RandRange(0, Lista.Num() - 1);
 ABloque* Bloque = Lista[i];
 Bloque->TipoMovimiento = Tipo;
 Bloque->DireccionMovimientoX = DirX;
 Bloque->DireccionMovimientoY = DirY;
 Bloque->DireccionMovimientoZ = DirZ;
 Bloque->bPuedeMoverse = true;
 }
 };
 
 AsignarMovimiento(Ladrillos, 0, 1, 0, 0);   // X
 AsignarMovimiento(Maderas, 1, 0, 1, 0);     // Y
 AsignarMovimiento(Aceros, 2, 0, 0, 1);      // Z
 AsignarMovimiento(Concretos, 0, -1, 0, 0);  // -X
 AsignarMovimiento(Burbujas, 1, 0, -1, 0);   // -Y
 }
 */
