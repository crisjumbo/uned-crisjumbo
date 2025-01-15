#pragma once

const int MAX_BUILDINGS = 5;
const int MAX_APPARMENTS = 20;
const int MAX_CHARACTERS = 20;
const int BUILDING_PROPS = 5;
const int MONTHS_IN_YEAR = 12;

extern int reservationId;

typedef char String[MAX_CHARACTERS];

typedef enum Months {Enero, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre};
typedef enum WeekDays {Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo};
typedef enum ApartmentService {B, L, N};

typedef struct DateType {
  int day;
  int month;
  int year;
};

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
  DateType entranceDate;
  int stanceDays;
};

typedef struct ReservationType {
  int reservationId;
  int buildingId;
  char apartmentType;
  DateType entranceDate;
  int stanceDays;
  ReservationType *next;
};

typedef ReservationType *ReservationHead;

typedef struct ApartmentType {
  String apartmentRef;
  ApartmentService type;
  bool available;

  ApartmentType *next;
};

typedef ApartmentType *ApartmentHead;

/** TAD **/
typedef struct MonthCalendar {
  int month;
  int year;
  String apartmentRef;
};
