#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum dayType {Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo};
typedef enum monthType {Enero, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre};
const int START_YEAR = 1601;

int isLeapYear(int year) {
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}

void printDay(int dayWeek, int dayNumber) {
    switch(dayWeek) {
        case 0:
            printf(" %d", dayNumber);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            printf("   %d", dayNumber);
            break;
        case 5:
            printf(" |  %d", dayNumber);
            break;
        case 6:
            printf("   %d", dayNumber);
            break;
    }
}

void printTwoDigitDay(int dayWeek, int dayNumber) {
    switch(dayWeek) {
        case 0:
            printf("%d", dayNumber);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            printf("  %d", dayNumber);
            break;
        case 5:
            printf(" | %d", dayNumber);
            break;
        case 6:
            printf("  %d", dayNumber);
            break;
    }
}

void printEmptyDay(int dayWeek) {
    switch(dayWeek) {
        case 0:
            printf(" .");
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            printf("   .");
            break;
        case 5:
            printf(" |  .");
            break;
        case 6:
            printf("   .");
            break;
    }
}

void printTheMonth(monthType month) {
  switch(month){
    case Enero:
    printf("ENERO                  ");
    break;
    case Febrero:
    printf("FEBRERO                ");
    break;
    case Marzo:
    printf("MARZO                  ");
    break;
    case Abril:
    printf("ABRIL                  ");
    break;
    case Mayo:
    printf("MAYO                   ");
    break;
    case Junio:
    printf("JUNIO                  ");
    break;
    case Julio:
    printf("JULIO                  ");
    break;
    case Agosto:
    printf("AGOSTO                 ");
    break;
    case Septiembre:
    printf("SEPTIEMBRE             ");
    break;
    case Octubre:
    printf("OCTUBRE                ");
    break;
    case Noviembre:
    printf("NOVIEMBRE              ");
    break;
    default:
    printf("DICIEMBRE              ");
  }
}

void printCalendarHeader(monthType month, int year) {
    printf("\n");
    printTheMonth(month);
    printf("%d\n", year);
    printf("===========================\n");
    printf("LU  MA  MI  JU  VI | SA  DO\n");
    printf("===========================\n");
}

int daysInMonth (int monthN) {
  switch(monthN){
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

int calculateDays(int year, int month) {
    int days = 0;
    // Days till 31th of December of the selected year
    for(int i = START_YEAR; i < year; i++){
        if (isLeapYear(i) == 1) {
            days = days + 366;
        } else {
            days = days + 365;
        }
    }

    // Days till the last day of the selected month
    for(int i = 0; i <= month; i++) {
        if(isLeapYear(year) == 1 && i == 1) {
            days = days + daysInMonth(i) + 1;
        } else {
            days = days + daysInMonth(i);
        }
    }

    // Days till previous day of the selected month
    if (isLeapYear(year) == 1 && month == 1) {
        days = days - daysInMonth(month) - 1;
    } else {
        days = days - daysInMonth(month);
    }

    return days;
}

char daysInWeek(int dayN) {
  switch(dayN){
    case 0:
    return 'L';
    break;
    case 1:
    return 'M';
    break;
    case 2:
    return 'X';
    break;
    case 3:
    return 'J';
    break;
    case 4:
    return 'V';
    break;
    case 5:
    return 'S';
    break;
    default:
    return 'D';
  }
}

int main() {
    int selectedMonth;
    int daysInSelectedMonth = 0;
    int firstDay = 0;
    int isLeap = 0;
    int year;
    int weeks;
    int days = 0;
    char dayOfWeek;

    printf("¿Mes (1..12)?)");
    scanf("%d", &selectedMonth);
    selectedMonth--;
    printf("¿Año (1601..3000)?");
    scanf("%d", &year);
    isLeap = isLeapYear(year);

    if (year < 1601 || year > 3000 || selectedMonth < 0 || selectedMonth > 11) {
        return 0;
    }

    days = calculateDays(year, selectedMonth);

    if(isLeap && selectedMonth == 1) {
        daysInSelectedMonth = daysInMonth(selectedMonth) + 1;
    } else {
        daysInSelectedMonth = daysInMonth(selectedMonth);
    }

    // Day of the week that the month start
    dayOfWeek = daysInWeek(days % 7);

    if (((days % 7) + daysInSelectedMonth ) % 7 == 0) {
        weeks = ((days % 7) + daysInSelectedMonth ) / 7;
    } else {
        weeks = ((days % 7) + daysInSelectedMonth ) / 7 + 1;
    }


    printCalendarHeader(monthType(selectedMonth), year);
    for(int i = 0; i < weeks; i++) {
        for(int j = 0; j < 7; j++) {
            if (dayOfWeek == daysInWeek(j) && firstDay < daysInSelectedMonth) {
                firstDay++;
                if (firstDay / 10 == 0) {
                    printDay(j, firstDay);
                } else {
                    printTwoDigitDay(j,firstDay);
                }
            } else {
                if (firstDay != 0 && firstDay < daysInSelectedMonth) {
                firstDay++;
                    if (firstDay / 10 == 0) {
                        printDay(j, firstDay);
                    } else {
                        printTwoDigitDay(j,firstDay);
                    }
                } else {
                    printEmptyDay(j);
                }
            }
        };
        printf("\n");
    };

    return 0;
}