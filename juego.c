#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "ascension_magios.h"
#include "utiles.h"





//VECTOR DE INPUTS
#define TECLAS_VALIDAS 10
const char TECLAS_VALIDAS_INPUTS[TECLAS_VALIDAS] = {'W', 'S', 'D', 'A', 'H', 'L'};
const int TECLAS_VALIDAS_INPUTS_TOPE = 6;



//Pre: Recibe el input del usuario
//Post: Devuelvo true si pertenece al vector de inputs, false si no.
bool es_movimiento_valido(char input){
    bool validado = false;
    for(int i = 0; i < TECLAS_VALIDAS_INPUTS_TOPE; i++){
        if(input == TECLAS_VALIDAS_INPUTS[i]){
            validado = true;
        }
    }
    return validado;
}
//pre: -
//post: Muestra el tutorial del juego, explicando las mecánicas básicas y los objetivos a cumplir.
int tutorial(char movimiento, int validacion){

    printf("------------------------------------||------------------------------------\n"
        "Bienvenido a la última prueba de Homero para entrar a los Magios.\n"
        "Dicha prueba consistira en que HOMERO deberá de pasar por 3 niveles diseñados por los magios.\n"
        "HOMERO deberá de llevar un PERGAMINO a altar establecido en cada nivel.\n"
        "------------------------------------||------------------------------------\n"
        "En cada nivel habrá una catapulta\n"
        "¡Ten mucho cuidado! ya que la misma se activa cada vez que utilizas un HECHIZO para ver el camino o si pisas la RUNA\n"
        "Tambíen habrá TOTEMS los cuales le darán 1 vida extra a HOMERO.\n"
        "¿Podrás hacer que HOMERO sea parte de los Magios?\n"
        "------------------------------------||------------------------------------\n"
        "Presiona 'S' para continuar " );
    scanf(" %c", &movimiento);

    if(es_movimiento_valido(movimiento)) {
        validacion++;
    }
    return validacion;
}



//pre: Recibe un carácter que representa el movimiento del usuario
//post: Valida si el movimiento es válido, en caso de no serlo, le pide al usuario que ingrese un movimiento válido
char realizo_jugada(juego_t juego, char movimiento){
    bool validar_tecla = false;
    while(!validar_tecla){
        printf("Ingrese un movimiento (W/A/S/D para moverse, H para hechizo revelador, T para antorcha mágica): ");
        scanf(" %c", &movimiento);
        if(es_movimiento_valido(movimiento)) validar_tecla = true;
    }

    return movimiento;
}

//pre: Recibe el juego y un booleano que indica si el juego ha terminado
//post: Devuelve true si el juego ha terminado, false en caso contrario
bool estado_del_juego(juego_t juego, bool juego_terminado){

    if(estado_juego(juego) == 1){
        system("clear");
        mostrar_juego(juego);
        printf("\n¡Felicidades! Has logrado que homero entre a los magios.\n");
        juego_terminado = true;
    } else if(estado_juego(juego) == -1){
        system("clear");
        mostrar_juego(juego);
        printf("\nHomero ha fallado la prueba, no ha entrado a los Magios.\n");
        juego_terminado = true;
    }
    return juego_terminado;

}


int main() {

    srand((unsigned)time(NULL));
    bool juego_terminado = false;
    int validacion_tutorial = 0;
    juego_t juego;
    inicializar_juego(&juego);
    char movimiento;
    
    
    while(!juego_terminado){

        while(validacion_tutorial == 0) validacion_tutorial = tutorial(movimiento, validacion_tutorial);

        system("clear");

        mostrar_juego(juego);
        
        movimiento = realizo_jugada(juego, movimiento);
        
        realizar_jugada(&juego, movimiento);

        if(estado_nivel(juego.niveles[juego.nivel_actual - 1], juego.homero) == 1){
            cambiar_nivel(&juego);
        }

        juego_terminado = estado_del_juego(juego, juego_terminado);
    }
    return 0;
}
