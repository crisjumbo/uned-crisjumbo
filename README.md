### OUTPUT
```
/*
* 1. largeSide: length of the side of the rhombus (also the height of the rhombus)
* 2. borderList: list of characters that will be used to build the border of the rhombus (from the outside to the inside)
* Example: largeSide = 10, borderList = ['@', '.', 'o']
* Output:
* 012345678 9 012345678
* ||||||||| | |||||||||
* vvvvvvvvv v vvvvvvvvv
*           @              -> 0
*         @ . @            -> 1
*        @. o .@           -> 2
*       @.o . o.@          -> 3
*      @.o. @ .o.@         -> 4
*     @.o.@ . @.o.@        -> 5
*    @.o.@. o .@.o.@       -> 6
*   @.o.@.o . o.@.o.@      -> 7
*  @.o.@.o. @ .o.@.o.@     -> 8
*
* @.o.@.o.@ . @.o.@.o.@    -> 9
*
*  @.o.@.o. @ .o.@.o.@     -> 0
*   @.o.@.o . o.@.o.@      -> 1
*    @.o.@. o .@.o.@       -> 2
*     @.o.@ . @.o.@        -> 3
*      @.o. @ .o.@         -> 4
*       @.o . o.@          -> 5
*        @. o .@           -> 6
*         @ . @            -> 7
*           @              -> 8
*/
```

### MATRIX OUTPUT
Matrix elements help us to visualize the mathematical relation between it's position wihtin the matrix and its simetry.
I reduced the largeSide to 3.

|   | 0   | 1   | 2   | 3   | 4   |
|---|:---:|:---:|:---:|:---:|:---:|
| 0 | (0,0) | (0,1) | (0,2) | (0,3) | (0,4) |
| 1 | (1,0) | (1,1) | (1,2) | (1,3) | (1,4) |
| 2 | (2,0) | (2,1) | (2,2) | (2,3) | (2,4) |
| 3 | (3,0) | (3,1) | (3,2) | (3,3) | (3,4) |
| 4 | (4,0) | (4,1) | (4,2) | (4,3) | (4,4) |




### WORKFLOW

 1. create square that contains the rhombus (largeSide * 2 - 1, odd number always)
 2. loop through each row[0,1,2,3,4,5,6,7,8, 9, 10,11,12,13,14,15,16,17,18] 19 -> elements
 3. loop through each column[0,1,2,3,4,5,6,7,8, 9, 10,11,12,13,14,15,16,17,18] 19 -> elements
 - vertex will always be the 10th element
 - border will always be row elements from the middle column 
 - border starts the pattern ['@', '.', 'o', '.'] till the middle element
 - border ends the pattern symetrically from the middle element's character to the first character on the pattern ['@', '.', 'o', '.']
 4. Find the middle element's character on the pattern base (pattern[row % pattern.length])
 5. Paint only the elements that are inside the range [(column + row === middleElement), (column - row === middleElement)]
 6. Paint the border of the most external rhombus, which are the elements that follows: row + column === row + largeSide. (this formule get the border of a rhombus)
 7. Paint the border of the rhombus and next rhombus, which match the row's character: (row + column - largeSide) % pattern.length. (because column == largeSide, then we get row character)
 8. Go to step 5, and apply symetric operations.
 9. Print side inside the range [(column === largeSide), (column - row === largeSide)]. (symetric to step 5) (range will always be < largeSide)
 10. Paint the border of the most external rhombus, which are the elements that follows: column - row === largeSide - row.
 11. Paint the border of the rhombus and next rhombus, which match the row's character: (column - row) % pattern.length. (because I am substracting progressively, then I am going backwards 10>9>8>7>6>5>4>3>2>1>0)

