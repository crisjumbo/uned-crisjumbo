const int MAX_BUILDINGS = 5;
const int MAX_APPARMENTS = 20;
const int MAX_CHARACTERS = 20;
const int BUILDING_PROPS = 5;

typedef char String[MAX_CHARACTERS];

typedef enum Months {Enero, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre};
typedef enum WeekDays {Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo};

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

/** TAD **/
typedef struct MonthCalendar {
  int month;
  int year;
  String apartmentRef;
};