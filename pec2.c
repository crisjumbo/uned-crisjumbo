#include <stdio.h>
#include <stdlib.h>

int main() {
    int side;
    int boxSide;
    char pattern[] = {'@', '.', 'o', '.'};
    int patternLength = sizeof(pattern);
    
    printf("Side of your rhombus: \n");
    scanf("%d", &side);
    
    if (side < 1 || side > 20) {
        return 0;
    }
    boxSide = (side * 2) - 1;
    int row = 0;
    
    while(row < boxSide) {
        int column = 0;
        while(column < boxSide){
            if (row <= side - 1) {

                if ((row + column) >= (side - 1) && (column - row) < side) {
                
                    if (column == side - 1) {
                        
                        printf("%c", pattern[row % patternLength]);
                        
                    }else if (row + column >= side -1 && column < side) {

                        printf("%c", pattern[(row + column - (side - 1)) % patternLength]);

                    } else {
                        printf("%c", pattern[((side - 1) - (column - row)) % patternLength]);
                        
                    }
                    
                    
                } else {
                    printf(" ");
                    
                }

            } else {
                if (row - column < side && row + column <= (boxSide + side - 2)) {

                    if (column == side - 1) {
                        printf("%c", pattern[((boxSide + side - 2) - (row + column)) % patternLength]);
                    } else if (row - column < side && column < side) {
                        printf("%c", pattern[((side - 1) - (row - column)) % patternLength]);
                    }
                    else {
                        printf("%c", pattern[((boxSide + side - 2) - (row + column)) % patternLength]);
                    }

                } else {
                    printf(" ");
                }

            }
            
            column++;
        }
        row++;
        printf("\n");
    }
    
    
    return 0;
}