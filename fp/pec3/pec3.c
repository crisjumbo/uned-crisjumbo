#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isLeapYear(int year);
void printDay(int dayWeek, int dayNumber);
void printTwoDigitDay(int dayWeek, int dayNumber);
void printCalendarHeader(char *month, int year);
void printEmptyDay(int dayWeek);
int calculateDays(int year, int month, int daysInMonth[]);

typedef enum dayType {Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo};
typedef enum monthType {Enero, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre};


int main() {
    char monthInYear[12][20] = {"JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"};
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char daysInWeek[7][1] = {"L","M","X","J","V","S","D"};
    int selectedMonth;
    int daysInSelectedMonth = 0;
    int firstDay = 0;
    int isLeap = 0;
    char month[10];
    int year;
    int days = 0;

    printf("¿Mes (1..12)?)");
    scanf("%d", &selectedMonth);
    selectedMonth--;
    printf("¿Año (1601..3000)?");
    scanf("%d", &year);
    isLeap = isLeapYear(year);

    if (year < 1601 || year > 3000) {
        return 0;
    }

    days = calculateDays(year, selectedMonth, daysInMonth);

    if(isLeap && selectedMonth == 1) {
        daysInSelectedMonth = daysInMonth[selectedMonth] + 1;
    } else {
        daysInSelectedMonth = daysInMonth[selectedMonth];
    }

    // Day of the week that the month start
    char dayOfWeek = daysInWeek[days % 7][0];
    int weeks;
    if (((days % 7) + daysInSelectedMonth ) % 7 == 0) {
        weeks = ((days % 7) + daysInSelectedMonth ) / 7;
    } else {
        weeks = ((days % 7) + daysInSelectedMonth ) / 7 + 1;
    }


    printCalendarHeader(month, year);
    for(int i = 0; i < weeks; i++) {
        for(int j = 0; j < 7; j++) {
            if (dayOfWeek == daysInWeek[j][0] && firstDay < daysInSelectedMonth) {
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
};

int isLeapYear(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
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
};

void printCalendarHeader(char *month, int year) {
    int total_width = 28;
    int month_length = strlen(month);
    int year_length = snprintf(NULL, 0, "%d", year);
    int spaces = total_width - month_length - year_length - 1;

    printf("\n");
     printf("%s", month);
     for (int i = 0; i < spaces; i++) {
         printf(" ");
     }
     printf("%d\n", year);
     printf("===========================\n");
     printf("LU  MA  MI  JU  VI | SA  DO\n");
     printf("===========================\n");
};

int calculateDays(int year, int month, int daysInMonth[]) {
    int days = 0;
    // Days till 31th of December of the selected year
    for(int i = 1601; i < year; i++) {
        if (isLeapYear(i) == 1) {
            days += 366;
        } else {
            days += 365;
        }
    }

    for(int i = 0; i <= month; i++) {
        if(isLeapYear(year) == 1 && i == 1) {
            days += daysInMonth[i] + 1;
        } else {
            days += daysInMonth[i];
        }
    }

    // Days till previous day of the selected month
    if (isLeapYear(1) == 1 && month == 1) {
        days -= daysInMonth[month] + 1;
    } else {
        days -= daysInMonth[month];
    }

    return days;
}
