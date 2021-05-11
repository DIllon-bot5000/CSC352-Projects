/*
* Author: Dillon Barr
* Program: rotate.c
* Course: CSC 352
* Purpose: This program takes in a vector's size, contents and the rotation amount,
* rotates the vector and then prints the results.
*/


#include <stdio.h>
#include <stdlib.h>

void rightRotation(int *input, int size, int rotations) {
/*
* This function takes in the vector, size and number of rotations
* and reforms the required rotations to the right.
*/
  int i;
  int j;
  int temp;
  for (i = size; i > rotations; i--) {
    temp = input[0];
    for (j =0; j < size -1; j++) {
      input[j] = input[j+1];
    }
    input[j] = temp;
  }
}

void leftRotation(int *input, int size, int rotations) {
/*
* This function takes in the vector, size and number of rotations
* and reforms the required rotations to the left.
*/
  int i;
  int j;
  int temp;
  rotations = rotations * -1;
  for (i = 0; i < rotations; i++) {
    temp = input[0];
    for (j = 0; j < size-1; j++) {
      input[j] = input[j+1];
    }
    input[j] = temp;
  }
}

int main() {
  int counter = 0;
  int holder;
  int retVal;
  int size;
  int *inputArray;
  int rotations;  

  retVal = scanf("%d", &size);
  if (retVal < 1) {
    fprintf(stderr, "No integers in file\n");
    return 1;
  }
  
  if (size < 0) {
    fprintf(stderr, "Non-positive value given for size\n");
    return 1;
  }

  inputArray = malloc(size *sizeof(int));
  if (inputArray == NULL) {
    fprintf(stderr, "Out of memory!\n");
    return 1;
  }
  
  while (counter < size) {
    retVal = scanf("%d", &holder);
    if (retVal < 1) {
      fprintf(stderr, "Invalid character\n");
      return 1;
    }
    else {
      inputArray[counter] = holder;
    }
    counter++;
  }
  
  if (counter < size) {
    fprintf(stderr, "Fewer integers supplied than size\n");
    return 1;
  }
  
  while ((retVal = scanf("%d", &holder)) > 0) {
    rotations = holder;
  }
  
  if (rotations > 0) {
    rightRotation(inputArray, size, rotations);
  }
  else { 
    leftRotation(inputArray, size, rotations);
  }
 
  int i;
  for (i = 0; i < size; i++) {
    printf("%d ", inputArray[i]);
  }
  printf("\n");

  return 0;
}
