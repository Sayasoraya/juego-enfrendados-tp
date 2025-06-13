#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Necesario para usar rand()

typedef struct {
    char nombre[30];      // para guardar el nombre del jugador
    int puntos;           // para guardar los puntos acumulados
    int dados[20];        // para guardar los valores de sus dados (6 dados al empezar)
    int cantidadDados;    // cuantos dados tiene actualmente
} Jugador;

// Tirar un dado de 6 caras
int tirarDado6() {
    return rand() % 6 + 1;
}

// Pedir los nombres de los jugadores e inicializar puntos y dados
void inicializarJugadores(Jugador *j1, Jugador *j2) {
    printf("\nIngrese el nombre del Jugador 1: ");
    scanf("%s", j1->nombre);
    j1->puntos = 0;
    j1->cantidadDados = 6;

    printf("Ingrese el nombre del Jugador 2: ");
    scanf("%s", j2->nombre);
    j2->puntos = 0;
    j2->cantidadDados = 6;
}

// Determinar quien empieza tirando un dado
Jugador* decidirInicio(Jugador *j1, Jugador *j2) {
    int dado1, dado2;

    do {
        dado1 = tirarDado6();
        dado2 = tirarDado6();
        printf("\n%s tira: %d\n", j1->nombre, dado1);
        printf("%s tira: %d\n", j2->nombre, dado2);

        if (dado1 > dado2) {
            printf("%s comienza la partida.\n", j1->nombre);
            return j1;
        } else if (dado2 > dado1) {
            printf("%s comienza la partida.\n", j2->nombre);
            return j2;
        } else {
            printf("Empate. Se repite la tirada.\n");
        }
    } while (dado1 == dado2);

    return NULL;
}

// Mostrar el menu principal
void mostrarMenu() {
    printf("\n----- MENU PRINCIPAL -----\n");
    printf("1 - JUGAR\n");
    printf("2 - ESTADISTICAS\n");
    printf("3 - CREDITOS\n");
    printf("0 - SALIR\n");
    printf("--------------------------\n");
    printf("Seleccione una opcion: ");
}

// Mostrar los creditos del TP
void mostrarCreditos() {
    printf("\nTrabajo practico realizado por:\n");
    printf("- Soraya Zaragoza\n");
    printf("- Rodrigo Garcia Dieguez\n");
    printf("Equipo: Enfrentados 2025 - UTN\n");
}

// Mostrar mensaje de estadisticas
void mostrarEstadisticas() {
    printf("\nEstadisticas (por ahora no implementadas)\n");
}

// Funcion que inicia la partida (falta completar logica del juego)
void jugarPartida() {
    Jugador jugador1, jugador2;

    printf("\n=== Iniciando el juego Enfrentados ===\n");

    inicializarJugadores(&jugador1, &jugador2);

    Jugador *quienEmpieza = decidirInicio(&jugador1, &jugador2);

    // Solo muestra quien empieza, luego se agregara la logica del juego
    printf("\nComenzaria a jugar %s\n", quienEmpieza->nombre);
    printf("(Aun falta programar las rondas del juego...)\n");
}

// Programa principal
int main() {
    int opcion;
    char confirmar;

    srand(time(NULL)); // Para generar numeros aleatorios diferentes cada vez

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                jugarPartida();
                break;
            case 2:
                mostrarEstadisticas();
                break;
            case 3:
                mostrarCreditos();
                break;
            case 0:
                printf("\nEstas segura de que queres salir? (s/n): ");
                scanf(" %c", &confirmar);
                if (confirmar == 's' || confirmar == 'S') {
                    printf("Saliendo del programa... Hasta luego.\n");
                    return 0;
                }
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }

        system("pause");
        system("cls"); // Limpia pantalla (en Windows)

    } while (1);

    return 0;
}
