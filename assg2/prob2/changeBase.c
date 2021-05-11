/*
* Program: changeBase.c
* Author: Dillon Barr
* Course: Csc 352
* Purpose: This program reads in a numeric base and converts the following
* strings to a numeric value in that base.
*/



#include <stdio.h>
#include <ctype.h>

long checkString(char temp[], int base) {
  /*
  * checkString(temp, base) -- takes the string currently
  * being looked at in main and attempts to convert the string
  * into the correct long valeu of the base given. Runs checks to
  * make sure the characters are valid alphanumeric characters
  * and are valid numbers in the base system in use.
  */
  int i;
  long num;
  int letterVal;
  int numVal;
  char letter;
  for (i = 0; temp[i] != '\0'; i++) {
    if (isalnum(temp[i] == 0)) {
      fprintf(stderr, "Invalid character in string\n");
      return -1;
    }
    else if (isdigit(temp[i]) > 0) {
      numVal = temp[i] - '0';
      if (numVal < base) {
        num = num * base + temp[i] - '0';
      }        
      else {
        fprintf(stderr, "Not a base %d number\n", base);
        return -1;
      }  
    }
    else if (isalpha(temp[i]) > 0) {
      letter = tolower(temp[i]);
      letterVal = letter - 'a' + 10;
      if (letterVal > base) {
        fprintf(stderr, "Not a base %d number\n", base);
        return -1;
      }
      else {
        num = num * base + letterVal;
      }
    }
  }
  return num;
}

int main() {
  int errSeen = 0;
  char input[7];  
  int base;
  long changed;

  scanf("%d", &base);

  if (base < 2 || base > 36) {
    fprintf(stderr, "Invalid base. Base must be between 2 and 36\n");
    return 1;
  }

  while (scanf("%6s", input) != EOF) {
   changed = checkString(input, base);
   if (changed != -1) { 
     printf("%lu\n", changed); 
   }
   else {
     errSeen = 1;
   }
  }
  return errSeen;
}
