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

//OTRAS CONSTANTES
const int MAX_TOTEMS = 5;
const int MAX_PIEDRA_DEL_CASTIGO = 10;
const int MAX_ANTORCHAS = 5;
const int MAX_HECHIZO_REVELADOR = 5;
const int MAX_VIDAS = 5;

//ESTADOS JUEGO
const int GANO = 1;
const int PERDIO = -1;
const int SIGUE_JUGANDO = 0;

// INPUTS
const char ARRIBA = 'W';
const char ABAJO = 'S';
const char DERECHA = 'D';
const char IZQUIERDA = 'A';
const char HECHIZO_REVELADOR = 'H';
const char ANTORCHA_MAGICA = 'L';

//MOSTRAR JUEGO
const char PERSONAJE = 'H';
const char PERGAMINO = 'P';
const char PARED = '#';
const char TOTEM = 'T';
const char PIEDRA_DEL_CASTIGO = 'R';
const char CAMINO = '.';
const char CATAPULTA = 'F';
const char ALTAR = 'A';
const char RUNA = 'U';
const char VACIO = ' ';


/*
 *  Pre: Previamente debe de estar inicializado el vector de camino, ya que el pergamino tendrá alguna posición aleatoria del mismo.
 *  Post: Cambia de posición al pergamino   
*/
void pos_pergamino(juego_t *juego){

    int tope_camino = juego->niveles[juego->nivel_actual - 1].tope_camino;
    int n_random = (rand() % tope_camino - 2) + 1;

    juego->niveles[juego->nivel_actual - 1].pergamino.fil = juego->niveles[juego->nivel_actual - 1].camino[n_random].fil;
    juego->niveles[juego->nivel_actual - 1].pergamino.col = juego->niveles[juego->nivel_actual - 1].camino[n_random].col;

}
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son CAMINO
*/
bool es_camino(juego_t juego, coordenada_t posicion){

    int tope = juego.niveles[juego.nivel_actual-1].tope_camino;
    bool es_camino = false;

    for(int i = 0;i<tope;i++){
        if(posicion.fil == juego.niveles[juego.nivel_actual - 1].camino[i].fil && posicion.col == juego.niveles[juego.nivel_actual - 1].camino[i].col){
            es_camino = true;
        }    
    }
    return es_camino;
}
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son PARED
*/
bool es_pared(juego_t juego, coordenada_t posicion){

    int tope = juego.niveles[juego.nivel_actual-1].tope_paredes;
    bool pared = false;

    for(int i = 0;i<tope;i++){
        if(posicion.fil == juego.niveles[juego.nivel_actual - 1].paredes[i].fil && posicion.col == juego.niveles[juego.nivel_actual - 1].paredes[i].col){
            pared = true;
        } 
    } 
    return pared;
}
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son TOTEM
*/
bool es_totem(juego_t juego, coordenada_t posicion){

    int tope = juego.niveles[juego.nivel_actual-1].tope_herramientas;
    bool totem = false;

    for(int i = 0;i<tope;i++){
        if(juego.niveles[juego.nivel_actual-1].herramientas[i].tipo == 'T' && posicion.fil == juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.fil && posicion.col == juego.niveles[juego.nivel_actual - 1].herramientas[i].posicion.col){
            totem = true;
        }    
    }
    return totem;
}
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son PIEDRA DEL CASTIGO
*/  
bool es_piedra(juego_t juego, coordenada_t posicion){

    int tope = juego.niveles[juego.nivel_actual-1].tope_obstaculos;
    bool es_piedra = false;

    for(int i = 0;i<tope;i++){
        if(juego.niveles[juego.nivel_actual-1].obstaculos[i].tipo == 'R' && posicion.fil == juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.fil && posicion.col == juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.col){
            es_piedra = true;
        }
    }
    return es_piedra;
    
} 
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas estan dentro del campo permitido [MAX_FILAS][MAX_COLUMNAS]
*/   
bool no_es_afuera(coordenada_t posicion){

    if(posicion.fil >= 0 && posicion.fil < MAX_FILAS && posicion.col >= 0 && posicion.col < MAX_COLUMNAS){
        return true;
    }    
    return false;
} 
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son PERGAMINO
*/   
bool es_pergamino(juego_t juego, coordenada_t posicion){
    
    if(juego.homero.recolecto_pergamino == true) return false;
    
    bool es_pergamino = false;

    if(posicion.fil == juego.niveles[juego.nivel_actual - 1].pergamino.fil && posicion.col == juego.niveles[juego.nivel_actual - 1].pergamino.col){
        es_pergamino = true;
    }
    return es_pergamino;
}
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son RUNA
*/
bool es_runa(juego_t juego, coordenada_t posicion){

    bool es_runa = false;

    if(posicion.fil == juego.niveles[juego.nivel_actual - 1].camino[0].fil && posicion.col == juego.niveles[juego.nivel_actual - 1].camino[0].col){
        es_runa = true;
    }
    return es_runa;
}
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son del ALTAR
*/
bool es_altar(juego_t juego, coordenada_t posicion){

    int tope = juego.niveles[juego.nivel_actual - 1].tope_camino -1;
    bool es_altar = false;

    if(posicion.fil == juego.niveles[juego.nivel_actual - 1].camino[tope].fil && posicion.col == juego.niveles[juego.nivel_actual - 1].camino[tope].col){
        es_altar = true;
    }
    return es_altar;
}
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son del PERSONAJE
*/
bool es_personaje(personaje_t homero, coordenada_t posicion){

    bool es_personaje = false;

    if(posicion.fil == homero.posicion.fil && posicion.col == homero.posicion.col){
        es_personaje = true;
    }
    return es_personaje;
}



/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son de la CATAPULTA
*/
bool es_catapulta(juego_t juego, coordenada_t posicion){

    int tope = juego.niveles[juego.nivel_actual-1].tope_obstaculos;
    bool validado = false;

    for(int i = 0; i < tope; i++){
        if(juego.niveles[juego.nivel_actual - 1].obstaculos[i].tipo == 'F' && posicion.fil == juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.fil && posicion.col == juego.niveles[juego.nivel_actual - 1].obstaculos[i].posicion.col){
            validado = true;
        }    
    }
    return validado;
}
/*
 *  Pre: El juego debe estar inicializado y juego.nivel_actual debe ser un valor válido (entre 1 y MAX_NIVELES). 
 *  La posicion ingresada debe tener coordenadas dentro de los límites 
 *  del mapa (filas entre 0 y MAX_FILAS - 1, columnas entre 0 y MAX_COLUMNAS - 1).
 *  Post: Devuelve true si las coordenadas son VACIO
*/
bool es_vacio(juego_t juego, coordenada_t posicion){

    bool es_vacio = false;

    if(!es_camino(juego, posicion) && !es_pared(juego, posicion) && !es_piedra(juego, posicion) && !es_totem(juego, posicion) && !es_catapulta(juego, posicion)){
        es_vacio = true;
    }
    return es_vacio;    
}


/*
 *  Pre: Recibe un indice para determinar en que nivel se inicializa el PERGAMINO, previamente estará
 *  inicializado la varable de nivel para enmarcar en cual se querrá inicializar, para asignarle una posición. 
 *  Post: Inicializa el PERGAMINO
*/
void inicializar_pergamino(juego_t *juego, int nivel){

    int tope_camino = juego->niveles[nivel].tope_camino;
    int n_random = (rand() % (tope_camino - 2)) + 1;

    juego->niveles[nivel].pergamino.fil = juego->niveles[nivel].camino[n_random].fil;
    juego->niveles[nivel].pergamino.col = juego->niveles[nivel].camino[n_random].col;
}

/*
 * Pre: El puntero posicion apuntará a un espacio 
 * de memoria válido de tipo coordenada_t.
 * Las constantes MAX_COLUMNAS y MAX_FILAS deben estar definidas y ser mayores a 0.
 * Se asumirá que la semilla de números aleatorios (srand) ya fue inicializada.
 *
 * Post: Los campos 'col' y 'fil' de la estructura apuntada por 'posicion' 
 * serán modificados.
 * posicion->col tendrá un valor en el rango [0, MAX_COLUMNAS - 1].
 * posicion->fil tendrá un valor en el rango [0, MAX_FILAS - 1].
 */
void numeros_aleatorios(coordenada_t *posicion){

    posicion->col = rand() % MAX_COLUMNAS;
    posicion->fil = rand() % MAX_FILAS;
}

/*
 *  Pre: Recibe un indice para determinar en que nivel se inicializa el TOTEM, previamente estará
 *  inicializado la varable de nivel para enmarcar en cual se querrá inicializar, para asignarle una posición. 
 *  Post: Inicializa el TOTEM
*/
void inicializar_herramienta_totem(juego_t *juego, int numero_nivel){

    for(int i= 0; i<MAX_TOTEMS;i++){
        
        int indice = juego->niveles[numero_nivel].tope_herramientas;
        bool validado = false;

        juego->niveles[numero_nivel].herramientas[indice].tipo = TOTEM;

        while(!validado){

            numeros_aleatorios(&juego->niveles[numero_nivel].herramientas[indice].posicion);

            coordenada_t pos_totem = juego->niveles[numero_nivel].herramientas[indice].posicion;
        
            if(no_es_afuera(pos_totem) && !es_runa(*juego, pos_totem) && !es_altar(*juego, pos_totem) && !es_pared(*juego, pos_totem) && !es_pergamino(*juego, pos_totem)){
                validado = true;
            }
        }
        juego->niveles[numero_nivel].tope_herramientas++;
    }
}

/*
 *  Pre: Recibe un indice para determinar en que nivel se inicializa la CATAPULTA, previamente estará
 *  inicializado la varable de nivel para enmarcar en cual se querrá inicializar, para asignarle una posición. 
 *  Post: Inicializa la CATAPULTA
*/
void inicializar_obstaculo_catapulta(juego_t *juego, int numero_nivel){

    bool validado = false;  

    int indice = juego->niveles[numero_nivel].tope_obstaculos;
    
    juego->niveles[numero_nivel].obstaculos[indice].tipo = CATAPULTA;

    while(!validado){
        numeros_aleatorios(&juego->niveles[numero_nivel].obstaculos[indice].posicion);

        coordenada_t pos_catapulta = juego->niveles[numero_nivel].obstaculos[indice].posicion;

        if(no_es_afuera(pos_catapulta) && !es_camino(*juego, pos_catapulta) && !es_pared(*juego, pos_catapulta) && !es_totem(*juego, pos_catapulta)){
            validado = true;
        }
    }
    juego->niveles[numero_nivel].tope_obstaculos++;

}

/*
    Pre: Recibe un indice para determinar en que nivel se inicializa la ROCA
    Post: Inicializo la PIEDRA DEL CASTIGO
*/
void inicializar_obstaculo_piedra(juego_t *juego, int numero_nivel){

    for(int i= 0; i<MAX_PIEDRA_DEL_CASTIGO;i++){
        int indice = juego->niveles[numero_nivel].tope_obstaculos;
        bool validado = false;

        juego->niveles[numero_nivel].obstaculos[indice].tipo = PIEDRA_DEL_CASTIGO;

        while(!validado){
            numeros_aleatorios(&juego->niveles[numero_nivel].obstaculos[indice].posicion);
        
            coordenada_t pos_piedra = juego->niveles[numero_nivel].obstaculos[indice].posicion;

            if(no_es_afuera(pos_piedra) && !es_camino(*juego, pos_piedra) && !es_pared(*juego, pos_piedra) && !es_catapulta(*juego, pos_piedra) && !es_totem(*juego, pos_piedra)){
                validado = true;
            }
        }
    juego->niveles[numero_nivel].tope_obstaculos++;
    }
    
}


/*
    Pre: Recibe un indice para determinar en que nivel se inicializarán los datos del juego
    Post: Carga los datos del nivel asignado
*/
void cargar_datos_nivel(juego_t *juego, int numero_nivel) {

    int nivel = numero_nivel - 1; 

    juego->niveles[nivel].tope_paredes = 0;
    juego->niveles[nivel].tope_camino = 0;
    juego->niveles[nivel].tope_obstaculos = 0;
    juego->niveles[nivel].tope_herramientas = 0;
    
    obtener_mapa(juego->niveles[nivel].paredes, &(juego->niveles[nivel].tope_paredes), juego->niveles[nivel].camino, &(juego->niveles[nivel].tope_camino), numero_nivel);

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

    juego->homero.antorcha_encendida = false;
    juego->homero.hechizos_reveladores = MAX_HECHIZO_REVELADOR;
    juego->homero.vidas_restantes = MAX_VIDAS;
    juego->homero.antorchas = MAX_ANTORCHAS;
    juego->homero.recolecto_pergamino = false;
    juego->tope_niveles = MAX_NIVELES;
    juego->camino_visible = true;

    
    for(int i=0; i<MAX_NIVELES;i++){
        juego->nivel_actual = i+1;
        cargar_datos_nivel(juego, juego->nivel_actual);
    }

    juego->nivel_actual = 1;
    juego->homero.posicion = juego->niveles[0].camino[0];

}

/* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego` y el nivel actual del juego tiene que ser 1 o 2.
 * Post condiciones: Actualizará el nivel actual el juego y el personaje para comenzar el siguiente nivel.
 */
void cambiar_nivel(juego_t* juego){
    if(juego->nivel_actual != MAX_NIVELES) juego->nivel_actual++;
    
        int nivel = juego->nivel_actual - 1;
        
        juego->homero.antorchas = MAX_ANTORCHAS; 
        juego->homero.recolecto_pergamino = false;
        
        juego->homero.posicion = juego->niveles[nivel].camino[0];
        
        juego->camino_visible = true; 
    
}

/*
 *  Pre: -
 *  Post: Asigna un valor permitido a una variable impacto que es donde impacta la bola de fuego, proveniente de la catapulta.
 *  Si impacta en el camino se eliminará del vector camino en la posición de impacto.
 *  Si el impacto cae donde estaba el pergamino, se le asigna una nueva posición al mismo.
*/
void ejecucion_catapulta(juego_t* juego){

    int tope = juego->niveles[juego->nivel_actual-1].tope_camino;
    bool encontro_posicion = false;
    coordenada_t impacto;

    while(!encontro_posicion){
        
        numeros_aleatorios(&impacto);

        //if(es_pergamino(*juego, impacto)){
        //    pos_pergamino(juego);
        //    encontro_posicion = true;
        //}        
        if(!es_pared(*juego, impacto) && !es_runa(*juego, impacto) && !es_altar(*juego, impacto) && !es_personaje(juego->homero, impacto)){
            encontro_posicion = true;
        }
    }

    for(int i = 0; i < tope; i++){
        if(impacto.col == juego->niveles[juego->nivel_actual - 1].camino[i].col && impacto.fil == juego->niveles[juego->nivel_actual - 1].camino[i].fil){
            for (int j = i; j < tope - 1; j++) {
                juego->niveles[juego->nivel_actual - 1].camino[j] = juego->niveles[juego->nivel_actual - 1].camino[j + 1];
            }
            juego->niveles[juego->nivel_actual - 1].tope_camino--;
        }
    }
}
/*
 *  Pre: -
 *  Post: Otorga una vida extra al personaje, luego de ser "consumido" el TOTEM, el mismo se eliminará del vector "herramientas".
*/
void ejecucion_totem(juego_t *juego){

    int nivel = juego->nivel_actual - 1;
    int tope = juego->niveles[nivel].tope_herramientas;

    for (int i = 0; i < tope; i++) {
        if ((juego->homero.posicion.fil == juego->niveles[nivel].herramientas[i].posicion.fil) && (juego->homero.posicion.col == juego->niveles[nivel].herramientas[i].posicion.col)) {
            
            for (int j = i; j < tope - 1; j++) {
                juego->niveles[nivel].herramientas[j] = juego->niveles[nivel].herramientas[j + 1];
            }
            juego->niveles[nivel].tope_herramientas--;
        }
    }
    juego->homero.vidas_restantes++;
}
/*
 *  Pre: -
 *  Post: Cambia de posición al pergamino, luego se eliminará el mismo del vector obstaculos
*/
void ejecucion_piedra(juego_t *juego) {

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

/*
 * Pre: El personaje (Homero) debe tener una posición actualizada dentro de los límites del mapa.
 * Movimiento debe ser un carácter que represente una acción válida.
 *
 * Post: Analiza la posición actual de Homero y aplica las consecuencias lógicas y dependiendo
 * donde se encuentre realizará las acciones correspondientes.
 */
void analisis_de_posicion(juego_t *juego, char movimiento){

    if(es_runa(*juego, juego->homero.posicion) || movimiento == HECHIZO_REVELADOR){
        if(juego->homero.hechizos_reveladores > 0 || es_runa(*juego, juego->homero.posicion)){ 
            ejecucion_catapulta(juego);
        }
    }

    if(es_runa(*juego, juego->homero.posicion)){
        juego->camino_visible = true;
    }

    if(juego->homero.posicion.fil == juego->niveles[juego->nivel_actual - 1].pergamino.fil && juego->homero.posicion.col == juego->niveles[juego->nivel_actual - 1].pergamino.col){
        if(!juego->homero.recolecto_pergamino) {
                juego->homero.recolecto_pergamino = true;
                juego->camino_visible = true;
            }
    }

    if(es_piedra(*juego, juego->homero.posicion)){
        ejecucion_piedra(juego);
    }

    if(es_totem(*juego, juego->homero.posicion)){
        if(!es_vacio(*juego, juego->homero.posicion)){
            ejecucion_totem(juego);
        }
    }
    
    if(es_vacio(*juego, juego->homero.posicion) && movimiento == HECHIZO_REVELADOR);

    else if(es_vacio(*juego, juego->homero.posicion) && movimiento == ANTORCHA_MAGICA);

    else if(es_vacio(*juego, juego->homero.posicion)){
        juego->homero.vidas_restantes--;
    }
}


/* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego` y la acción
 * debe ser válida.
 * Post condiciones: Realizará la acción recibida por parámetro actualizando el juego.
 */
void realizar_jugada(juego_t *juego, char movimiento){

    juego->camino_visible = false;
    juego->homero.antorcha_encendida = false;
    coordenada_t coords_nuevas = juego->homero.posicion;
    
    if (movimiento == ARRIBA) coords_nuevas.fil--;
    else if (movimiento == ABAJO) coords_nuevas.fil++;
    else if (movimiento == DERECHA) coords_nuevas.col++;
    else if (movimiento == IZQUIERDA) coords_nuevas.col--;

    else if (movimiento == HECHIZO_REVELADOR){
        if(juego->homero.hechizos_reveladores > 0 && !es_runa(*juego, juego->homero.posicion)){
            juego->homero.hechizos_reveladores--;
            juego->camino_visible = true;
        }
    }
    else if (movimiento == ANTORCHA_MAGICA){
        if(juego->homero.antorchas > 0 && !es_runa(*juego, juego->homero.posicion)){
            juego->homero.antorchas--;
            juego->homero.antorcha_encendida = true;
        }
    }

    if (movimiento == ARRIBA || movimiento == ABAJO || movimiento == DERECHA || movimiento == IZQUIERDA) {
        if (no_es_afuera(coords_nuevas) && !es_pared(*juego, coords_nuevas)) {
            juego->homero.posicion.fil = coords_nuevas.fil;
            juego->homero.posicion.col = coords_nuevas.col;
        }
    }

    analisis_de_posicion(juego, movimiento);


}

//pre: -
//post: Muestra por pantalla las vidas, hechizos reveladores, antorchas, pergamino, posición de homero, si esta pisando la runa o no y si tiene el pergamino o no. 
void mostrar_stats(juego_t juego){

    printf("\n---------||---------\nTe quedan %i vidas\n---------||---------\n", juego.homero.vidas_restantes); 

    printf("Te quedan %i hechizos \nreveladores\n---------||---------\n", juego.homero.hechizos_reveladores);
    
    printf("Te quedan %i antorchas\n---------||---------\n", juego.homero.antorchas);
    
    if(juego.homero.recolecto_pergamino == true) printf("Tienes el pergamino en el inventario\n---------||---------\n");
    else printf("No tienes el pergamino\n---------||---------\n");
    
    printf("Posición: (%d;%d)\n---------||---------\n", juego.homero.posicion.col, juego.homero.posicion.fil);
    
    if(es_runa(juego,juego.homero.posicion)) printf("Estas pisando la runa\n---------||---------\n");
    
    printf("\n");
}

/*
 * Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego `.
 * Post condiciones: Imprime el juego por pantalla.
 */
void mostrar_juego(juego_t juego){

    coordenada_t coords;

    for(coords.fil = 0; coords.fil < MAX_FILAS; coords.fil++) {

        for(coords.col = 0; coords.col < MAX_COLUMNAS; coords.col++) {
            
            int dist_man = abs(juego.homero.posicion.fil - coords.fil) + abs(juego.homero.posicion.col - coords.col);

            if(es_personaje(juego.homero, coords)) {
                printf(" %c", PERSONAJE);
            } else if(es_pergamino(juego, coords)) {
                printf(" %c", PERGAMINO);
            } else if(es_piedra(juego, coords)) {
                printf(" %c", PIEDRA_DEL_CASTIGO);
            } else if(es_catapulta(juego,coords)){
                printf(" %c", CATAPULTA);
            } else if(es_totem(juego, coords)) {
                printf(" %c", TOTEM);
            } else if(es_pared( juego, coords)) {
                printf(" %c", PARED);
                
            } else if(juego.camino_visible || (juego.homero.antorcha_encendida && dist_man <= 3)) {
                if(es_runa(juego, coords)) printf(" %c", RUNA);
                else if(es_altar(juego, coords)) printf(" %c", ALTAR);
                else if(es_camino(juego, coords)) printf(" %c", CAMINO);
                else printf(" %c", VACIO);
                
            } else printf(" %c", VACIO);
        }
        printf("\n");
    }
    mostrar_stats(juego);

}



/*
 * 'nivel' tiene todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando el pergamino esté en el altar
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */
int estado_nivel(nivel_t nivel, personaje_t homero){

    if(nivel.camino[nivel.tope_camino -1].col == homero.posicion.col && nivel.camino[nivel.tope_camino -1].fil == homero.posicion.fil && homero.recolecto_pergamino == true){
        return GANO;
    }
    return SIGUE_JUGANDO;
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

    if(estado_nivel(juego.niveles[juego.nivel_actual - 1], juego.homero) == GANO && juego.nivel_actual == MAX_NIVELES){
        return GANO;
        
    }else if (juego.homero.vidas_restantes <= 0){
        return PERDIO;
    }
    return SIGUE_JUGANDO;
}

