#include <stdio.h>
#include <string.h>
#include "funciones.h"

double precios[] = {90, 120, 160, 65, 100, 140, 85, 110, 150};

int main(int argc, char *argv[]) {
    char clientes[5][2][40] = {
        {"", ""},
        {"", ""},
        {"", ""},
        {"", ""},
        {"", ""}
    };

    char habitaciones[9][3][40] = {
        {"1", "simple", "Dan Carlton"},
        {"2", "doble", "Dan Carlton"},
        {"3", "triple", "Dan Carlton"},
        {"4", "simple", "Swissotel"},
        {"5", "doble", "Swissotel"},
        {"6", "triple", "Swissotel"},
        {"7", "simple", "Sheraton"},
        {"8", "doble", "Sheraton"},
        {"9", "triple", "Sheraton"}
    };

    int reservas[10][4] = {
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0}
    };

    cargarClientes(clientes, "clientes.txt");
    cargarReservas(reservas, "reservas.txt");

    int opcion, numHabitacion = 0, numReserva = 0;
    do {
        printf("\nEscoja una opción:\n1. Buscar Habitación\n2. Realizar reserva\n3. Pagar Reserva\n4. Ver Reserva\n5. Salir\n>> ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("============TIPO HABITACION============\n");
                printf("1. Por tamaño\n2. Por Hotel\n>> ");
                scanf("%d", &opcion);
                switch (opcion) {
                    case 1:
                        printf("-------TIPO DE TAMAÑOS-------\n -doble-\n -triple-\n -simple-\n------------\n>> ");
                        buscarPorTamano(&numHabitacion, habitaciones, precios);
                        break;
                    case 2:
                        printf("-------HOTELES-------\n -Dan Carlton-\n -Swissotel-\n -Sheraton-\n----------------\n>> ");
                        buscarHotel(&numHabitacion, habitaciones, precios);
                        break;
                    default:
                        printf("Opción no válida.\n");
                        break;
                }
                break;
            case 2:
                realizarReserva(&numHabitacion, habitaciones, clientes, reservas, precios);
                guardarClientes(clientes, reservas, "clientes.txt");
                guardarReservas(reservas, habitaciones, precios, "reservas.txt");
                break;
            case 3:
                pagarReserva(reservas, habitaciones, precios, clientes, "reservas.txt");
                break;
            case 4:
                verReserva(clientes, reservas, habitaciones, precios);
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida, por favor ingrese una opción válida.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}

