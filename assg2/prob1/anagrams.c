/*
* Program: anagrams.c
* Author: Dillon Barr
* Course: CSC 352
* Purpose: This program reads in a series of strings and checks if all
* the strings after the first one are anagrams of the first. This is done by getting
* the ASCII total of the characters in the word and checking if the other words
* come to the same total.
*/


#include <stdio.h>
#include <ctype.h>

int getAsciiVal(char word[]) {
  /*
  * getAsciiVal(word[) -- returns the Ascii value of the characters in the string
  * passed in from main. Runs a check to make sure the character is a letter.
  */
  int total = 0;
  int i;

  for (i = 0; word[i] != '\0'; ++i) {
    if (isdigit(word[i]) != 0) {
      fprintf(stderr, "Bad Input ... non-alphabetical character\n");
      return -1;
    }
    char letter = tolower(word[i]);
    total = total + letter - 'a';    
  }
  return total;
}

int main() {
  int errSeen = 0;
  char firstWord[65];
  char potentialAnagram[65];
  int potentialVal = 0;
  scanf("%64s", firstWord);
  int firstWordVal = getAsciiVal(firstWord);
  if (firstWordVal == -1) {
    return 1;
  }
  printf("%s\n", firstWord);  
 
  while (scanf("%s", potentialAnagram) != EOF) {
    potentialVal = getAsciiVal(potentialAnagram);
    if (potentialVal == -1) {
      errSeen = 1;
    }
    else if (potentialVal == firstWordVal) {
      printf("%s\n", potentialAnagram);
    }      
  }

  return errSeen;
}
