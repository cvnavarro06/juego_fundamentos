#include "ascension_magios.h"
#include "utiles.h"
#include <stdbool.h>
#include <stdlib.h>


#define MAX_FILAS 20
#define MAX_COLUMNAS 30
#define MAX_ELEMENTOS 40
#define MAX_PAREDES 600
#define MAX_CAMINO 600
#define MAX_NIVELES 3





// INPUTS
const char ARRIBA = 'w';
const char ABAJO = 's';
const char DERECHA = 'd';
const char IZQUIERDA = 'a';
const char HECHIZO_REVELADOR = 'h';
const char ANTORCHA_MAGICA = 'l';

static void pos_pergamino(juego_t *juego){
//Busco un número aleatorio dentro del camino para colocar el pergamino.
    int tope_camino = juego->niveles[juego->nivel_actual - 1].tope_camino;
    int n_random = (rand() % tope_camino - 2) + 1;
    //Resto 2 para evitar que caiga en la posición del altar y sumo uno para evitar que caiga en la posición de inicio.

    juego->niveles[juego->nivel_actual - 1].pergamino.fil = juego->niveles[juego->nivel_actual - 1].camino[n_random].fil;
    juego->niveles[juego->nivel_actual - 1].pergamino.col = juego->niveles[juego->nivel_actual - 1].camino[n_random].col;

}
static void inicializar_obstaculo_piedra(juego_t *juego, int numero_nivel){
    for(int i= 0; i<10;i++){
        juego->niveles[numero_nivel].obstaculos[i].tipo = 'R';
        juego->niveles[numero_nivel].obstaculos[i].posicion.fil = rand() % MAX_FILAS;
        juego->niveles[numero_nivel].obstaculos[i].posicion.col = rand() % MAX_COLUMNAS;
        juego->niveles[numero_nivel].tope_obstaculos++;
    }

}
static void pos_herramienta_totem(juego_t *juego, int numero_nivel){
    for(int i= 0; i<5;i++){
        juego->niveles[numero_nivel].herramientas[i].tipo = 'T';
        juego->niveles[numero_nivel].herramientas[i].posicion.fil = rand() % MAX_FILAS;
        juego->niveles[numero_nivel].herramientas[i].posicion.col = rand() % MAX_COLUMNAS;
        juego->niveles[numero_nivel].tope_herramientas++;
    }
}

static bool no_es_camino(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual-1].tope_camino;

    bool no_es_camino = false;
    for(int i = 0;i<tope;i++){
        if(posicion_fil == juego->niveles[juego->nivel_actual - 1].camino[i].fil && posicion_col == juego->niveles[juego->nivel_actual - 1].camino[i].col){
            no_es_camino = true;
        }
    }
    return no_es_camino;
}

static bool no_es_pared(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual-1].tope_paredes;

    bool no_es_pared = false;
    for(int i = 0;i<tope;i++){
        if(posicion_fil == juego->niveles[juego->nivel_actual - 1].paredes[i].fil && posicion_col == juego->niveles[juego->nivel_actual - 1].paredes[i].col){
            no_es_pared = true;
        }
    }
    return no_es_pared;
}
static bool no_es_totem(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual-1].tope_herramientas;

    bool no_es_totem = false;
    for(int i = 0;i<tope;i++){
        if(posicion_fil == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.fil && posicion_col == juego->niveles[juego->nivel_actual - 1].herramientas[i].posicion.col){
            no_es_totem = true;
        }
    }
    return no_es_totem;
}
static bool no_es_piedra(juego_t *juego, int posicion_fil, int posicion_col){
    int tope = juego->niveles[juego->nivel_actual-1].tope_obstaculos;

    bool no_es_piedra = false;
    for(int i = 0;i<tope;i++){
        if(posicion_fil == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.fil && posicion_col == juego->niveles[juego->nivel_actual - 1].obstaculos[i].posicion.col){
            no_es_piedra = true;
        }
    }
    return no_es_piedra;
    
}

static bool no_es_afuera(juego_t *juego, int posicion_fil, int posicion_col){
    if(posicion_fil >= 0 && posicion_fil < MAX_FILAS && posicion_col >= 0 && posicion_col < MAX_COLUMNAS){
        return true;
    }
    return false;
}





static void inicializar_obstaculo_catapulta(juego_t *juego, int numero_nivel){
    bool validado = false;

        juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].tipo = 'C';
        while(!validado){
            
            juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.col = rand() % MAX_COLUMNAS;
            juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.fil = rand() % MAX_FILAS;
            //Evalúa si la posicion de la catapulta no es camino, pared, herrentas u obstaculos. Si no es generará otra posición aleatoria hasta encontrar una válida.
            //Optimizar luego
            if(no_es_camino(juego, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.fil, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.col) == true&& no_es_pared(juego, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.fil, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.col) == true && no_es_totem(juego, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.fil, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.col) == true && no_es_piedra(juego, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.fil, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.col) == true && no_es_afuera(juego, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.fil, juego->niveles[numero_nivel].obstaculos[juego->niveles[numero_nivel].tope_obstaculos].posicion.col) == true){
                validado = true;
            }
            
        }
        juego->niveles[numero_nivel].tope_obstaculos++;
        
    }    
    void cargar_datos_nivel(juego_t* juego, int numero_nivel) {
    int nivel = numero_nivel - 1; 
    juego->niveles[nivel].tope_paredes = 0;
    juego->niveles[nivel].tope_camino = 0;
    juego->niveles[nivel].tope_obstaculos = 0;
    juego->niveles[nivel].tope_herramientas = 0;
    
    //Inicializo las paredes y el camino del nivel.
    obtener_mapa(juego->niveles[nivel].paredes, &(juego->niveles[nivel].tope_paredes), juego->niveles[nivel].camino, &(juego->niveles[nivel].tope_camino), numero_nivel);
    //Inicializo los obstáculos y las herramientas del nivel.

    inicializar_obstaculo_piedra(juego, nivel);
    inicializar_obstaculo_catapulta(juego, nivel);
    pos_herramienta_totem(juego, nivel);

    pos_pergamino(juego);
    
}




/* Pre condiciones: -
 * Post condiciones: Inicializará el juego, cargando toda la información inicial de Homero y de los 3 niveles.
 */
void inicializar_juego(juego_t *juego){
//Valores del personaje
    juego->homero.posicion.col = 0;
    juego->homero.posicion.fil = 0;
    juego->homero.antorcha_encendida = false;
    juego->homero.hechizos_reveladores = 5;
    juego->homero.vidas_restantes = 5;
    juego->homero.antorchas = 5;
    juego->homero.recolecto_pergamino = false;
    juego->nivel_actual = 1;
    juego->tope_niveles = 3;
    juego->camino_visible = true;

    //Nivel 1
    cargar_datos_nivel(juego, 1);
    
    //Nivel 2
    cargar_datos_nivel(juego, 2);

    //Nivel 3
    cargar_datos_nivel(juego, 3);

}

/* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego` y el nivel actual del juego tiene que ser 1 o 2.
 * Post condiciones: Actualizará el nivel actual el juego y el personaje para comenzar el siguiente nivel.
 */
void cambiar_nivel(juego_t* juego){
    juego->nivel_actual++;

    juego->homero.posicion.col = 0;
    juego->homero.posicion.fil = 0;
    
    juego->homero.recolecto_pergamino = false;
    juego->homero.antorchas = 5;
    juego->homero.antorcha_encendida = false;
    
    juego->camino_visible = true;
}



static bool detectar_pared(juego_t* juego, coordenada_t posicion_nueva){
    int nivel_actual = juego->nivel_actual;
    bool validado = false;
    int tope_paredes = juego->niveles[nivel_actual - 1].tope_paredes;
    for(int i=0; i<tope_paredes;i++){
        coordenada_t pared = juego->niveles[nivel_actual - 1].paredes[i];

        if(posicion_nueva.col == pared.col && posicion_nueva.fil == pared.fil)
            validado=true;

    }

return validado;
}


static bool posicion_valida(juego_t* juego, coordenada_t pos) {
    if (pos.fil < 0 || pos.fil >= 20 || pos.col < 0 || pos.col >= 30) {
        return false;
    }
    return true;

}



/* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego` y la acción
 * debe ser válida.
 * Post condiciones: Realizará la acción recibida por parámetro actualizando el juego.
 */
void realizar_jugada(juego_t *juego, char movimiento){

if (movimiento == ARRIBA){
    //Aplico filtros
    if(!detectar_pared(juego,juego->homero.posicion) && posicion_valida(juego, juego->homero.posicion)){
        juego->homero.posicion.fil--;
    }

    
}
else if (movimiento == ABAJO){
    //Aplico filtros
    if(!detectar_pared(juego, juego->homero.posicion) && posicion_valida(juego, juego->homero.posicion)){
        juego->homero.posicion.fil++;
    }
    
}
else if (movimiento == DERECHA) {
    //Aplico filtros
    if(!detectar_pared(juego, juego->homero.posicion) && posicion_valida(juego, juego->homero.posicion)){
        juego->homero.posicion.col++;
    }
}
else if (movimiento == IZQUIERDA){
    //Aplico filtros
    if(!detectar_pared(juego, juego->homero.posicion) && posicion_valida(juego, juego->homero.posicion)){
        juego->homero.posicion.col--;
    }
}
else if (movimiento == HECHIZO_REVELADOR){
    juego->homero.hechizos_reveladores--;
    juego->camino_visible = true;
}
else if (movimiento == ANTORCHA_MAGICA){
    juego->homero.antorchas--;
    juego->homero.antorcha_encendida = true;
}


if ((juego->homero.posicion.fil == juego->niveles[juego->nivel_actual - 1].camino[0].fil && juego->homero.posicion.col == juego->niveles[juego->nivel_actual - 1].camino[0].col) || movimiento == HECHIZO_REVELADOR){

}

if(juego->homero.posicion.fil == juego->niveles[juego->nivel_actual - 1].camino[0].fil && juego->homero.posicion.col == juego->niveles[juego->nivel_actual - 1].camino[0].col){
    juego->camino_visible = true;
} else juego->camino_visible = false;

if(juego->homero.posicion.fil == juego->niveles[juego->nivel_actual - 1].pergamino.fil && juego->homero.posicion.col == juego->niveles[juego->nivel_actual - 1].pergamino.col){
    juego->homero.recolecto_pergamino = true;
} else juego->homero.recolecto_pergamino = false;



}

/*
 * Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego `.
 * Post condiciones: Imprime el juego por pantalla.
 */
void mostrar_juego(juego_t juego){
//Aca añado las características del juego que quiero mostrar por pantalla, como la posición de homero, el nivel actual, las vidas restantes, etc.


//Revisar después si hacer una función para ver si homero choca con el obstaculo PIEDRA para llamar a la fucion
//de cambiar la pos del pergamino


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

