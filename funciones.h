#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void guardarClientes(char clientes[][2][40], int reservas[][4], const char *filename);
void cargarClientes(char clientes[][2][40], const char *filename);
void guardarReservas(int reservas[][4], char habitaciones[][3][40], double precios[], const char *filename);
void cargarReservas(int reservas[][4], const char *filename);
void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]);
void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]);
void realizarReserva(int *numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][4], double precios[]);
void imprimirReserva(int *numReserva, int reservas[][4], char habitaciones[][3][40], double precios[], char clientes[][2][40]);
void pagarReserva(int reservas[][4], char habitaciones[][3][40], double precios[], char clientes[][2][40], const char *filename);
void verReserva(char clientes[][2][40], int reservas[][4], char habitaciones[][3][40], double precios[]);


#endif 
