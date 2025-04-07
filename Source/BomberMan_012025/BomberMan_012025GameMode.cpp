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
#include <Kismet/GameplayStatics.h>

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

    // Reubicar al personaje existente
    if (aposicionesLibres.Num() > 0) {
        int indiceAleatorio = FMath::RandRange(0, aposicionesLibres.Num() - 1);
        FVector posicionAleatoria = aposicionesLibres[indiceAleatorio];

        // Obtener el personaje existente
        APawn* PersonajeExistente = UGameplayStatics::GetPlayerPawn(this, 0); // Busca el personaje predeterminado
        if (PersonajeExistente) {
            // Mover el personaje a la posición seleccionada
            PersonajeExistente->SetActorLocation(posicionAleatoria);
            UE_LOG(LogTemp, Warning, TEXT("Personaje movido a posición: %s"), *posicionAleatoria.ToString());
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("No se encontró un personaje existente."));
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("No hay posiciones libres para reubicar al personaje."));
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
        // Almacenar la posición sin obstáculos en el TArray

        aposicionesLibres.Add(posicionBloque); // Solo agrega posiciones dentro de los límites
  


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
    // Arrays para almacenar los diferentes tipos de bloques
    TArray<ABloque*> Ladrillos, Maderas, Aceros, Concretos, Pastos, Arenas, Gravas, Cobres, Robles, Oros;

    // Clasificar los bloques según su tipo
    for (ABloque* Bloque : aBloques)
    {
        if (Bloque->IsA(ABloqueLadrillo::StaticClass())) Ladrillos.Add(Bloque);
        else if (Bloque->IsA(ABloqueMadera::StaticClass())) Maderas.Add(Bloque);
        else if (Bloque->IsA(ABloqueAcero::StaticClass())) Aceros.Add(Bloque);
        else if (Bloque->IsA(ABloqueConcreto::StaticClass())) Concretos.Add(Bloque);
        else if (Bloque->IsA(ABloquePasto::StaticClass())) Pastos.Add(Bloque);
        else if (Bloque->IsA(ABloqueArena::StaticClass())) Arenas.Add(Bloque);
        else if (Bloque->IsA(ABloqueGrava::StaticClass())) Gravas.Add(Bloque);
        else if (Bloque->IsA(ABloqueCobre::StaticClass())) Cobres.Add(Bloque);
        else if (Bloque->IsA(ABloqueRoble::StaticClass())) Robles.Add(Bloque);
        else if (Bloque->IsA(ABloqueOro::StaticClass())) Oros.Add(Bloque);
    }

    // Asignar movimientos a todos los bloques de manera general
  auto AsignarMovimiento = [](TArray<ABloque*>& Lista, int Tipo, int DirX, int DirY, int DirZ, float Velocidad = 100.0f)
        {
            for (ABloque* Bloque : Lista)
            {
                Bloque->TipoMovimiento = Tipo;
                Bloque->DireccionMovimientoX = DirX;
                Bloque->DireccionMovimientoY = DirY;
                Bloque->DireccionMovimientoZ = DirZ;
                Bloque->FloatSpeed = Velocidad;
                Bloque->bPuedeMoverse = true;
            }
        };

    AsignarMovimiento(Ladrillos, 0, 1, 0, 0, 80.0f);    // Ladrillo: Eje X, Velocidad 80
    AsignarMovimiento(Maderas, 1, 0, 1, 0, 70.0f);      // Madera: Eje Y, Velocidad 70
    AsignarMovimiento(Aceros, 2, 0, 0, 1, 50.0f);       // Acero: Eje Z, Velocidad 50
    AsignarMovimiento(Concretos, 0, -1, 0, 0, 60.0f);   // Concreto: Eje -X, Velocidad 60
    AsignarMovimiento(Pastos, 1, 0, -1, 0, 120.0f);     // Pasto: Eje -Y, Velocidad 120
    AsignarMovimiento(Arenas, 2, 0, 0, -1, 130.0f);     // Arena: Eje -Z, Velocidad 130
    AsignarMovimiento(Gravas, 0, 1, 1, 0, 75.0f);       // Grava: Diagonal X+Y, Velocidad 75
    AsignarMovimiento(Cobres, 1, 0, 1, 1, 65.0f);       // Cobre: Diagonal Y+Z, Velocidad 65
    AsignarMovimiento(Robles, 2, 1, 0, 1, 85.0f);       // Roble: Diagonal X+Z, Velocidad 85
    AsignarMovimiento(Oros, 0, -1, -1, 0, 100.0f);      // Oro: Diagonal -X-Y, Velocidad 100
   

    // Lógica específica para mover solo 2 bloques
    if (Pastos.Num() >= 2) // Puedes cambiar Ladrillos por otro tipo de bloque
    {
        TArray<ABloque*> BloquesSeleccionados;

        // Mezcla los bloques y selecciona 2
        for (int32 i = 0; i < Pastos.Num(); i++)
        {
            int32 j = FMath::RandRange(0, Pastos.Num() - 1);
            Pastos.Swap(i, j);
        }

        BloquesSeleccionados.Add(Pastos[0]);
        BloquesSeleccionados.Add(Pastos[1]);

        // Asignar movimiento específico para los 2 bloques seleccionados
        for (ABloque* Bloque : BloquesSeleccionados)
        {
            UE_LOG(LogTemp, Warning, TEXT("Bloque seleccionado: %s"), *Bloque->GetName());
            

            // Generar direcciones aleatorias (-1, 0, o 1)
           // int DirX = FMath::RandRange(-1, 1); // Movimiento horizontal
           // int DirY = FMath::RandRange(-1, 1); // Movimiento vertical (puedes usar 0 si solo deseas movimiento horizontal o vertical)


            // Definir direcciones de movimiento
            int DirX = 1; // Por ejemplo, moverse horizontalmente hacia la derecha
            int DirY = 0; // Por ejemplo, no moverse verticalmente

            Bloque->DireccionMovimientoX = DirX; // Mover horizontalmente en X
            Bloque->DireccionMovimientoY = DirY; // No moverse en Y
            Bloque->FloatSpeed = 500.0f;         // Velocidad de movimiento
            Bloque->bPuedeMoverse = true;


            // Depuración: Confirma las propiedades asignadas
            UE_LOG(LogTemp, Warning, TEXT("Dirección de movimiento asignada: X=%d, Y=%d, Velocidad=%f"),
                Bloque->DireccionMovimientoX, Bloque->DireccionMovimientoY, Bloque->FloatSpeed);

        }
    }
}



/*void ABomberMan_012025GameMode::AsignarMovimientosAleatorios()
{
    // Arrays para almacenar los diferentes tipos de bloques
    TArray<ABloque*> Ladrillos, Maderas, Aceros, Concretos, Pastos, Arenas, Gravas, Cobres, Robles, Oros;

    // Clasificar los bloques según su tipo
    for (ABloque* Bloque : aBloques)
    {
        if (Bloque->IsA(ABloqueLadrillo::StaticClass())) Ladrillos.Add(Bloque);
        else if (Bloque->IsA(ABloqueMadera::StaticClass())) Maderas.Add(Bloque);
        else if (Bloque->IsA(ABloqueAcero::StaticClass())) Aceros.Add(Bloque);
        else if (Bloque->IsA(ABloqueConcreto::StaticClass())) Concretos.Add(Bloque);
        else if (Bloque->IsA(ABloquePasto::StaticClass())) Pastos.Add(Bloque);
        else if (Bloque->IsA(ABloqueArena::StaticClass())) Arenas.Add(Bloque);
        else if (Bloque->IsA(ABloqueGrava::StaticClass())) Gravas.Add(Bloque);
        else if (Bloque->IsA(ABloqueCobre::StaticClass())) Cobres.Add(Bloque);
        else if (Bloque->IsA(ABloqueRoble::StaticClass())) Robles.Add(Bloque);
        else if (Bloque->IsA(ABloqueOro::StaticClass())) Oros.Add(Bloque);
    }

    // Función para asignar movimiento a 2 bloques aleatorios de un tipo
    auto AsignarMovimiento = [](TArray<ABloque*>& Lista, int Tipo, int DirX, int DirY, int DirZ, float Velocidad = 100.0f)
        {
            if (Lista.Num() >= 2)
            {
                TArray<ABloque*> BloquesSeleccionados;

                // Mezclar el array para selección aleatoria
                for (int32 i = 0; i < Lista.Num(); i++)
                {
                    int32 j = FMath::RandRange(0, Lista.Num() - 1);
                    if (i != j)
                    {
                        Lista.Swap(i, j);
                    }
                }

                // Seleccionar los primeros 2 bloques después de mezclar
                for (int32 i = 0; i < 2 && i < Lista.Num(); i++)
                {
                    ABloque* Bloque = Lista[i];
                    Bloque->TipoMovimiento = Tipo; // Tipo de movimiento 
                    Bloque->DireccionMovimientoX = DirX; // mover en X
					Bloque->DireccionMovimientoY = DirY; // mover en Y
					Bloque->DireccionMovimientoZ = DirZ; // mover en Z
                    Bloque->FloatSpeed = Velocidad;
                    Bloque->bPuedeMoverse = true;
                }
            }
        };

    // Asignar movimientos específicos para cada tipo de bloque
    AsignarMovimiento(Ladrillos, 0, 1, 0, 0, 80.0f);    // Ladrillo: Eje X, Velocidad 80
    AsignarMovimiento(Maderas, 1, 0, 1, 0, 70.0f);      // Madera: Eje Y, Velocidad 70
    AsignarMovimiento(Aceros, 2, 0, 0, 1, 50.0f);       // Acero: Eje Z, Velocidad 50
    AsignarMovimiento(Concretos, 0, -1, 0, 0, 60.0f);   // Concreto: Eje -X, Velocidad 60
    AsignarMovimiento(Pastos, 1, 0, -1, 0, 120.0f);     // Pasto: Eje -Y, Velocidad 120
    AsignarMovimiento(Arenas, 2, 0, 0, -1, 130.0f);     // Arena: Eje -Z, Velocidad 130
    AsignarMovimiento(Gravas, 0, 1, 1, 0, 75.0f);       // Grava: Diagonal X+Y, Velocidad 75
    AsignarMovimiento(Cobres, 1, 0, 1, 1, 65.0f);       // Cobre: Diagonal Y+Z, Velocidad 65
    AsignarMovimiento(Robles, 2, 1, 0, 1, 85.0f);       // Roble: Diagonal X+Z, Velocidad 85
    AsignarMovimiento(Oros, 0, -1, -1, 0, 100.0f);      // Oro: Diagonal -X-Y, Velocidad 100
}

*/



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
