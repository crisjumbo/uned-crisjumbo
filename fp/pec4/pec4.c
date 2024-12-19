#include <stdio.h>

char renderMenu();
void editBuilding();
void listBuildings();
void availableApartments();
void reserveApartment();
void monthlyReservations();


int main() {
    char option;

    option = renderMenu();
    editBuilding();
    listBuildings();
    availableApartments();
    reserveApartment();
    monthlyReservations();

    return 0;
};

char renderMenu() {
    char option;

    printf("GesRAE: Gestion de Reservas Apartamentos-Edificios\n");
    printf("\n");
    printf("    Editar Edificion                        (Pulsar E)\n");
    printf("    Listar Edificios                        (Pulsar L)\n");
    printf("    Apartamentos Disponibles                (Pulsar A)\n");
    printf("    Reservar Apartamento                    (Pulsar R)\n");
    printf("    Reservas Mensuales Apartamento          (Pulsar M)\n");
    printf("    Salir                                   (Pulsar S)\n");
    printf("\n");
    printf("Teclear una opcion valida (E|L|A|R|M|S)?\n");
    scanf("%c", &option);

    return option;
};

void editBuilding() {
    printf("Editar Edificio:\n");
    printf("\n");
    printf("Identificador (número entre 1 y 5)?\n");
    printf("Nombre (entre 1 y 20 caracteres)?\n");
    printf("Número de Apartamentos Básicos?");
    printf("Número de Apartamentos Normales?");
    printf("Número de Apartamentos de Lujo?");
    printf("\n");
    printf("IMPORTANTE: Esta opción borra los datos anteriores.\nSon correctos los nuevos datos (S/N)?");
};

void listBuildings() {
    printf("Id   Nombre  Aptos Basicos  Aptos Normales  Aptos Lujo\n");
    printf("1   Neptuno       10              5              2\n");
    printf("3   Apolo         15              8              3\n");
    printf("4   Zeus          20             10              4\n");
    printf("5   Atenea        25             12              5\n");
};

void availableApartments() {
    printf("Apartamentos Disponibles:\n");
    printf("    Identificador Edificio?\n");
    printf("    Fecha de Entrada: Dia?\n");
    printf("    Fecha de Entrada: Mes?\n");
    printf("    Fecha de Entrada: Año?\n");
    printf("    Dias de duracion de la estancia?\n");
    printf("\n");
    printf("El edificio Apolo desde el 8/9/2025 y 15 días de estancia, tendría disponibles:\n");
    printf("\n");
    printf("4 apartamentos básicos\n");
    printf("2 apartamentos normales\n");
    printf("1 apartamento de lujo\n");
};

void reserveApartment() {
    printf("Reservar Apartamento:\n");
    printf("\n");
    printf("    Identificador Edificio?\n");
    printf("    Tipo de Apartamento (B-Basico|N-Normal|L-Lujo)?\n");
    printf("    Fecha de Entrada: Dia?\n");
    printf("    Fecha de Entrada: Mes?\n");
    printf("    Fecha de Entrada: Año?\n");
    printf("    Dias de duracion de la estancia?\n");
    printf("\n");
    printf("        Datos de reserva");
    printf("\n");
    printf("    Numero de Reserva: 34/2025\n");
    printf("    Edificio: Apolo\n");
    printf("    Referencia Apartamento:\n");
    printf("    Fecha Entrada:\n");
    printf("    Duracion estancia:\n");
    printf("    Fecha salida:\n");
    printf("\n");
    printf("Es correcta la operacion? (S/N)?\n");
};

void monthlyReservations() {
    printf("Reservas Mensuales Apartamento:\n");
    printf("\n");
    printf("    Referencia Apartamento ?\n");
    printf("    Selección Mes?\n");
    printf("    Selección Año?\n");
    printf("\n");
    printf("    Estado Mensual Apartamento:\n");
    printf("        Edificion:\n");
    printf("\n");
    printf("Reserva 21/2025: Fecha entrada 27/8/2025 y de 10 días\n");
    printf("Reserva 21/2025: Fecha entrada 27/8/2025 y de 10 días\n");
    printf("Reserva 21/2025: Fecha entrada 27/8/2025 y de 10 días\n");
    printf("Total días reservados del mes: xx dias\n");
    printf("Total días libres del mes: xx dias\n");
    printf("\n");
    printf("Mostrar otro mes (S/N)?\n");
};