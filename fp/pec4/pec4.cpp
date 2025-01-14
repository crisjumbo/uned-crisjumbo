#include <stdio.h>
#include <string.h>

const int MAX_BUILDINGS = 5;
const int MAX_APPARMENTS = 20;
const int MAX_CHARACTERS = 20;

typedef char String[MAX_CHARACTERS];

typedef enum Months {Enero, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre};

typedef struct BuildingType{
    int buildingId;
    String buildingName;
    int basicApartments;
    int normalApartments;
    int luxuryApartments;
    bool isEmpty;
};

typedef BuildingType Buildings[MAX_BUILDINGS];

typedef struct AvalabilityApartmentType {
  int buildingId;
  int entranceDay;
  int entranceMonth;
  int entranceYear;
  int stanceDays;
};

typedef struct ReservationType {
  int reservationId;
  int buildingId;
  char apartmentType;
  int entranceDay;
  int entranceMonth;
  int entranceYear;
  int stanceDays;
  ReservationType *next;
};

typedef struct DateType {
  int day;
  int month;
  int year;
};

/**TAD**/
typedef struct MonthCalendar {
  int month;
  int year;
  String apartmentRef;
};

/********** Methods *********/

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
}

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
    printf("    Fecha de Entrada: A�o?");
    scanf("%d", &year);
    printf("    Dias de duracion de la estancia?");
    scanf("%d", &stayDays);
    printf("\n");
    printf("El edificio Apolo desde el 8/9/2025 y 15 d�as de estancia, tendr�a disponibles:\n");
    printf("\n");
    printf("4 apartamentos b�sicos\n");
    printf("2 apartamentos normales\n");
    printf("1 apartamento de lujo\n");
}

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
    printf("    Fecha de Entrada: A�o?");
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
}

void monthlyReservations() {
    char showAnotherMonth;
    int buildingId;
    int month;
    int year;

    printf("\nReservas Mensuales Apartamento:\n");
    printf("\n");
    printf("    Referencia Apartamento ?");
    scanf("%d", &buildingId);
    printf("    Selecci�n Mes?");
    scanf("%d", &month);
    printf("    Selecci�n A�o?");
    scanf("%d", &year);
    printf("\n");
    printf("    Estado Mensual Apartamento:\n");
    printf("        Edificion:\n");
    printf("\n");
    printf("Reserva 21/2025: Fecha entrada 27/8/2025 y de 10 d�as\n");
    printf("Reserva 21/2025: Fecha entrada 27/8/2025 y de 10 d�as\n");
    printf("Reserva 21/2025: Fecha entrada 27/8/2025 y de 10 d�as\n");
    printf("Total d�as reservados del mes: xx dias\n");
    printf("Total d�as libres del mes: xx dias\n");
    printf("\n");
    printf("Mostrar otro mes (S/N)?\n");
    scanf(" %c", &showAnotherMonth);
}

void addBuilding(BuildingNode head, BuildingType building) {
    BuildingNode newNode, current;
    int apartmentsBuilding = building.basicApartments + building.normalApartments + building.luxuryApartments;
    int apartmentsBuildings = 0;
    int totalApartments = 0;
    int i = 0;
    int j = 0;

//count total appartments
    *current = *head;
    while(current != NULL) {
        apartmentsBuildings = apartmentsBuildings + (current->building.basicApartments + current->building.normalApartments + current->building.luxuryApartments);
        current = current->next;
        i++;
    };
    totalApartments = apartmentsBuilding + apartmentsBuildings;
    free(current);

//condition if there is full capacity
    if (totalApartments > 20 || i == 5) {
        printf("Full capacity, please remove or edit building\n");
        return;
    };

//add building to the linked list
    newNode = new Node;
    newNode->building = building;
    newNode->next = NULL;
    newNode->prev = NULL;

    if(head == NULL) {
        *head = *newNode;
        free(newNode);
    } else {
        *current = *head;
        while(current->next != NULL) {
            if(current->building.buildingId == building.buildingId) {
                current->building = building;
                free(newNode);
                return;
            };
            current = current->next;
        };
        if (current->building.buildingId != building.buildingId) {
            current->next = newNode;
            newNode->prev = current;
            free(newNode);
        };

        free(current);
    };
}

void getBuildings(BuildingNode head) {
    BuildingNode current;

    *current = *head;
    while(current != NULL) {
        printf("\nId   Nombre  Aptos Basicos  Aptos Normales  Aptos Lujo\n");
        printf(" %d   ", current->building.buildingId);
        printf("%s   ", current->building.buildingName);
        printf(" %d   ", current->building.basicApartments);
        printf(" %d   ", current->building.normalApartments);
        printf(" %d   ", current->building.luxuryApartments);
        current = current->next;
    };
    delete current;
}

void listBuildings(BuildingNode head) {
    printf("\nId   Nombre  Aptos Basicos  Aptos Normales  Aptos Lujo\n");
    getBuildings(head);
}

void editBuilding(BuildingNode head) {
    BuildingType building;
    char correctData;

    printf("\nEditar Edificio:\n");
    printf("\n");
    printf("Identificador (n�mero entre 1 y 5)?");
    scanf("%d", &building.buildingId);
    printf("Nombre (entre 1 y 20 caracteres)?");
    scanf("%s", building.buildingName);
    printf("N�mero de Apartamentos B�sicos?");
    scanf("%d", &building.basicApartments);
    printf("N�mero de Apartamentos Normales?");
    scanf("%d", &building.normalApartments);
    printf("N�mero de Apartamentos de Lujo?");
    scanf("%d", &building.luxuryApartments);
    printf("\n");
    printf("IMPORTANTE: Esta opci�n borra los datos anteriores.\n");
    printf("Son correctos los nuevos datos (S/N)?");
    scanf(" %c", &correctData);

    if(correctData == 'S') {
        addBuilding(head, building);
    };
}

void renderOption(char option, BuildingNode head) {
    switch(option) {
        case 'E':
            editBuilding(head);
            break;
        case 'L':
            listBuildings(head);
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
            printf("Opci�n no v�lida\n");
    }
}

/********** UI Panel **********/
int main() {
    char option;
    BuildingNode head;
    head = NULL;

    do {
        option = renderMenu();
        renderOption(option, head);
    } while(option != 'S');

    return 0;
}

