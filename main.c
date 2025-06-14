#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nombre[30];
    int puntos;
    int dados[20];
    int cantidadDados;
} Jugador;

int tirarDado6() {
    return rand() % 6 + 1;
}

int tirarDado12() {
    return rand() % 12 + 1;
}

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
    } while (1);
}

void mostrarMenu() {
    printf("\n----- MENU PRINCIPAL -----\n");
    printf("1 - JUGAR\n");
    printf("2 - ESTADISTICAS\n");
    printf("3 - CREDITOS\n");
    printf("0 - SALIR\n");
    printf("--------------------------\n");
    printf("Seleccione una opcion: ");
}

void mostrarCreditos() {
    printf("\nTrabajo practico realizado por:\n");
    printf("- Soraya Zaragoza\n");
    printf("- Rodrigo Garcia Dieguez\n");
    printf("Equipo: Enfrentados 2025 - UTN\n");
}

void mostrarEstadisticas() {
    printf("\nEstadisticas (por ahora no implementadas)\n");
}

void mostrarDadosConIndices(int dados[], int cantidad) {
    printf("Dados:     ");
    for (int i = 0; i < cantidad; i++) {
        printf("[%d] ", dados[i]);
    }
    printf("\nIndices:   ");
    for (int i = 0; i < cantidad; i++) {
        printf(" %d  ", i + 1);
    }
    printf("\n");
}

void jugarTurno(Jugador* jugadorActual, Jugador* rival) {
    printf("\nTurno de %s:\n", jugadorActual->nombre);

    int dadoObj1 = tirarDado12();
    int dadoObj2 = tirarDado12();
    int numeroObjetivo = dadoObj1 + dadoObj2;
    printf("Dados objetivo: %d + %d = %d (Numero objetivo)\n", dadoObj1, dadoObj2, numeroObjetivo);

    if (jugadorActual->cantidadDados > 20) jugadorActual->cantidadDados = 20;
    if (jugadorActual->cantidadDados < 1) {
        printf("%s no tiene dados para jugar. Salta el turno.\n", jugadorActual->nombre);
        return;
    }

    for (int i = 0; i < jugadorActual->cantidadDados; i++) {
        jugadorActual->dados[i] = tirarDado6();
    }

    mostrarDadosConIndices(jugadorActual->dados, jugadorActual->cantidadDados);

    int suma = 0;
    int elegidos[20] = {0};
    int usados[20] = {0};
    int cantidadElegidos = 0;

    printf("\nSelecciona los dados uno por uno (ingresa el indice). Ingresa 0 para rendirte:\n");
    while (1) {
        int seleccion;
        printf("Seleccion #%d: ", cantidadElegidos + 1);
        scanf("%d", &seleccion);

        if (seleccion == 0) {
            printf("Rendiste la tirada. Se considera fallida.\n");
            break;
        }

        if (seleccion < 1 || seleccion > jugadorActual->cantidadDados) {
            printf("Indice invalido. Intente nuevamente.\n");
            continue;
        }
        if (usados[seleccion - 1]) {
            printf("Ese dado ya fue seleccionado. Elegi otro.\n");
            continue;
        }

        int valorSeleccionado = jugadorActual->dados[seleccion - 1];
        suma += valorSeleccionado;
        usados[seleccion - 1] = 1;
        elegidos[cantidadElegidos++] = seleccion - 1;

        printf("Suma actual: %d\n", suma);

        if (suma == numeroObjetivo) {
            int puntosGanados = numeroObjetivo * cantidadElegidos;
            jugadorActual->puntos += puntosGanados;
            printf("\n­Tirada exitosa!\n");
            printf("Ganaste %d puntos.\n", puntosGanados);

            for (int i = 0; i < cantidadElegidos; i++) {
                if (rival->cantidadDados < 20) {
                    rival->dados[rival->cantidadDados++] = jugadorActual->dados[elegidos[i]];
                }
            }

            jugadorActual->cantidadDados -= cantidadElegidos;

            if (jugadorActual->cantidadDados == 0) {
                printf("%s se quedo sin dados. ­Gana automaticamente con 10000 puntos extra!\n", jugadorActual->nombre);
                jugadorActual->puntos += 10000;
            }
            break;
        } else if (suma > numeroObjetivo) {
            printf("La suma supero el objetivo. Tirada fallida.\n");
            break;
        }
    }

    if (suma != numeroObjetivo && rival->cantidadDados > 1) {
        jugadorActual->dados[jugadorActual->cantidadDados++] = rival->dados[rival->cantidadDados - 1];
        rival->cantidadDados--;
        printf("%s recibe 1 dado de %s por tirada fallida.\n", jugadorActual->nombre, rival->nombre);
    }

    printf("Puntaje actual: %s: %d | %s: %d\n", jugadorActual->nombre, jugadorActual->puntos, rival->nombre, rival->puntos);
    printf("Dados restantes: %s: %d | %s: %d\n", jugadorActual->nombre, jugadorActual->cantidadDados, rival->nombre, rival->cantidadDados);
}

void jugarPartida() {
    Jugador jugador1, jugador2;
    printf("\n=== Iniciando el juego Enfrentados ===\n");
    inicializarJugadores(&jugador1, &jugador2);
    Jugador *turno = decidirInicio(&jugador1, &jugador2);
    Jugador *otro = (turno == &jugador1) ? &jugador2 : &jugador1;

    for (int ronda = 1; ronda <= 3; ronda++) {
        printf("\n===== Ronda %d =====\n", ronda);
        jugarTurno(turno, otro);
        jugarTurno(otro, turno);
    }

    printf("\n--- Resultado final ---\n");
    printf("%s: %d puntos\n", jugador1.nombre, jugador1.puntos);
    printf("%s: %d puntos\n", jugador2.nombre, jugador2.puntos);

    if (jugador1.puntos > jugador2.puntos) {
        printf("Ganador: %s\n", jugador1.nombre);
    } else if (jugador2.puntos > jugador1.puntos) {
        printf("Ganador: %s\n", jugador2.nombre);
    } else {
        printf("­Empate!\n");
    }
}

int main() {
    int opcion;
    char confirmar;
    srand(time(NULL));
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
        system("cls");
    } while (1);
    return 0;
}
