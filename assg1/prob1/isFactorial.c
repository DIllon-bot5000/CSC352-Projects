#include <stdio.h>
/*
* Program: isFactorial.c
* Author: Dillon Barr
* Course: Csc 352
* Description: This program reads in a series of positive integers from
* the user and checks if the integers are the factorial result of another integer
* and displays the result.
*/
void isFactorial(int number) {
  int counter = 1;
  int total = 1;
  while (counter <= number) {
    total = total * counter;
    if (total > number) {
      printf("%d not factorial\n", number);
      counter = number + 1;
    }
    
    if (total == number) {
      printf("%d = %d!\n", number, counter);
      counter = number + 1;
    }
    
    counter++;
  }
  return;
}

int main(void) {
  int errSeen = 0;
  int retVal;
  int num;
  while ((retVal = scanf("%d", &num)) > 0) {
    if (num > 0) {
      isFactorial(num);
    }
    else {
    fprintf(stderr, "Invalid negative input!\n");
    errSeen = 1;
    }
  }
  if (retVal < 1) {
    fprintf(stderr, "Invalid non-integer input!\n");
    errSeen = 1;
  }
  return errSeen;
}
