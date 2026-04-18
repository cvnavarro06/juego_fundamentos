#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FILAS 10
#define MAX_COLS 10

// Mapa de prueba ('#' son paredes, '.' es pasto)
char mapa[MAX_FILAS][MAX_COLS] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '.', '#', '.', '#', '#', '.', '#'},
    {'#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

int main() {
    int pos_fil = 1; // Posición inicial del jugador
    int pos_col = 1;
    bool antorcha_encendida = false;
    char tecla;
    bool jugando = true;

    while (jugando) {
        // 1. LIMPIAR PANTALLA (Dependiendo del sistema operativo)
        system("clear"); // Usar system("cls") si estás en Windows

        // 2. DIBUJAR EL MAPA
        printf("--- MINI JUEGO DE VISIBILIDAD ---\n\n");
        for (int f = 0; f < MAX_FILAS; f++) {
            for (int c = 0; c < MAX_COLS; c++) {
                
                // Si es la posición del jugador, lo dibujamos siempre
                if (f == pos_fil &&c == pos_col) {
                    printf("@ ");
                } else {
                    // CALCULAMOS LA DISTANCIA DE MANHATTAN
                    int distancia = abs(pos_fil - f) + abs(pos_col - c);

                    // Si la antorcha está encendida Y la distancia es <= 3, revelamos
                    if (antorcha_encendida && distancia <= 2) {
                        printf("%c ", mapa[f][c]); // Mostramos lo que hay en el mapa
                    } else {
                        printf("? "); // Oscuridad
                    }
                }
            }
            printf("\n");
        }

        // 3. MOSTRAR INSTRUCCIONES
        printf("\nPosicion: (%i, %i) | Antorcha: %s\n", pos_fil, pos_col, antorcha_encendida ? "ENCENDIDA" : "APAGADA");
        printf("Controles: [W] Arriba [S] Abajo [A] Izq [D] Der\n");
        printf("[T] Activar/Desactivar Antorcha | [Q] Salir\n");
        printf("Tu movimiento: ");
        
        // 4. LEER TECLA
        scanf(" %c", &tecla);

        // 5. PROCESAR ACCIÓN
        int nueva_fil = pos_fil;
        int nueva_col = pos_col;

        if (tecla == 'w' || tecla == 'W') nueva_fil--;
        if (tecla == 's' || tecla == 'S') nueva_fil++;
        if (tecla == 'a' || tecla == 'A') nueva_col--;
        if (tecla == 'd' || tecla == 'D') nueva_col++;
        if (tecla == 't' || tecla == 'T') antorcha_encendida = !antorcha_encendida;
        if (tecla == 'q' || tecla == 'Q') jugando = false;

        // Validar que no se salga del mapa ni pise paredes
        if (nueva_fil >= 0 && nueva_fil < MAX_FILAS && nueva_col >= 0 && nueva_col < MAX_COLS) {
            if (mapa[nueva_fil][nueva_col] != '#') {
                pos_fil = nueva_fil;
                pos_col = nueva_col;
            }
        }
    }

    printf("¡Gracias por probar el sandbox!\n");
    return 0;
}