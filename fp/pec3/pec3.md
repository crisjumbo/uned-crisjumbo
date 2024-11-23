# Calendar

### Requirement
1. Select Month
2. Select Year between range [1601, 3000]
3. Print the month page for that selection

### Steps
1. Ask for a year and month.
2. Condition; if out of range (1601 - 3000).
3. Condition; if out of range (1 - 12).
4. Calculate days looping throuh each year from 1601 to introduced year X.
5. Sum 365, but if year is leap sum 366, then substract 365 or 366 of X year.
6. Loop till introduced month Y
7. Add 1 day if indexed February month is in a leap year.
8. Create 4 weeks calendar or 5 weeks if total days N % 7 is Monday or not.
9. Print day or empty day "*" for the calendar.