#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "ascension_magios.h"
#include "utiles.h"



//VECTOR DE INPUTS
char VECTOR_INPUTS[10] = {'W', 'S', 'D', 'A', 'H', 'M', 'V', 'L', 'N'};
int VECTOR_INPUTS_TOPE = 9;



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
    int tutorial = 0;
    inicializar_juego(&juego);
    char movimiento;
    
    
    while(!juego_terminado){

        while(tutorial == 0){
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
            scanf(" %s", &movimiento);
            if(es_movimiento_valido(movimiento)) tutorial++;
        }
        system("clear");
        mostrar_juego(juego);
        
        bool validar_tecla = false;
        while(!validar_tecla){
            printf("Ingrese un movimiento (W/A/S/D para moverse, H para hechizo revelador, T para antorcha mágica): ");
            scanf(" %c", &movimiento);
            if(es_movimiento_valido(movimiento)){    
                validar_tecla = true;
            }
        }
        
        realizar_jugada(&juego, movimiento);

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
        } else {
            
            if(estado_nivel(juego.niveles[juego.nivel_actual - 1], juego.homero) == 1){
                cambiar_nivel(&juego);
            }
        }
    }
    return 0;
}
