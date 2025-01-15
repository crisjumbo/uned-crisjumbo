#include <stdio.h>
#include <string.h>
#include "practica_4.h"

int reservationId = 0;

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

int checkApartmentsAvailability(BuildingType building, char apartment) {
  int apartmentsAvailable;

  switch(apartment){
    case 'B':
    apartmentsAvailable = building.basicApartments;
    break;
    case 'N':
    apartmentsAvailable = building.normalApartments;
    break;
    case 'L':
    apartmentsAvailable = building.luxuryApartments;
    break;
    default:
    apartmentsAvailable = 0;
  }

  return apartmentsAvailable;
}

bool isLeapYear(int year) {
  if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){
    return true;
  }
  return false;
}

int daysInMonth(int month) {
  switch(month){
    case 1:
    return 28;
    break;
    case 3:
    case 5:
    case 8:
    case 10:
    return 30;
    break;
    default:
    return 31;
  }
}

DateType getExitDate(DateType date, int stanceDays){
  DateType exitDate;
  bool isLeap;
  int days;
  int daysCount;
  int month;

  isLeap = isLeapYear(date.year);
  days = 0;
  daysCount = 0;
  exitDate.day = 0;
  exitDate.month = 0;
  exitDate.year = date.year;

  for(int i = 0; i < (date.month - 1); i++) { // days till last day of previous month
    days = days + daysInMonth(i);
  }
  days = date.day + stanceDays;

  for(int i = 0; i < MONTHS_IN_YEAR; i++) {
    daysCount = daysCount + daysInMonth(i);
    if( days < daysCount) {
      daysCount = daysCount - daysInMonth(i);
      exitDate.day = days - daysCount;
      exitDate.month = i + 1;
      exitDate.year = date.year;

      return exitDate;
    }
  }

  return exitDate;
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

void renderAvailability(Buildings &buildings, DateType entranceDate,int stanceDays, int buildingId) {
  int availableNormalApartments;
  int availableBasicApartments;
  int availableLuxuryApartments;

  for(int i = 0; i < MAX_APPARMENTS; i++){
    if(buildings[i].buildingId == buildingId){
      availableBasicApartments = checkApartmentsAvailability(buildings[i], 'B');
      availableNormalApartments = checkApartmentsAvailability(buildings[i], 'N');
      availableLuxuryApartments = checkApartmentsAvailability(buildings[i], 'L');

      printf("El edificio %s desde el %d/%d/%d y %d dias de estancia, tendria disponibles:\n", buildings[i].buildingName, entranceDate.day, entranceDate.month, entranceDate.year, stanceDays );
      printf("\n");
      printf("%d apartamentos basicos\n", availableBasicApartments);
      printf("%d apartamentos normales\n", availableNormalApartments);
      printf("%d apartamento de lujo\n", availableLuxuryApartments);
    }
  }
}

void renderReservationInfo(DateType exitDate, ReservationType reservation, Buildings &buildings, ReservationHead &head) {
    char correctData;
    ReservationHead aux;

    reservation.next = NULL;
    aux = head;
    printf("        Datos de reserva");
    printf("\n");
    printf("    Numero de Reserva: %d/%d\n", reservationId + 1 ,reservation.entranceDate.year);
    printf("    Edificio: %s\n", buildings[reservation.buildingId - 1].buildingName);
    printf("    Referencia Apartamento:\n");
    printf("    Fecha Entrada: %d/%d/%d\n", reservation.entranceDate.day, reservation.entranceDate.month, reservation.entranceDate.year);
    printf("    Duracion estancia: %d\n", reservation.stanceDays);
    printf("    Fecha salida: %d/%d/%d\n", exitDate.day, exitDate.month, exitDate.year);
    printf("\n");
    printf("Es correcta la operacion? (S/N)?\n");
    scanf(" %c", &correctData);
    fflush(stdin);

    if(correctData == 'S') {
      reservationId = reservationId + 1;

      if(head == NULL) {
        *head = reservation;
      }
      while(aux != NULL) {
        aux = head->next;
        if(head->next != NULL) {
          head->next = &reservation;
        }
      }
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
    fflush(stdin);

    return option;
}

/** Render Available Apartments **/
void availableApartments(Buildings &buildings) {
    int buildingId,stanceDays;
    DateType entranceDate;

    printf("\nApartamentos Disponibles:\n");
    printf("    Identificador Edificio?");
    scanf("%d", &buildingId);
    fflush(stdin);
    printf("    Fecha de Entrada: Dia?");
    scanf("%d", &entranceDate.day);
    fflush(stdin);
    printf("    Fecha de Entrada: Mes?");
    scanf("%d", &entranceDate.month);
    fflush(stdin);
    printf("    Fecha de Entrada: Annio?");
    scanf("%d", &entranceDate.year);
    fflush(stdin);
    printf("    Dias de duracion de la estancia?");
    scanf("%d", &stanceDays);
    fflush(stdin);
    printf("\n");
    renderAvailability(buildings, entranceDate, stanceDays, buildingId);
}

/** Render Reserve Apartment **/
void reserveApartment(Buildings &buildings, ReservationHead &head) {
    ReservationType reservation;
    int totalAvailableApartments;
    char correctData;
    DateType exitDate;

    printf("\nReservar Apartamento:\n");
    printf("\n");
    printf("    Identificador Edificio?");
    scanf("%d", &reservation.buildingId);
    fflush(stdin);
    printf("    Tipo de Apartamento (B-Basico|N-Normal|L-Lujo)?");
    scanf(" %c", &reservation.apartmentType);
    fflush(stdin);
    printf("    Fecha de Entrada: Dia?");
    scanf("%d", &reservation.entranceDate.day);
    fflush(stdin);
    printf("    Fecha de Entrada: Mes?");
    scanf("%d", &reservation.entranceDate.month);
    fflush(stdin);
    printf("    Fecha de Entrada: Annio?");
    scanf("%d", &reservation.entranceDate.year);
    fflush(stdin);
    printf("    Dias de duracion de la estancia?");
    scanf("%d", &reservation.stanceDays);
    fflush(stdin);
    printf("\n");

    totalAvailableApartments = checkApartmentsAvailability(buildings[reservation.buildingId - 1], 'B');
    totalAvailableApartments = totalAvailableApartments + checkApartmentsAvailability(buildings[reservation.buildingId - 1], 'N');
    totalAvailableApartments = totalAvailableApartments + checkApartmentsAvailability(buildings[reservation.buildingId - 1], 'L');
    exitDate = getExitDate(reservation.entranceDate, reservation.stanceDays);

    if(totalAvailableApartments == 0) {
      printf("No hay apartamentos disponibles!");
    } else {
      renderReservationInfo(exitDate, reservation, buildings, head);
    }
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
    fflush(stdin);
    printf("    Seleccion Mes?");
    scanf("%d", &month);
    fflush(stdin);
    printf("    Seleccion Annio?");
    scanf("%d", &year);
    fflush(stdin);
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
    fflush(stdin);
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
    fflush(stdin);
    printf("Nombre (entre 1 y 20 caracteres)?");
    scanf("%s", building.buildingName);
    fflush(stdin);
    printf("Numero de Apartamentos Basicos?");
    scanf("%d", &building.basicApartments);
    fflush(stdin);
    printf("Numero de Apartamentos Normales?");
    scanf("%d", &building.normalApartments);
    fflush(stdin);
    printf("Numero de Apartamentos de Lujo?");
    scanf("%d", &building.luxuryApartments);
    fflush(stdin);
    printf("\n");
    printf("IMPORTANTE: Esta opcion borra los datos anteriores.\n");
    printf("Son correctos los nuevos datos (S/N)?");
    scanf(" %c", &correctData);
    fflush(stdin);

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
void renderOption(char option, Buildings &buildings, ReservationHead &head) {
    switch(option) {
        case 'E':
            editBuilding(buildings);
            break;
        case 'L':
            listBuildings(buildings);
            break;
        case 'A':
            availableApartments(buildings);
            break;
        case 'R':
            reserveApartment(buildings, head);
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
    ReservationHead head;

    head = NULL;
    initializeBuildings(buildings);
    do {
        option = renderMenu();
        renderOption(option, buildings, head);
    } while(option != 'S');

    return 0;
}
