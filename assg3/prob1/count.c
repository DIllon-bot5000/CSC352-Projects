/*
* Program: count.c
* Author: Dillon Barr
* Course: CSC 352
* Purpose: This program takes in n numbers, stores them in an
* array and prints out the elements in the array as well
* as the number of occurences.
*/

#include <stdio.h>
#include <stdlib.h>

int * insertionSort(int *input, int size) {
/*
* This function performs insertion sort on the array and returns
* the sorted result.
*/
  int i;
  int key;
  int j;
  for (i = 1; i < size; i++) {
    key = input[i];
    j = i - 1;

    while (j >= 0 && input[j] > key) {
      input[j + 1] = input[j];
      j = j-1;
    }
  input[j + 1] = key;
  }
  return input;
}

int printResults(int *input, int size) {
/*
* This functino takes in the sorted array and iterates over it
* keeping track of the values as well as the number of times
* it appears before printing the results.
*/
  int i;
  int counter = 0;
  int printed = 0;
  int current;
  for (i = 0; i < size; i++) {
    current = input[i];
    ++counter;
    printed = 1;
    if (current != input[i+1]) {
      printf("%d %d\n", current, counter);
      counter = 0;
      printed = 0;
    }
  }
  if (printed == 1) {
    printf("%d %d\n", current, counter);
  }
  return 0;
  }
       

int main() {
  int counter = 0;
  int holder;
  int retVal;
  int size;
  int *inputArray;
  
  retVal = scanf("%d", &size);
  if (retVal < 1) {
    fprintf(stderr, "No integers in file\n");
    return 1;
  }
  if (size < 0) {
    fprintf(stderr, "Non-positive size given\n");
    return 1;
  }
  inputArray = malloc(size *sizeof(int));
  if (inputArray == NULL) {
    fprintf(stderr, "Out of memory!\n");
  }
  
  while ((retVal = scanf("%d", &holder)) > 0) {
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
    return(1);
  }
  int temp;
  inputArray = insertionSort(inputArray, size);
  temp = printResults(inputArray, size);  
  
  return temp;
}
