#include <stdio.h>
#include <string.h>
#include "pec4.h"

/********** Util Methods *********/
bool isBuildingEmpty(BuildingType building) {
  int totalApartments;

  totalApartments = building.basicApartments + building.normalApartments + building.luxuryApartments;
  if(totalApartments < 1){
    return true;
  } else {
    return false;
  }
}

bool throwBuildingError(BuildingType building) {
  int totalApartments;

  totalApartments = building.basicApartments + building.normalApartments + building.luxuryApartments;
  if(totalApartments > MAX_APPARMENTS){
    return true;
  } else {
    return false;
  }
}

/********** Help Methods *********/
void deleteBuilding(Buildings &buildings, int buildingId) {
    for(int i = 0; i < MAX_APPARMENTS; i++) {
    if (buildings[i].buildingId == buildingId) {
      buildings[i].buildingId = buildingId;
      buildings[i].isEmpty = true;
      strcpy(buildings[i].buildingName, "");
      buildings[i].basicApartments = 0;
      buildings[i].normalApartments = 0;
      buildings[i].luxuryApartments = 0;
    }
  }
}

void addBuilding(Buildings &buildings, BuildingType building) {
  for(int i = 0; i < MAX_APPARMENTS; i++) {
    if (buildings[i].buildingId == building.buildingId) {
      buildings[i].buildingId = building.buildingId;
      buildings[i].isEmpty = false;
      strcpy(buildings[i].buildingName,building.buildingName);
      buildings[i].basicApartments = building.basicApartments;
      buildings[i].normalApartments = building.normalApartments;
      buildings[i].luxuryApartments = building.luxuryApartments;
    }
  }
}

void renderBuildings(Buildings &buildings) {
    for(int i = 0; i < MAX_BUILDINGS; i++) {
      for(int j = 0; j < BUILDING_PROPS; j++) {
        if(!buildings[i].isEmpty) {
          switch(j) {
            case 0:
            printf(" %d ", buildings[i].buildingId);
            break;
            case 1:
            printf(" %s ", buildings[i].buildingName);
            break;
            case 2:
            printf(" %d ", buildings[i].basicApartments);
            break;
            case 3:
            printf(" %d ", buildings[i].normalApartments);
            break;
            default:
            printf(" %d ", buildings[i].luxuryApartments);
          }
        }
      }
      printf("\n");
    }
}

void initializeBuildings(Buildings & buildings) {
  for(int i = 0; i < MAX_BUILDINGS; i++) {
    buildings[i].buildingId = i + 1;
    buildings[i].isEmpty = true;
    strcpy(buildings[i].buildingName, "");
    buildings[i].basicApartments = 0;
    buildings[i].normalApartments = 0;
    buildings[i].luxuryApartments = 0;
  }
}

/********** Core Methods *********/

/** Render Home Header **/
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

/** Render Available Apartments **/
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
    printf("    Fecha de Entrada: Annio?");
    scanf("%d", &year);
    printf("    Dias de duracion de la estancia?");
    scanf("%d", &stayDays);
    printf("\n");
    printf("El edificio Apolo desde el 8/9/2025 y 15 dias de estancia, tendr�a disponibles:\n");
    printf("\n");
    printf("4 apartamentos basicos\n");
    printf("2 apartamentos normales\n");
    printf("1 apartamento de lujo\n");
}

/** Render Reserve Apartment **/
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
    printf("    Fecha de Entrada: Annio?");
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

/** Render Month Reservation **/
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

/** Render List Of Buildings **/
void listBuildings(Buildings &buildings) {
    printf("\nId   Nombre  Aptos Basicos  Aptos Normales  Aptos Lujo\n");
    renderBuildings(buildings);
}

/** Render Edit Building **/
void editBuilding(Buildings &buildings) {
    BuildingType building;
    char correctData;
    bool toDeleteBuilding;
    bool buildingError;

    printf("\nEditar Edificio:\n");
    printf("\n");
    printf("Identificador (numero entre 1 y 5)?");
    scanf("%d", &building.buildingId);
    printf("Nombre (entre 1 y 20 caracteres)?");
    scanf("%s", building.buildingName);
    printf("Numero de Apartamentos Basicos?");
    scanf("%d", &building.basicApartments);
    printf("Numero de Apartamentos Normales?");
    scanf("%d", &building.normalApartments);
    printf("Numero de Apartamentos de Lujo?");
    scanf("%d", &building.luxuryApartments);
    printf("\n");
    printf("IMPORTANTE: Esta opcion borra los datos anteriores.\n");
    printf("Son correctos los nuevos datos (S/N)?");
    scanf(" %c", &correctData);

    toDeleteBuilding = isBuildingEmpty(building);
    buildingError = throwBuildingError(building);
    if(correctData == 'S') {
      if(toDeleteBuilding) {
        deleteBuilding(buildings, building.buildingId);
      } else if (buildingError) {
        printf("No se pudo anniadir el Edificio");
      } else {
        addBuilding(buildings, building);
      }
    };
}

/** Render Home Panel **/
void renderOption(char option, Buildings &buildings) {
    switch(option) {
        case 'E':
            editBuilding(buildings);
            break;
        case 'L':
            listBuildings(buildings);
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
            printf("Opcion no valida\n");
    }
}

/********** UI Panel **********/
int main() {
    char option;
    Buildings buildings;

    initializeBuildings(buildings);
    do {
        option = renderMenu();
        renderOption(option, buildings);
    } while(option != 'S');

    return 0;
}
