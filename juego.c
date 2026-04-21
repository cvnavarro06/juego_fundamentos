#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "ascension_magios.h"
#include "utiles.h"

//VECTOR DE INPUTS
char VECTOR_INPUTS[6] = {'w', 's', 'd', 'a', 'h', 'l'};
int VECTOR_INPUTS_TOPE = 6;



//Pre: Recibe el input del usuario
//Post: Devuelvo true si pertenece al vector de inputs, false si no.
bool es_movimiento_valido(char input){
    bool validado = false;
    for(int i = 0; i < VECTOR_INPUTS_TOPE; i++){
        if(input == VECTOR_INPUTS[i]){
            validado = true;
        }
    }
    return validado;
}





int main() {

    srand((unsigned)time(NULL));
    bool juego_terminado = false;
    juego_t juego;
    
    printf("Prueba\n");
    printf("Prueba2\n");
    inicializar_juego(&juego);
    printf("Prueba3\n");
    
    
    while(!juego_terminado){
        system("clear");
        mostrar_juego(juego);
        
        char movimiento;
        bool validar_tecla = false;
        while(!validar_tecla){
        printf("Ingrese un movimiento (W/A/S/D para moverse, H para hechizo revelador, L para antorcha mágica): ");
        scanf(" %c", &movimiento);
            if(es_movimiento_valido(movimiento)){    
            validar_tecla = true;
            }
    }
    realizar_jugada(&juego, movimiento);


    //Evaluo el estado del nivel.    
    if(estado_nivel(juego.niveles[juego.nivel_actual - 1], juego.homero) == 1){
        if (juego.nivel_actual <= 3){
            cambiar_nivel(&juego);
            if(estado_juego(juego) == 1){
                printf("¡Has ganado! El juego ha terminado.\n");
                juego_terminado = true;
            }else if(estado_juego(juego) == -1){
                printf("Has perdido el juego :(");
                juego_terminado = true;
            }
        }   
    }
    //estado_juego
    
    

    }
   
    return 0;
}
