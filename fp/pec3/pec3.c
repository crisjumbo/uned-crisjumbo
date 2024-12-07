#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int year;
    char month[10];
    int selectedMonth;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char monthInYear[12][20] = {"january","february","march","april","may","june","july","august","september","october","november","december"};
    char daysInWeek[7][1] = {"L","M","X","J","V","S","D"};
    int days;
    int firstDay = 0;
    int isLeap = 0;

    printf("¿Mes (1..12)?)");
    scanf("%s", month);
    printf("¿Año (1601..3000)?");
    scanf("%d", &year);

    if (year < 1601 || year > 3000) {
        return 0;
    }

    // Days till 31th of December of the selected year
    for(int i = 1601; i <= year; i++) {
        if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) {
            days += 366;
        } else {
            days += 365;
        }
    }

    // Days till 31th of December of previous year
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        isLeap = 1;
        days -= 366;
    } else {
        days -= 365;
    }

    // Days till the selected month
    for(int i = 0; i < 12; i++) {
        if (strcmp(month, monthInYear[i]) == 0) {
            selectedMonth = i;
            break;
        }
        
    };
    for(int i = 0; i <= selectedMonth; i++) {
        if(isLeap && i == 1) {
            days += daysInMonth[i] + 1;
        } else {
            days += daysInMonth[i];
        }
    }

    // Days till previous day of the selected month
    int daysInSelectedMonth;
    if (isLeap && selectedMonth == 1) {
        days -= daysInMonth[selectedMonth] + 1;
        daysInSelectedMonth = daysInMonth[selectedMonth] + 1;
    } else {
        days -= daysInMonth[selectedMonth];
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
    for(int i = 0; i < weeks; i++) {
        for(int j = 0; j < 7; j++) {
            if (dayOfWeek == daysInWeek[j][0] && firstDay < daysInSelectedMonth) {
                firstDay++;
                if (firstDay / 10 == 0) {
                    switch(j) {
                        case 0:
                            printf(" %d", firstDay);
                            break;
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                            printf("   %d", firstDay);
                            break;
                        case 5:
                            printf(" |  %d", firstDay);
                            break;
                        case 6:
                            printf("   %d", firstDay);
                            break;
                    }
                } else {
                    switch(j) {
                        case 0:
                            printf("%d", firstDay);
                            break;
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                            printf("  %d", firstDay);
                            break;
                        case 5:
                            printf(" | %d", firstDay);
                            break;
                        case 6:
                            printf("  %d", firstDay);
                            break;
                    }
                }
            } else {
                if (firstDay != 0 && firstDay < daysInSelectedMonth) {
                firstDay++;
                    if (firstDay / 10 == 0) {
                        switch(j) {
                            case 0:
                                printf(" %d", firstDay);
                                break;
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                                printf("   %d", firstDay);
                                break;
                            case 5:
                                printf(" |  %d", firstDay);
                                break;
                            case 6:
                                printf("   %d", firstDay);
                                break;
                        }
                    } else {
                        switch(j) {
                            case 0:
                                printf("%d", firstDay);
                                break;
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                                printf("  %d", firstDay);
                                break;
                            case 5:
                                printf(" | %d", firstDay);
                                break;
                            case 6:
                                printf("  %d", firstDay);
                                break;
                        }
                    }
                } else {
                    switch(j) {
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
            }
        };
        printf("\n");
    };

    return 0;
};