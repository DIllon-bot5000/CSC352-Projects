/*
* Program: anagrams2.c
* Author: Dillon Barr
* Course: CSC 352
* Purpose: This program reads in a series of strings, sorts the words alphabetically, processes them
* and prints out the words that are anagrams of each other.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


struct Node {
  char word[65];
  int length;
  char sorted[65]; 
  struct Node* anagram;
  struct Node* next;
};

/*
* This function checks if all the characters are valid alphabetical characters and then 
* sorts the word in the sorted array for later use.
*/
int getSorted(char sorted[], int length) {
  int i;
  int j;
  char temp;      

  for (i = 0; i < length; i++) {
    if (isdigit(sorted[i]) != 0) {
      fprintf(stderr, "Bad input ... non-alphabetical character\n");
      return -1;
    }
    sorted[i] = tolower(sorted[i]);
  }
  
  for (i = 0; i < length-1; i++) {
    for (j = i+1; j < length; j++) {
      if (sorted[i] > sorted[j]) {
        temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = temp;
      }
    }
 }
  return 0;
}
 
/*
* This function is used to check if the two sorted arrays of the current
* words are matches. If so a true is returned otherwise false.
*/
int checkWord(char nodeWord[], char newWord[], int length) {
  int i;
  for (i = 0; i < length; i++) {
     if (nodeWord[i]-'a' != newWord[i]-'a') {
       return 1;
     }
  }
  return 0; 
}
/*
* This function adds a new Node to the linked list of words that are not anagrams
* of any of the previous words. 
*/
void addNode(struct Node** headRef, int length, char sorted[], char word[]) {
  struct Node* newNode = malloc(sizeof(struct Node));
  if (newNode == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }
  struct Node *last = *headRef;

  strcpy(newNode->word, word);
  newNode->length = length;
  strcpy(newNode->sorted, sorted);
  newNode->anagram = NULL;
  newNode->next = NULL;

  if (*headRef == NULL) {
    *headRef = newNode;
    return;
  }

  while (last->next != NULL) {
    last = last->next;
  }
  last->next = newNode;
  return;
}
/*
* This function was used for debugging and prints off the 
* linked list of words that have anagrams, but not the anagrams.
*/
void printList(struct Node *head) {
  while(head != NULL) {
    printf("%s ", head->word);
    head = head->next;
  }
}
/*
* This function adds a new node to the linked lists of anagrams that each word has.
*/
void addNodetoAnagram(struct Node** anagram, int length, char sorted[], char word[]) {
  struct Node* newNode = malloc(sizeof(struct Node));
  if (newNode == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }
  struct Node *last = *anagram;

  strcpy(newNode->word, word);
  newNode->length = length;
  strcpy(newNode->sorted, sorted);
  newNode->anagram = NULL;
  newNode->next = NULL;

  if (*anagram == NULL) {
    *anagram = newNode;
    return;
  }

  while (last->anagram != NULL) {
    last = last->anagram;
  }
  last->anagram = newNode;
  return;
}
 
/*
* This function checks if a word is an anagram by comparing length and Ascii values. I thought this method would
* work however there are edge cases that show this isn't the best way to do this.
*/
void checkIfAnagram(struct Node** headRef, int length, char sorted[], char word[]) {
  struct Node *last = *headRef;
  int sortedCheck = 0;
  while (last != NULL) {
    if (last->length == length) {
      sortedCheck = checkWord(last->sorted, sorted, length);
      if (sortedCheck == 0) {
        addNodetoAnagram(&last->anagram, length, sorted, word);
        return;
      }
    }
    last = last->next;
  }
  addNode(headRef, length, sorted, word);
}

/*
* This function prints off the linked list of words and all
* the anagrams that were found for that word.
*/
void printAnagrams(struct Node* head) {
  while (head != NULL) {
    printf("%s", head->word);
    struct Node * anagrams = head->anagram;
    while (anagrams != NULL) {
      if (anagrams->anagram == NULL) {
        printf(" %s", anagrams->word);
      }
      else {
        printf(" %s", anagrams->word);
      }
      anagrams = anagrams->anagram;
      }
    
    printf("\n");
    head = head->next;
  }
}



int main() {
  struct Node* head = NULL;
  int errSeen = 0;
  int valid = 0;
  char word[65];
  char sorted[65];
  int length = 0;
  if (scanf("%64s", word) != EOF) {
    length = strlen(word);
    memcpy(sorted, word, 65*sizeof(char));
    valid = getSorted(sorted, length);
    if (valid == 0) {
      addNode(&head, length, sorted, word); 
    }
    else {
      errSeen = 1;
    }
    while (scanf("%64s", word) != EOF) {
     valid = 0;
     length = strlen(word);
     memcpy(sorted, word, 65*sizeof(char));
     valid = getSorted(sorted, length);
     if (valid == 0) {
       checkIfAnagram(&head, length, sorted, word);
     }
     else {
       errSeen = 1;
     }
   }
    printAnagrams(head);
  }
  return errSeen;
}
