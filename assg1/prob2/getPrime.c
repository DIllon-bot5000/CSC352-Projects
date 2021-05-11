#include <stdio.h>
/*
* Program getPrime.c
* Author: Dillon Barr
* Course: Csc 352
* Description: This program takes a positive integer
* as input and finds the smaller prime number
* larger than the input.
*/
void isPrime(int number) {
  int temp = number + 1;
  int searching = 1;
  
  while (searching != 0) {
    int counter = 2;

    while (counter < temp) {
      if (temp % counter == 0) {
        temp++;
        break;
      }
      
      if (counter == temp - 1) {
        printf("%d\n", temp);
        return;
      }
      counter++;
    }
  }
}

int main() {
  int retVal;
  int num;
  retVal = scanf("%d", &num);
  if (retVal < 1) {
    fprintf(stderr, "Invalid input. Input must be of time integer.\n");
    return 1;
  }
  else if (num < 0) {
    fprintf(stderr, "Invalid input. Input must be positive.\n");
    return 1;
  }
  else {
    isPrime(num);
    return 0;
  }
}
