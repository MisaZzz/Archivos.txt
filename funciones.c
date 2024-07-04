#include <stdio.h>
#include <string.h>
#include "funciones.h"

void guardarClientes(char clientes[][2][40], int reservas[][4], const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s para escribir\n", filename);
        return;
    }

    for (int i = 0; i < 5; i++) {
        if (clientes[i][0][0] != '\0') {
            int habitacionReservada = -1;
            for (int j = 0; j < 10; j++) {
                if (reservas[j][0] == i) {
                    habitacionReservada = reservas[j][1] + 1;  // 
                    break;
                }
            }
            fprintf(file, "Cliente: %s || Cédula: %s || Habitación: %d\n", clientes[i][0], clientes[i][1], habitacionReservada);
        }
    }

    fclose(file);
}

void cargarClientes(char clientes[][2][40], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s para leer\n", filename);
        return;
    }
    char buffer[100];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL && i < 5) {
        sscanf(buffer, "Cliente: %[^|||]||| Cedula: %[^\n]", clientes[i][0], clientes[i][1]);
        i++;
    }
    fclose(file);
}

void guardarReservas(int reservas[][4], char habitaciones[][3][40], double precios[], const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s para escribir\n", filename);
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (reservas[i][3] != 0) {
            int habitacionIndice = reservas[i][1];
            const char *estadoPago = reservas[i][3] == 2 ? "Pagado" : "No pagado";
            fprintf(file, "Habitación: %s\t||\tTamaño: %s\t||\tHotel: %s\t||\tPrecio: %.2lf\t||\tEstado: %s\n",
                    habitaciones[habitacionIndice][0],
                    habitaciones[habitacionIndice][1],
                    habitaciones[habitacionIndice][2],
                    precios[habitacionIndice],
                    estadoPago);
        }
    }

    fclose(file);
}

void cargarReservas(int reservas[][4], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s para leer\n", filename);
        return;
    }
    int i = 0;
    while (fscanf(file, "%d,%d,%d,%d", &reservas[i][0], &reservas[i][1], &reservas[i][2], &reservas[i][3]) == 4 && i < 10) {
        i++;
    }
    fclose(file);
}

void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char tipo[40];
    printf("Ingrese el tamaño de habitacion que desea buscar: ");
    scanf("%s", tipo);
    printf("\n-------------------DATOS--------------------\n#\t\tTamaño\t\tHotel\t\t\tPrecio\n--------------------------------------------\n");

    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n--------------------------------------------\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char NomHotel[40];
    printf("Ingrese el nombre del hotel: ");
    scanf(" %39[^\n]", NomHotel);
    printf("\n-------------------DATOS--------------------\n#\t\tTamaño\t\tHotel\t\t\tPrecio\n--------------------------------------------\n");

    for (int i = 0; i < 9; i++) {
        if (strcasecmp(habitaciones[i][2], NomHotel) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n--------------------------------------------\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
}

void realizarReserva(int *numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][4], double precios[]) {
    char nombreCliente[40];
    char cedulaCliente[40];
    int habitacionSeleccionada;

    printf("Ingrese su nombre: ");
    scanf(" %39[^\n]", nombreCliente);

    printf("Ingrese su cedula: ");
    scanf(" %39[^\n]", cedulaCliente);

    printf("Elija el numero de habitacion que desea reservar (1-9): ");
    scanf("%d", &habitacionSeleccionada);

    if (habitacionSeleccionada < 1 || habitacionSeleccionada > 9) {
        printf("Número de habitación inválido\n");
        return;
    }

    if (reservas[habitacionSeleccionada - 1][3] != 0) {
        printf("*** La habitación %d ya está reservada ***\n", habitacionSeleccionada);
        return;
    }

    int indiceCliente = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedulaCliente) == 0) {
            indiceCliente = i;
            break;
        }
    }

    if (indiceCliente == -1) {
        for (int i = 0; i < 5; i++) {
            if (clientes[i][0][0] == '\0') {
                strcpy(clientes[i][0], nombreCliente);
                strcpy(clientes[i][1], cedulaCliente);
                indiceCliente = i;
                break;
            }
        }

        if (indiceCliente == -1) {
            printf("No hay espacio para más clientes\n");
            return;
        }
    }

    reservas[habitacionSeleccionada - 1][3] = 1;  // Marcamos la habitación como reservada
    reservas[habitacionSeleccionada - 1][0] = indiceCliente;  // Guardamos el índice del cliente
    reservas[habitacionSeleccionada - 1][1] = habitacionSeleccionada - 1;  // Guardamos el número de habitación (ajustado al índice del arreglo)
    *numHabitacion = habitacionSeleccionada;

    printf("\n¡Reserva realizada con éxito!\n");
    printf("*** Habitación seleccionada %d ***\n", *numHabitacion);
    printf("Precio: %.2lf\n", precios[habitacionSeleccionada - 1]);  
    guardarClientes(clientes, reservas, "clientes.txt");
}

void imprimirReserva(int *numReserva, int reservas[][4], char habitaciones[][3][40], double precios[], char clientes[][2][40]) {
    int indiceReserva = *numReserva - 1;

    if (indiceReserva < 0 || indiceReserva >= 10) {
        printf("Número de reserva inválido.\n");
        return;
    }

    if (reservas[indiceReserva][3] == 0) {
        printf("La reserva seleccionada no está activa.\n");
        return;
    }

    int indiceCliente = reservas[indiceReserva][0];
    int indiceHabitacion = reservas[indiceReserva][1];
    double precioReserva = precios[indiceHabitacion];
    char *nombreCliente = clientes[indiceCliente][0];
    char *cedulaCliente = clientes[indiceCliente][1];
    char *tipoHabitacion = habitaciones[indiceHabitacion][1];
    char *hotel = habitaciones[indiceHabitacion][2];

    printf("\n=========== DETALLES DE LA RESERVA ===========\n");
    printf("Número de reserva: %d\n", *numReserva);
    printf("Cliente: %s\n", nombreCliente);
    printf("Cédula: %s\n", cedulaCliente);
    printf("Hotel: %s\n", hotel);
    printf("Tipo de habitación: %s\n", tipoHabitacion);
    printf("Precio: $%.2f\n", precioReserva);
    printf("==============================================\n");
}

void pagarReserva(int reservas[][4], char habitaciones[][3][40], double precios[], char clientes[][2][40], const char *filename) {
    char cedulaCliente[40];
    printf("Ingrese su cedula: ");
    scanf(" %39[^\n]", cedulaCliente);

    int indiceCliente = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedulaCliente) == 0) {
            indiceCliente = i;
            break;
        }
    }

    if (indiceCliente == -1) {
        printf("No se encontró un cliente con esa cédula.\n");
        return;
    }

    int indiceReserva = -1;
    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == indiceCliente && reservas[i][3] == 1) {
            indiceReserva = i;
            break;
        }
    }

    if (indiceReserva == -1) {
        printf("No se encontró una reserva activa para ese cliente.\n");
        return;
    }

    int indiceHabitacion = reservas[indiceReserva][1];
    double precio = precios[indiceHabitacion];

    printf("\n=========== DETALLES DE PAGO ===========\n");
    printf("Cliente: %s\n", clientes[indiceCliente][0]);
    printf("Cédula: %s\n", clientes[indiceCliente][1]);
    printf("Hotel: %s\n", habitaciones[indiceHabitacion][2]);
    printf("Tipo de habitación: %s\n", habitaciones[indiceHabitacion][1]);
    printf("Precio: $%.2f\n", precio);
    printf("========================================\n");
    printf("¿Desea proceder con el pago? (s/n): ");

    char confirmacion;
    scanf(" %c", &confirmacion);

    if (confirmacion == 's' || confirmacion == 'S') {
        reservas[indiceReserva][3] = 2;  // Marcamos la reserva como pagada
        guardarReservas(reservas, habitaciones, precios, filename);
        printf("Reserva pagada con éxito.\n");
    } else {
        printf("Pago cancelado.\n");
    }
}

void verReserva(char clientes[][2][40], int reservas[][4], char habitaciones[][3][40], double precios[]) {
    char nombreCliente[40];
    char cedulaCliente[40];

    printf("Ingrese el nombre del cliente: ");
    scanf(" %39[^\n]", nombreCliente);

    printf("Ingrese la cedula del cliente: ");
    scanf(" %39[^\n]", cedulaCliente);

    int indiceCliente = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][0], nombreCliente) == 0 && strcmp(clientes[i][1], cedulaCliente) == 0) {
            indiceCliente = i;
            break;
        }
    }

    if (indiceCliente == -1) {
        printf("No se encontró un cliente con ese nombre y cédula.\n");
        return;
    }

    int indiceReserva = -1;
    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == indiceCliente && reservas[i][3] != 0) {
            indiceReserva = i;
            break;
        }
    }

    if (indiceReserva == -1) {
        printf("No se encontró una reserva activa para ese cliente.\n");
        return;
    }

    int indiceHabitacion = reservas[indiceReserva][1];
    double precioReserva = precios[indiceHabitacion];
    char *tipoHabitacion = habitaciones[indiceHabitacion][1];
    char *hotel = habitaciones[indiceHabitacion][2];
    char *estadoPago = reservas[indiceReserva][3] == 2 ? "Pagado" : "No pagado";

    printf("\n=========== DETALLES DE LA RESERVA ===========\n");
    printf("Cliente: %s\n", nombreCliente);
    printf("Cédula: %s\n", cedulaCliente);
    printf("Hotel: %s\n", hotel);
    printf("Tipo de habitación: %s\n", tipoHabitacion);
    printf("Precio: $%.2f\n", precioReserva);
    printf("Estado de pago: %s\n", estadoPago);
    printf("==============================================\n");
}
