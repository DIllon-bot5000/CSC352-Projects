#include <stdio.h>
/*
* Program: sumReverse
* Author: Dillon Barr
* Course: Csc 352
* Description: This program takes positive integer user
* input and calculates the sum of the input and the input's reverse.
*/
int main() {
  int number;
  int retVal;
  int errSeen = 0;
  while ((retVal = scanf("%d", &number)) > 0) {
    int reversed = 0;
    int sum = 0;
    int dividend;
    int temp = number;
    if (number > 0) {

      while (number > 0) {
        dividend = number % 10;
        reversed = (reversed * 10) + dividend;
        number = number / 10;
      }
      sum = reversed + temp;
      printf("%d\n", sum);
    }
    else {
      fprintf(stderr, "Invalid negative input\n");
      errSeen = 1;
    }
  }
  if (retVal < 1) {
    fprintf(stderr, "Invalid non-integer input\n");
    errSeen = 1;
  }
  return errSeen;
}
