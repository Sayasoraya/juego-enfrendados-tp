#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Jugador {
    string nombre;
    int puntos;
    int dados[20];
    int cantidadDados;
};

// Funciones para tirar dados
int tirarDado6() {
    return rand() % 6 + 1;
}

int tirarDado12() {
    return rand() % 12 + 1;
}

// Inicializar jugadores
void inicializarJugadores(Jugador& j1, Jugador& j2) {
    cout << "Ingrese el nombre del Jugador 1: ";
    cin >> j1.nombre;
    j1.puntos = 0;
    j1.cantidadDados = 6;

    cout << "Ingrese el nombre del Jugador 2: ";
    cin >> j2.nombre;
    j2.puntos = 0;
    j2.cantidadDados = 6;
}

// Decidir quién empieza
Jugador* decidirInicio(Jugador& j1, Jugador& j2) {
    int dado1, dado2;
    do {
        dado1 = tirarDado6();
        dado2 = tirarDado6();
        cout << j1.nombre << " tira: " << dado1 << endl;
        cout << j2.nombre << " tira: " << dado2 << endl;

        if (dado1 > dado2) {
            cout << j1.nombre << " comienza la partida." << endl;
            return &j1;
        } else if (dado2 > dado1) {
            cout << j2.nombre << " comienza la partida." << endl;
            return &j2;
        } else {
            cout << "Empate. Se repite la tirada." << endl;
        }
    } while (true);
}

// Mostrar dados con índices
void mostrarDadosConIndices(int dados[], int cantidad) {
    cout << "Dados:     ";
    for (int i = 0; i < cantidad; i++) {
        cout << "[" << dados[i] << "] ";
    }
    cout << "\nIndices:   ";
    for (int i = 0; i < cantidad; i++) {
        cout << " " << i + 1 << "  ";
    }
    cout << endl;
}

// Turno de un jugador
void jugarTurno(Jugador& actual, Jugador& rival) {
    cout << "\nTurno de " << actual.nombre << ":\n";

    int dado1 = tirarDado12();
    int dado2 = tirarDado12();
    int objetivo = dado1 + dado2;

    cout << "Dados objetivo: " << dado1 << " + " << dado2 << " = " << objetivo << endl;

    for (int i = 0; i < actual.cantidadDados; i++) {
        actual.dados[i] = tirarDado6();
    }

    mostrarDadosConIndices(actual.dados, actual.cantidadDados);

    int suma = 0, seleccion, elegidos[20], cantElegidos = 0;
    bool usados[20] = {false};

    while (true) {
        cout << "Selecciona el dado #" << cantElegidos + 1 << " (ingresá 0 para rendirte): ";
        cin >> seleccion;

        if (seleccion == 0) {
            cout << "Te rendiste. Tirada fallida.\n";
            break;
        }

        if (seleccion < 1 || seleccion > actual.cantidadDados || usados[seleccion - 1]) {
            cout << "Seleccion invalida o ya elegida. Intentá de nuevo.\n";
            continue;
        }

        usados[seleccion - 1] = true;
        int valor = actual.dados[seleccion - 1];
        suma += valor;
        elegidos[cantElegidos++] = seleccion - 1;

        cout << "Suma actual: " << suma << endl;

        if (suma == objetivo) {
            int puntos = objetivo * cantElegidos;
            actual.puntos += puntos;

            cout << "¡Tirada exitosa! Ganaste " << puntos << " puntos.\n";

            for (int i = 0; i < cantElegidos; i++) {
                if (rival.cantidadDados < 20) {
                    rival.dados[rival.cantidadDados++] = actual.dados[elegidos[i]];
                }
            }

            actual.cantidadDados -= cantElegidos;

            if (actual.cantidadDados == 0) {
                cout << actual.nombre << " se quedó sin dados. ¡Victoria automática con 10000 puntos!\n";
                actual.puntos += 10000;
            }
            break;
        } else if (suma > objetivo) {
            cout << "La suma superó el objetivo. Tirada fallida.\n";
            break;
        }

        if (cantElegidos >= actual.cantidadDados) {
            cout << "Ya elegiste todos tus dados. Tirada fallida por no alcanzar el objetivo.\n";
            break;
        }
    }

    if (suma != objetivo && rival.cantidadDados > 1) {
        actual.dados[actual.cantidadDados++] = rival.dados[rival.cantidadDados - 1];
        rival.cantidadDados--;
        cout << actual.nombre << " recibe un dado de " << rival.nombre << " por tirada fallida.\n";
    }

    cout << "Puntaje actual: " << actual.nombre << ": " << actual.puntos << " | "
         << rival.nombre << ": " << rival.puntos << endl;
    cout << "Dados restantes: " << actual.nombre << ": " << actual.cantidadDados << " | "
         << rival.nombre << ": " << rival.cantidadDados << endl;
}

// Estadísticas (simples, sin almacenamiento global)
void mostrarEstadisticas(const Jugador& j1, const Jugador& j2) {
    cout << "\n----- ESTADISTICAS -----\n";
    if (j1.puntos > j2.puntos) {
        cout << "Mayor puntaje: " << j1.nombre << " con " << j1.puntos << " puntos.\n";
        cout << "Menor puntaje: " << j2.nombre << " con " << j2.puntos << " puntos.\n";
    } else if (j2.puntos > j1.puntos) {
        cout << "Mayor puntaje: " << j2.nombre << " con " << j2.puntos << " puntos.\n";
        cout << "Menor puntaje: " << j1.nombre << " con " << j1.puntos << " puntos.\n";
    } else {
        cout << "Ambos jugadores empataron con " << j1.puntos << " puntos.\n";
    }
}

// Créditos
void mostrarCreditos() {
    cout << "\nTrabajo realizado por:\n";
    cout << "- Soraya Zaragoza (30656)\n";
    cout << "- Rodrigo Garcia Dieguez (32655)\n";
    cout << "Grupo: Mapache Team\n";
    cout << "Inspirado en el juego inventado por Angel Simón.\n";
}

// Menú
void mostrarMenu() {
    cout << "\n----- MENU PRINCIPAL -----\n";
    cout << "1 - JUGAR\n";
    cout << "2 - ESTADISTICAS\n";
    cout << "3 - CREDITOS\n";
    cout << "0 - SALIR\n";
    cout << "Seleccione una opcion: ";
}

// Partida completa (3 rondas)
void jugarPartida() {
    Jugador j1, j2;
    inicializarJugadores(j1, j2);
    Jugador* primero = decidirInicio(j1, j2);
    Jugador* segundo = (primero == &j1) ? &j2 : &j1;

    for (int ronda = 1; ronda <= 3; ronda++) {
        cout << "\n========== RONDA " << ronda << " ==========\n";

        if (primero->cantidadDados > 0)
            jugarTurno(*primero, *segundo);
        if (primero->cantidadDados == 0)
            break;

        if (segundo->cantidadDados > 0)
            jugarTurno(*segundo, *primero);
        if (segundo->cantidadDados == 0)
            break;
    }

    cout << "\n====== RESULTADOS FINALES ======\n";
    if (j1.puntos > j2.puntos)
        cout << "Ganador: " << j1.nombre << " con " << j1.puntos << " puntos.\n";
    else if (j2.puntos > j1.puntos)
        cout << "Ganador: " << j2.nombre << " con " << j2.puntos << " puntos.\n";
    else
        cout << "Empate con " << j1.puntos << " puntos cada uno.\n";
}

// MAIN
int main() {
    srand(time(0));
    int opcion;
    Jugador j1, j2;

    do {
        mostrarMenu();
        cin >> opcion;
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
                cout << "¿Seguro que querés salir? (s/n): ";
                char c;
                cin >> c;
                if (c == 's' || c == 'S') {
                    cout << "Gracias por jugar. ¡Hasta la próxima!\n";
                    return 0;
                }
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (true);
}
