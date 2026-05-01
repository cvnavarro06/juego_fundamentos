#include "ascension_magios.h"
#include "utiles.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#define MAX_FILAS 20
#define MAX_COLUMNAS 30
#define MAX_ELEMENTOS 40
#define MAX_PAREDES 600
#define MAX_CAMINO 600
#define MAX_NIVELES 3

const int MAX_TOTEMS = 5;
const int MAX_PIEDRA_DEL_CASTIGO = 10;




// INPUTS
const char ARRIBA = 'W';
const char ABAJO = 'S';
const char DERECHA = 'D';
const char IZQUIERDA = 'A';
const char HECHIZO_REVELADOR = 'H';
const char ANTORCHA_MAGICA = 'L';
const char VER = 'V';
const char MAS_VIDA = 'M';
const char SIG_NIVEL = 'N';


/*
    Pre: -
    Post: Cambia de posición al pergamino
*/
void pos_pergamino(juego_t *juego){
    //Busco un número aleatorio dentro del camino para colocar el pergamino.
    int tope_camino = juego->niveles[juego->nivel_actual - 1].tope_camino;
    int n_random = (rand() % tope_camino - 2) + 1;
    //Resto 2 para evitar que caiga en la posición del altar y sumo uno para evitar que caiga en la posición de inicio.

    juego->niveles[juego->nivel_actual - 1].pergamino.fil = juego->niveles[juego->nivel_actual - 1].camino[n_random].fil;
    juego->niveles[juego->nivel_actual - 1].pergamino.col = juego->niveles[juego->nivel_actual - 1].camino[n_random].col;

}
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son CAMINO
*/
bool es_camino(juego_t *juego, int posicion_fil, int posicion_col){

    int tope = juego->niveles[juego->nivel_actual-1].tope_camino;
    
    bool es_camino = false;
        for(int i = 0;i<tope;i++){
            if(posicion_fil == juego->niveles[juego->nivel_actual - 1].camino[i].fil && posicion_col == juego->niveles[juego->nivel_actual - 1].camino[i].col){
                es_camino = true;
            }    
    }
    return es_camino;
}
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son PARED
*/
bool es_pared(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual-1].tope_paredes;
    
    bool pared = false;
        for(int i = 0;i<tope;i++){
            if(posicion_fil == juego->niveles[juego->nivel_actual - 1].paredes[i].fil && posicion_col == juego->niveles[juego->nivel_actual - 1].paredes[i].col){
                pared = true;
            } 
        } 
    return pared;
}    
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son TOTEM
*/
bool es_totem(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual-1].tope_herramientas;
    
    bool totem = false;
        for(int i = 0;i<tope;i++){
            if(juego->niveles[juego->nivel_actual-1].herramientas[i].tipo == 'T' && posicion_fil == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.fil && posicion_col == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.col){
                totem = true;
            }    
    }
    return totem;
}
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son PIEDRA DEL CASTIGO
*/  
bool es_piedra(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual-1].tope_obstaculos;
    
    bool es_piedra = false;
        for(int i = 0;i<tope;i++){
            if(juego->niveles[juego->nivel_actual-1].obstaculos[i].tipo == 'R' && posicion_fil == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil && posicion_col == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col){
                es_piedra = true;
            }
        }
    return es_piedra;
    
} 
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas estan dentro del campo permitido [20][30]
*/   
bool no_es_afuera(juego_t *juego, int posicion_fil, int posicion_col){
    if(posicion_fil >= 0 && posicion_fil < MAX_FILAS && posicion_col >= 0 && posicion_col < MAX_COLUMNAS){
        return true;
    }    
    return false;
} 
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son PERGAMINO
*/   
bool es_pergamino(juego_t *juego, int posicion_fil, int posicion_col){
    
    if(juego->homero.recolecto_pergamino == true) return false;
    
    bool es_pergamino = false;
    if(posicion_fil == juego->niveles[juego->nivel_actual - 1].pergamino.fil && posicion_col == juego->niveles[juego->nivel_actual - 1].pergamino.col){
        es_pergamino = true;
    }
    return es_pergamino;
}
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son RUNA
*/
bool es_runa(juego_t *juego, int posicion_fil, int posicion_col){
    bool es_runa = false;
    if(posicion_fil == juego->niveles[juego->nivel_actual - 1].camino[0].fil && posicion_col == juego->niveles[juego->nivel_actual - 1].camino[0].col){
        es_runa = true;
    }
    return es_runa;
}
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son ALTAR
*/
bool es_altar(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual - 1].tope_camino -1;
    bool es_altar = false;
    if(posicion_fil == juego->niveles[juego->nivel_actual - 1].camino[tope].fil && posicion_col == juego->niveles[juego->nivel_actual - 1].camino[tope].col){
        es_altar = true;
    }
    return es_altar;
}
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son PERSONAJE
*/
bool es_personaje(juego_t *juego, int posicion_fil, int posicion_col){
    bool es_personaje = false;
    if(posicion_fil == juego->homero.posicion.fil && posicion_col == juego->homero.posicion.col){
        es_personaje = true;
    }
    return es_personaje;
}



/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son CATAPULTA
*/
bool es_catapulta(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual-1].tope_obstaculos;
    bool validado = false;
    for(int i = 0; i < tope; i++){
        if(juego->niveles[juego->nivel_actual - 1].obstaculos[i].tipo == 'F' && posicion_fil == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil && posicion_col == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col){
            validado = true;
        }    
    }
    return validado;
}
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas son VACIO
*/
bool es_vacio(juego_t *juego, int posicion_fil, int posicion_col){
    bool es_vacio = false;
    if(!es_camino(juego, posicion_fil, posicion_col) && !es_pared(juego, posicion_fil, posicion_col) && !es_piedra(juego, posicion_fil, posicion_col) && !es_totem(juego, posicion_fil, posicion_col) && !es_catapulta(juego, posicion_fil, posicion_col)){
        es_vacio = true;
    }
    return es_vacio;
}
/*
    Pre: Recibe valores de coordenadas
    Post: Devuelve true si las coordenadas no son RUNA y ALTAR
*/
bool no_es_runa_ni_altar(juego_t* juego, int posicion_fil, int posicion_col){

    bool no_es_runa_ni_altar = false;
    if(posicion_fil != juego->niveles[juego->nivel_actual - 1].camino[0].fil && posicion_col != juego->niveles[juego->nivel_actual - 1].camino[0].col && posicion_fil != juego->niveles[juego->nivel_actual - 1].camino[juego->niveles[juego->nivel_actual - 1].tope_camino - 1].fil && posicion_col != juego->niveles[juego->nivel_actual - 1].camino[juego->niveles[juego->nivel_actual - 1].tope_camino - 1].col){
        no_es_runa_ni_altar = true;
    }
    return no_es_runa_ni_altar;

}

/*
    Pre: Recibo un nivel
    Post: Inicializa el PERGAMINO
*/
void inicializar_pergamino(juego_t *juego, int nivel){
        int tope_camino = juego->niveles[nivel].tope_camino;
        int n_random = (rand() % (tope_camino - 2)) + 1;
        juego->niveles[nivel].pergamino.fil = juego->niveles[nivel].camino[n_random].fil;
        juego->niveles[nivel].pergamino.col = juego->niveles[nivel].camino[n_random].col;

}


/*
    Pre: Recibo un nivel
    Post: Inicializo el TOTEM
*/
void inicializar_herramienta_totem(juego_t *juego, int numero_nivel){

    for(int i= 0; i<MAX_TOTEMS;i++){
        
        int indice = juego->niveles[numero_nivel].tope_herramientas;
        bool validado = false;

        juego->niveles[numero_nivel].herramientas[indice].tipo = 'T';

        while(!validado){
            juego->niveles[numero_nivel].herramientas[indice].posicion.col = rand() % MAX_COLUMNAS;
            juego->niveles[numero_nivel].herramientas[indice].posicion.fil = rand() % MAX_FILAS;
        
            if(no_es_afuera(juego, juego->niveles[numero_nivel].herramientas[indice].posicion.fil, juego->niveles[numero_nivel].herramientas[indice].posicion.col) == true && no_es_runa_ni_altar(juego, juego->niveles[numero_nivel].herramientas[indice].posicion.fil, juego->niveles[numero_nivel].herramientas[indice].posicion.col) && !es_pared(juego, juego->niveles[numero_nivel].herramientas[indice].posicion.fil, juego->niveles[numero_nivel].herramientas[indice].posicion.col) && !es_pergamino(juego, juego->niveles[numero_nivel].herramientas[indice].posicion.fil, juego->niveles[numero_nivel].herramientas[indice].posicion.col)){
                validado = true;
            }
        }
        juego->niveles[numero_nivel].tope_herramientas++;
    }
}

/*
    Pre: Recibo un nivel
    Post: Inicializo la CATAPULTA
*/
void inicializar_obstaculo_catapulta(juego_t *juego, int numero_nivel){
    bool validado = false;  
    int indice = juego->niveles[numero_nivel].tope_obstaculos;
    
    juego->niveles[numero_nivel].obstaculos[indice].tipo = 'F';

    while(!validado){
        juego->niveles[numero_nivel].obstaculos[indice].posicion.col = rand() % MAX_COLUMNAS;
        juego->niveles[numero_nivel].obstaculos[indice].posicion.fil = rand() % MAX_FILAS;
        
        if(no_es_afuera(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col) == true && !es_camino(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col) && !es_pared(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col) && !es_totem(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col)){
            validado = true;
        }
    }
    juego->niveles[numero_nivel].tope_obstaculos++;

}

/*
    Pre: Recibo un nivel
    Post: Inicializo la PIEDRA DEL CASTIGO
*/
void inicializar_obstaculo_piedra(juego_t *juego, int numero_nivel){
    for(int i= 0; i<MAX_PIEDRA_DEL_CASTIGO;i++){
        
        int indice = juego->niveles[numero_nivel].tope_obstaculos;
        bool validado = false;

        juego->niveles[numero_nivel].obstaculos[indice].tipo = 'R';

        while(!validado){
            juego->niveles[numero_nivel].obstaculos[indice].posicion.col = rand() % MAX_COLUMNAS;
            juego->niveles[numero_nivel].obstaculos[indice].posicion.fil = rand() % MAX_FILAS;
        
            if(no_es_afuera(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col) == true && !es_camino(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col) && !es_pared(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col) && !es_catapulta(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col) && !es_totem(juego, juego->niveles[numero_nivel].obstaculos[indice].posicion.fil, juego->niveles[numero_nivel].obstaculos[indice].posicion.col)){
                validado = true;
            }
        }
    juego->niveles[numero_nivel].tope_obstaculos++;
    }
    
}


/*
    Pre: Recibo un nivel
    Post: Carga los datos del nivel asignado
*/
void cargar_datos_nivel(juego_t* juego, int numero_nivel) {
    int nivel = numero_nivel - 1; 
    juego->niveles[nivel].tope_paredes = 0;
    juego->niveles[nivel].tope_camino = 0;
    juego->niveles[nivel].tope_obstaculos = 0;
    juego->niveles[nivel].tope_herramientas = 0;
    //Inicializo las paredes y el camino del nivel.
    obtener_mapa(juego->niveles[nivel].paredes, &(juego->niveles[nivel].tope_paredes), juego->niveles[nivel].camino, &(juego->niveles[nivel].tope_camino), numero_nivel);
    //Inicializo los obstáculos y las herramientas del nivel.

    juego->homero.posicion = juego->niveles[nivel].camino[0];


    inicializar_pergamino(juego, nivel);
    
    inicializar_herramienta_totem(juego, nivel);
    
    inicializar_obstaculo_catapulta(juego, nivel);
    
    inicializar_obstaculo_piedra(juego, nivel);
    
}

/* Pre condiciones: -
 * Post condiciones: Inicializará el juego, cargando toda la información inicial de Homero y de los 3 niveles.
 */
void inicializar_juego(juego_t *juego){
//Valores del personaje

    juego->homero.antorcha_encendida = false;
    juego->homero.hechizos_reveladores = 5;
    juego->homero.vidas_restantes = 5;
    juego->homero.antorchas = 5;
    juego->homero.recolecto_pergamino = false;
    juego->tope_niveles = MAX_NIVELES;
    juego->camino_visible = true;

    juego->nivel_actual = 1;
    cargar_datos_nivel(juego, 1);
    
    juego->nivel_actual = 2;
    cargar_datos_nivel(juego, 2);
    
    juego->nivel_actual = 3;
    cargar_datos_nivel(juego, 3);

    juego->nivel_actual = 1;
    //Inicializo acá la posición de homero, ya que guardaba, en el nivel 1, la pos[0] del nivel 3
    juego->homero.posicion = juego->niveles[0].camino[0];

}

/* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego` y el nivel actual del juego tiene que ser 1 o 2.
 * Post condiciones: Actualizará el nivel actual el juego y el personaje para comenzar el siguiente nivel.
 */
void cambiar_nivel(juego_t* juego){
    if(juego->nivel_actual != MAX_NIVELES) juego->nivel_actual++;
    
        int nivel = juego->nivel_actual - 1;
        
        juego->homero.antorchas = 5; 
        juego->homero.recolecto_pergamino = false;
        
        juego->homero.posicion = juego->niveles[nivel].camino[0];
        
        juego->camino_visible = true; 
    
}

/*
    Pre: -
    Post: Asigna un valor permitido a una variable impacto que es donde impacta la bola de fuego
*/
void ejecuccion_catapulta(juego_t* juego){
    int tope = juego->niveles[juego->nivel_actual-1].tope_camino;
    bool encontro_posicion = false;
    coordenada_t impacto;
    //Creo esta variable para que no entre en un bucle infinito (medida de seguridad)
    int intentos = 0;
    while(!encontro_posicion && intentos < 500){
        impacto.fil = rand() % MAX_FILAS;
        impacto.col = rand() % MAX_COLUMNAS;

            if(es_pergamino(juego, impacto.fil, impacto.col) == true){
                pos_pergamino(juego);

            }

            if(!es_pared(juego, impacto.fil, impacto.col) && no_es_runa_ni_altar(juego, impacto.fil, impacto.col) &&  impacto.col != juego->homero.posicion.col && impacto.fil != juego->homero.posicion.fil){
                encontro_posicion = true;
            }
            intentos++;
        }
        //Modularizar
        for(int i = 0; i < tope; i++){
            if(impacto.col == juego->niveles[juego->nivel_actual - 1].camino[i].col && impacto.fil == juego->niveles[juego->nivel_actual - 1].camino[i].fil){
                //Elimino la posición del camino donde impactó la catapulta.
                for (int j = i; j < tope - 1; j++) {
                    juego->niveles[juego->nivel_actual - 1].camino[j] = juego->niveles[juego->nivel_actual - 1].camino[j + 1];
                }
                juego->niveles[juego->nivel_actual - 1].tope_camino--;
            }
        }
}
/*
    Pre: Recibe valores de coordenadas
    Post: Otorga una vida extra al personaje
*/
void ejecucion_totem(juego_t *juego, int pos_fil, int pos_col){
    //Modificado (luego ver con el algotrón)
    int nivel = juego->nivel_actual - 1;
    int tope = juego->niveles[juego->nivel_actual].tope_herramientas;

    for (int i = 0; i < tope; i++) {
        if ((juego->homero.posicion.fil == juego->niveles[nivel].herramientas[i].posicion.fil) && (juego->homero.posicion.col == juego->niveles[nivel].herramientas[i].posicion.col)) {
            
            for (int j = i; j < tope -1; j++) {
                juego->niveles[nivel].herramientas[j] = juego->niveles[nivel].herramientas[j + 1];
            }
            juego->niveles[nivel].tope_herramientas--;
        }
     }
    juego->homero.vidas_restantes++;
}
/*
    Pre: -
    Post: Cambia de posición al pergamino
*/
void ejecuccion_piedra(juego_t *juego) {
    int nivel = juego->nivel_actual - 1;
    int tope = juego->niveles[nivel].tope_obstaculos;
    pos_pergamino(juego);
    juego->homero.recolecto_pergamino = false;

    for (int i = 0; i < tope; i++) {
        if ((juego->homero.posicion.fil == juego->niveles[nivel].obstaculos[i].posicion.fil) && (juego->homero.posicion.col == juego->niveles[nivel].obstaculos[i].posicion.col)) {
            
            for (int j = i; j < tope - 1; j++) {
                juego->niveles[nivel].obstaculos[j] = juego->niveles[nivel].obstaculos[j + 1];
            }
            juego->niveles[nivel].tope_obstaculos--;
        }
    }
}

/* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego` y la acción
 * debe ser válida.
 * Post condiciones: Realizará la acción recibida por parámetro actualizando el juego.
 */
void realizar_jugada(juego_t *juego, char movimiento){
    juego->camino_visible = false;
    //La antorcha dura un movimiento
    juego->homero.antorcha_encendida = false;
    int nueva_fil = juego->homero.posicion.fil;
    int nueva_col = juego->homero.posicion.col;

    if (movimiento == ARRIBA) nueva_fil--;
    else if (movimiento == ABAJO) nueva_fil++;
    else if (movimiento == DERECHA) nueva_col++;
    else if (movimiento == IZQUIERDA) nueva_col--;

    else if (movimiento == HECHIZO_REVELADOR){
        if(juego->homero.hechizos_reveladores > 0 && !es_runa(juego, juego->homero.posicion.fil,juego->homero.posicion.col)){
            juego->homero.hechizos_reveladores--;
            juego->camino_visible = true;
        }
    }
    else if (movimiento == ANTORCHA_MAGICA){
        if(juego->homero.antorchas > 0 && !es_runa(juego, juego->homero.posicion.fil,juego->homero.posicion.col)){
            juego->homero.antorchas--;
            juego->homero.antorcha_encendida = true;
        }
    }

    //CHEATS
    else if (movimiento == VER){
        juego->camino_visible = true;
    } else if(movimiento == MAS_VIDA){
        juego->homero.vidas_restantes++;
    } else if(movimiento == SIG_NIVEL){
        juego->nivel_actual++;
    }

    //Filtros
    if (movimiento == ARRIBA || movimiento == ABAJO || movimiento == DERECHA || movimiento == IZQUIERDA) {
        if (no_es_afuera(juego, nueva_fil, nueva_col) && !es_pared(juego, nueva_fil, nueva_col)) {
            juego->homero.posicion.fil = nueva_fil;
            juego->homero.posicion.col = nueva_col;
        }
    }

    //Catapulta
    if(es_runa(juego, juego->homero.posicion.fil, juego->homero.posicion.col) || movimiento == HECHIZO_REVELADOR){
        if(juego->homero.hechizos_reveladores > 0 || es_runa(juego, juego->homero.posicion.fil, juego->homero.posicion.col)){ 
            ejecuccion_catapulta(juego);

        }
    } 
    //Runa
    if(es_runa(juego, juego->homero.posicion.fil, juego->homero.posicion.col)){
        juego->camino_visible = true;
    }
    //Recoleccón del pergamino
    if(juego->homero.posicion.fil == juego->niveles[juego->nivel_actual - 1].pergamino.fil && juego->homero.posicion.col == juego->niveles[juego->nivel_actual - 1].pergamino.col){
        if(!juego->homero.recolecto_pergamino) {
                juego->homero.recolecto_pergamino = true;
                juego->camino_visible = true;
            }
    }
    //Piedra
    if(es_piedra(juego, juego->homero.posicion.fil, juego->homero.posicion.col)){
        ejecuccion_piedra(juego);
    }
    //Totem
    if(es_totem(juego, juego->homero.posicion.fil, juego->homero.posicion.col)){
        ejecucion_totem(juego, juego->homero.posicion.fil, juego->homero.posicion.col);
        if(es_vacio(juego, juego->homero.posicion.fil, juego->homero.posicion.col)){
            juego->homero.vidas_restantes = juego->homero.vidas_restantes; 
        }
    }
    //No resto vida si esta en vacio | 'H' y 'L'
    if(es_vacio(juego, juego->homero.posicion.fil, juego->homero.posicion.col) && movimiento == HECHIZO_REVELADOR){
        if(juego->homero.hechizos_reveladores > 0 && !es_runa(juego, juego->homero.posicion.fil,juego->homero.posicion.col)){
                juego->homero.hechizos_reveladores--;
                juego->camino_visible = true;
            }
    }
    else if(es_vacio(juego, juego->homero.posicion.fil, juego->homero.posicion.col) && movimiento == ANTORCHA_MAGICA){
        if(juego->homero.antorchas > 0 && !es_runa(juego, juego->homero.posicion.fil,juego->homero.posicion.col)){
                juego->homero.antorchas--;
                juego->homero.antorcha_encendida = true;
        }
    }
    //Vacio
    else if(es_vacio(juego, juego->homero.posicion.fil, juego->homero.posicion.col)){
        juego->homero.vidas_restantes--;
    }
}
/*
 * Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego `.
 * Post condiciones: Imprime el juego por pantalla.
 */
void mostrar_juego(juego_t juego){
    for(int f = 0; f < MAX_FILAS; f++) {
        for(int c = 0; c < MAX_COLUMNAS; c++) {
            
            int dist_man = abs(juego.homero.posicion.fil - f) + abs(juego.homero.posicion.col - c);

            if(es_personaje(&juego, f, c)) {
                printf("H ");
            } else if(es_pergamino(&juego, f, c)) {
                printf("P ");
            } else if(es_piedra(&juego, f, c)) {
                printf("R ");
            } else if(es_catapulta(&juego,f,c)){
                printf("F ");
            } else if(es_totem(&juego, f, c)) {
                printf("T ");
            } else if(es_pared(&juego, f, c)) {
                printf("# ");
                
            } else if(juego.camino_visible || (juego.homero.antorcha_encendida && dist_man <= 3)) {
                if(es_runa(&juego, f, c)) printf("U ");
                else if(es_altar(&juego, f, c)) printf("A ");
                else if(es_camino(&juego, f, c)) printf(". ");
                else printf("  ");
                
            } else printf("? ");
        }
        printf("\n");
    }
    printf("\n---------||---------\nTe quedan %i vidas\n---------||---------\n", juego.homero.vidas_restantes); 
    printf("Te quedan %i hechizos \nreveladores\n---------||---------\n", juego.homero.hechizos_reveladores);
    printf("Te quedan %i antorchas\n---------||---------\n", juego.homero.antorchas);
    if(juego.homero.recolecto_pergamino == true) printf("Tienes el pergamino en el inventario\n---------||---------\n");
    else printf("No tienes el pergamino\n---------||---------\n");

    printf("Posición: (%d;%d)\n---------||---------\n", juego.homero.posicion.col, juego.homero.posicion.fil);
    if(es_runa(&juego,juego.homero.posicion.fil, juego.homero.posicion.col)) printf("Estas pisando la runa\n---------||---------\n");
    printf("\n");


}



/*
 * 'nivel' tiene todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando el pergamino esté en el altar
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */
int estado_nivel(nivel_t nivel, personaje_t homero){
    //Altar
    if(nivel.camino[nivel.tope_camino -1].col == homero.posicion.col && nivel.camino[nivel.tope_camino -1].fil == homero.posicion.fil && homero.recolecto_pergamino == true){
        return 1;
    }
    return 0;
}


/*
 * Pre condiciones: El juego deberá estar inicializado previamente con `inicializar_juego `
 * Post condiciones: Devuelve:
 * --> 1 si es ganado
 * --> -1 si es perdido
 * --> 0 si se sigue jugando
 * El juego se dará por ganado cuando Homero lleve todos los pergaminos a sus altares correspondientes.
 * Se dará por perdido si se le termina la vida antes de llevar todos los pergaminos a sus altares.
 */
int estado_juego(juego_t juego){
    if(estado_nivel(juego.niveles[juego.nivel_actual - 1], juego.homero) == 1 && juego.nivel_actual == 3){
        return 1;
        
    
    }else if (juego.homero.vidas_restantes <= 0){
        return -1;
    }
    return 0;
}

