#include <stdio.h>

char renderMenu();
void editBuilding(Node **head);
void listBuildings();
void availableApartments();
void reserveApartment();
void monthlyReservations();
void renderOption(char option, Node **head);
void addBuilding(Node **head, Building building);

typedef struct Building{
    int buildingId;
    char buildingName[20];
    int basicApartments;
    int normalApartments;
    int luxuryApartments;
} Building;

//add previous Node to free at the end of program
typedef struct Node {
    Building building;
    struct Node *next;
} Node;

const MAX_BUILDINGS = 5;
const MAX_APPARMENTS = 20;
const IS_TRUE = 1;
const IS_FALSE = 0;

int main() {
    char option;
    Node *head = NULL;

    do {
        option = renderMenu();
        renderOption(option, &head);
    } while(option != 'S');

    return 0;
};

void renderOption(char option, Node **head) {
    switch(option) {
        case 'E':
            editBuilding(head);
            break;
        case 'L':
            listBuildings();
            break;
        case 'A':
            availableApartments();
            break;
        case 'R':
            reserveApartment();
            break;
        case 'M':
            monthlyReservations();
            break;
        case 'S':
            break;
        default:
            printf("Opción no válida\n");
            break;
    }
};

char renderMenu() {
    char option;

    printf("\nGesRAE: Gestion de Reservas Apartamentos-Edificios\n");
    printf("\n");
    printf("    Editar Edificion                        (Pulsar E)\n");
    printf("    Listar Edificios                        (Pulsar L)\n");
    printf("    Apartamentos Disponibles                (Pulsar A)\n");
    printf("    Reservar Apartamento                    (Pulsar R)\n");
    printf("    Reservas Mensuales Apartamento          (Pulsar M)\n");
    printf("    Salir                                   (Pulsar S)\n");
    printf("\n");
    printf("Teclear una opcion valida (E|L|A|R|M|S)?");
    scanf(" %c", &option);

    return option;
};

void editBuilding(Node **head) {
    Building building;
    char correctData;

    printf("\nEditar Edificio:\n");
    printf("\n");
    printf("Identificador (número entre 1 y 5)?");
    scanf("%d", &building.buildingId);
    printf("Nombre (entre 1 y 20 caracteres)?");
    scanf("%s", building.buildingName);
    printf("Número de Apartamentos Básicos?");
    scanf("%d", &building.basicApartments);
    printf("Número de Apartamentos Normales?");
    scanf("%d", &building.normalApartments);
    printf("Número de Apartamentos de Lujo?");
    scanf("%d", &building.luxuryApartments);
    printf("\n");
    printf("IMPORTANTE: Esta opción borra los datos anteriores.\n");
    printf("Son correctos los nuevos datos (S/N)?");
    scanf(" %c", &correctData);

    if(correctData == 'S') {
        addBuilding(head, building);
    };
};

void listBuildings() {
    printf("\nId   Nombre  Aptos Basicos  Aptos Normales  Aptos Lujo\n");
    printf("1   Neptuno       10              5              2\n");
    printf("3   Apolo         15              8              3\n");
    printf("4   Zeus          20             10              4\n");
    printf("5   Atenea        25             12              5\n");
};

void availableApartments() {
    int buildingId;
    int day;
    int month;
    int year;
    int stayDays;

    printf("\nApartamentos Disponibles:\n");
    printf("    Identificador Edificio?");
    scanf("%d", &buildingId);
    printf("    Fecha de Entrada: Dia?");
    scanf("%d", &day);
    printf("    Fecha de Entrada: Mes?");
    scanf("%d", &month);
    printf("    Fecha de Entrada: Año?");
    scanf("%d", &year);
    printf("    Dias de duracion de la estancia?");
    scanf("%d", &stayDays);
    printf("\n");
    printf("El edificio Apolo desde el 8/9/2025 y 15 días de estancia, tendría disponibles:\n");
    printf("\n");
    printf("4 apartamentos básicos\n");
    printf("2 apartamentos normales\n");
    printf("1 apartamento de lujo\n");
};

void reserveApartment() {
    int buildingId;
    char apartmentType;
    char correctData;
    int entryDay;
    int entryMonth;
    int entryYear;
    int stayDays;

    printf("\nReservar Apartamento:\n");
    printf("\n");
    printf("    Identificador Edificio?");
    scanf("%d", &buildingId);
    printf("    Tipo de Apartamento (B-Basico|N-Normal|L-Lujo)?");
    scanf(" %c", &apartmentType);
    printf("    Fecha de Entrada: Dia?");
    scanf("%d", &entryDay);
    printf("    Fecha de Entrada: Mes?");
    scanf("%d", &entryMonth);
    printf("    Fecha de Entrada: Año?");
    scanf("%d", &entryYear);
    printf("    Dias de duracion de la estancia?");
    scanf("%d", &stayDays);
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
    scanf(" %c", &correctData);
};

void monthlyReservations() {
    char showAnotherMonth;
    int buildingId;
    int month;
    int year;

    printf("\nReservas Mensuales Apartamento:\n");
    printf("\n");
    printf("    Referencia Apartamento ?");
    scanf("%d", &buildingId);
    printf("    Selección Mes?");
    scanf("%d", &month);
    printf("    Selección Año?");
    scanf("%d", &year);
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
    scanf(" %c", &showAnotherMonth);
};

void addBuilding(Node **head, Building building) {
    int apartmentsBuilding = building.basicApartments + building.normalApartments + building.luxuryApartments;
    int apartmentsBuildings = 0;
    int totalApartments = 0;
    int i = 0;
    int j = 0;

//count total appartments
    Node *current = *head;
    while(current != NULL) {
        apartmentsBuildings += current->building.basicApartments + current->building.normalApartments + current->building.luxuryApartments;
        current = current->next;
        i++;
    };
    totalApartments = apartmentsBuilding + apartmentsBuildings;

//condition if there is full capacity
    if (totalApartments > 20 || i == 5) {
        printf("Full capacity, please remove or edit building\n");
        return;
    };

//add building to the linked list
};