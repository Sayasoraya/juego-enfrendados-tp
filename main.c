#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
    printf("- Soraya Zaragoza (30656)\n");
    printf("- Rodrigo Garcia Dieguez (32655)\n");
    printf("Grupo: MAPACHE TEAM\n");
    printf("Juego inventado por Angel Simon\n");
}

void mostrarEstadisticas(Jugador j1, Jugador j2) {
    printf("\n=== ESTADISTICAS ===\n");
    if (j1.puntos > j2.puntos)
        printf("Jugador con mayor puntaje: %s con %d puntos\n", j1.nombre, j1.puntos);
    else if (j2.puntos > j1.puntos)
        printf("Jugador con mayor puntaje: %s con %d puntos\n", j2.nombre, j2.puntos);
    else
        printf("Ambos jugadores tienen el mismo puntaje: %d\n", j1.puntos);
}

void inicializarJugadores(Jugador *j1, Jugador *j2) {
    printf("Ingrese el nombre del Jugador 1: ");
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

        if (dado1 > dado2) return j1;
        if (dado2 > dado1) return j2;
        printf("Empate. Se repite la tirada.\n");

    } while (dado1 == dado2);

    return NULL;
}

void mostrarDados(int dados[], int cantidad) {
    printf("Dados:     ");
    for (int i = 0; i < cantidad; i++) printf("[%d] ", dados[i]);
    printf("\nIndices:   ");
    for (int i = 0; i < cantidad; i++) printf(" %d  ", i + 1);
    printf("\n");
}

int jugarTurno(Jugador* actual, Jugador* rival) {
    printf("\nTurno de %s\n", actual->nombre);
    int d1 = tirarDado12(), d2 = tirarDado12();
    int objetivo = d1 + d2;

    printf("Dados objetivo: %d + %d = %d\n", d1, d2, objetivo);

    for (int i = 0; i < actual->cantidadDados; i++)
        actual->dados[i] = tirarDado6();

    mostrarDados(actual->dados, actual->cantidadDados);

    int suma = 0, elegidos[20], usados = 0;
    int yaElegidos[20] = {0};

    while (1) {
        int index;
        printf("Seleccion #%d (0 para rendirse): ", usados + 1);
        scanf("%d", &index);

        if (index == 0) {
            printf("Tirada fallida.\n");
            break;
        }

        if (index < 1 || index > actual->cantidadDados || yaElegidos[index - 1]) {
            printf("Indice invalido o ya elegido.\n");
            continue;
        }

        yaElegidos[index - 1] = 1;
        suma += actual->dados[index - 1];
        elegidos[usados++] = index - 1;

        printf("Suma actual: %d\n", suma);

        if (suma == objetivo) {
            int puntos = objetivo * usados;
            actual->puntos += puntos;
            printf("­Tirada exitosa! Ganaste %d puntos.\n", puntos);

            for (int i = 0; i < usados; i++) {
                if (rival->cantidadDados < 20)
                    rival->dados[rival->cantidadDados++] = actual->dados[elegidos[i]];
            }

            actual->cantidadDados -= usados;

            if (actual->cantidadDados == 0) {
                printf("%s se quedo sin dados. Gana automaticamente con +10000 puntos.\n", actual->nombre);
                actual->puntos += 10000;
                return 1;
            }

            return 0;
        } else if (suma > objetivo) {
            printf("La suma supero el objetivo. Tirada fallida.\n");
            break;
        }
    }

    if (rival->cantidadDados > 1) {
        actual->dados[actual->cantidadDados++] = rival->dados[--rival->cantidadDados];
        printf("%s recibe 1 dado de %s por tirada fallida.\n", actual->nombre, rival->nombre);
    }

    return 0;
}

void jugarPartida() {
    Jugador j1, j2;
    inicializarJugadores(&j1, &j2);
    Jugador *turno = decidirInicio(&j1, &j2);
    Jugador *otro = (turno == &j1) ? &j2 : &j1;

    printf("Comienza %s\n", turno->nombre);

    for (int ronda = 1; ronda <= 3; ronda++) {
        printf("\n--- RONDA %d ---\n", ronda);

        if (jugarTurno(turno, otro)) break;
        printf("\nPresione una tecla para continuar...\n");
        getchar(); getchar();

        if (jugarTurno(otro, turno)) break;
        printf("\nPresione una tecla para continuar...\n");
        getchar(); getchar();
    }

    printf("\n--- RESULTADOS FINALES ---\n");
    printf("%s: %d puntos\n", j1.nombre, j1.puntos);
    printf("%s: %d puntos\n", j2.nombre, j2.puntos);

    if (j1.puntos > j2.puntos)
        printf("Gana %s\n", j1.nombre);
    else if (j2.puntos > j1.puntos)
        printf("Gana %s\n", j2.nombre);
    else
        printf("Empate\n");
}

int main() {
    srand(time(NULL));
    int opcion;
    char confirmar;

    Jugador j1 = {"", 0, {}, 0}, j2 = {"", 0, {}, 0};

    do {
        mostrarMenu();
        scanf(" %d", &opcion);

        switch (opcion) {
            case 1:
                jugarPartida();
                break;
            case 2:
                mostrarEstadisticas(j1, j2);
                break;
            case 3:
                mostrarCreditos();
                break;
            case 0:
                printf("¨Seguro que deseas salir? (s/n): ");
                scanf(" %c", &confirmar);
                if (confirmar == 's' || confirmar == 'S')
                    return 0;
                break;
            default:
                printf("Opcion no valida.\n");
        }

        system("pause");
        system("cls");

    } while (1);

    return 0;
}
