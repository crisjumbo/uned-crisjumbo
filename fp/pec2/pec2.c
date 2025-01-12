
#include <stdio.h>
#include <stdlib.h>

char pattern(int pos) {
  switch(pos) {
    case 0:
      return'@';
      break;
    case 1:
      return'.';
      break;
    case 2:
      return'o';
      break;
    default:
      return'.';
  }
}

int main() {
    int side;
    int boxSide;
    int patternLength;
    int row;
    int column;
    patternLength = 4;

    printf("Side of your rhombus: \n");
    scanf("%d", &side);

    if (side < 1 || side > 20) {
        return 0;
    }
    boxSide = (side * 2) - 1;
    row = 0;

    while(row < boxSide) {
        column = 0;
        while(column < boxSide){
            if (row <= side - 1) {

                if ((row + column) >= (side - 1) && (column - row) < side) {

                    if (column == side - 1) {

                        printf("%c", pattern(row % patternLength));

                    }else if (row + column >= side -1 && column < side) {

                        printf("%c", pattern((row + column - (side - 1)) % patternLength));

                    } else {
                        printf("%c", pattern(((side - 1) - (column - row)) % patternLength));

                    }


                } else {
                    if((column - row) < side) {
                      printf(" ");
                    }
                }

            } else {
                if (row - column < side && row + column <= (boxSide + side - 2)) {

                    if (column == side - 1) {
                        printf("%c", pattern(((boxSide + side - 2) - (row + column)) % patternLength));
                    } else if (row - column < side && column < side) {
                        printf("%c", pattern(((side - 1) - (row - column)) % patternLength));
                    }
                    else {
                        printf("%c", pattern(((boxSide + side - 2) - (row + column)) % patternLength));
                    }

                } else {
                  if(row + column <= (boxSide + side - 2)){
                    printf(" ");
                  }
                }

            }

            column++;
        }
        row++;
        printf("\n");
    }


    return 0;
}
