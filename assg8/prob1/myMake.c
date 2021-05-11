/*
* File: myMake.c
* Author: Dillon Barr
* Course: CSC 352
* Purpose: This program is a simple version of the make program. It will read in a makefile
* and build a graph of the associated targets, dependencies, and commands. After, it prints
* the target node and its dependents and commands in a post order traversal. I was lot of 
* testcases in the early submission and it turned out I was freeing some memory twice if there 
* was an error so once I fixed that I was able to pass those cases..
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "myGraph.h"

extern targetNode *head;

FILE *fileptr;
char *line;

// This function is called when an error occurs so
// that all memory can be freed before the program exits.
void exitWithError() {
  fclose(fileptr);
  free(line);
  freeAllMem();
  exit(1);
}

// Checks to see if a line is a command by checking
// if the first character is a tab.
int isACommand(char *line) {
  return line[0] == '\t';
}

// Chekcks if the line passed in is a blank line.
int blankCheck(char *line) {
  char *ptr = line;
  while (*ptr) {
    if (!isspace(*ptr)){
      return 0;
    }
    ptr++;
  }
  return 1;
}

// This function is used to clean a line containing a target and
// then build the necessary target and dependency nodes in the graph.
targetNode *processTarget(char *line) {
  char *lineptr = line;
  char colon;
  char buff[65];
  int charsRead;
  if (sscanf(lineptr, "%64[^:]%[:]%n", buff, &colon, &charsRead) != 2 || colon != ':') {
    fprintf(stderr, "Invalid target format\n");
    exitWithError();
  }
  lineptr += charsRead;
  char *cleanedTarget = buff;
  if (sscanf(buff, "%s", cleanedTarget) != 1) {
    fprintf(stderr, "Empty target\n");
    exitWithError();
  }
  targetNode *target = addTarget(cleanedTarget);
  if (target->isTarget == 1) {
    fprintf(stderr, "Target already exists\n");
    exitWithError();
  }
  target->isTarget = 1;
  while (sscanf(lineptr, "%64s%n", buff, &charsRead) == 1) {
    addDependent(target, buff);
    lineptr += charsRead;
  }
  return target;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Invalid number of commands\n");
    freeAllMem();
    exit(1);
  }
  char *filename = argv[1];
  char *makeFileTarget = argv[2];
  fileptr = fopen(filename, "r");
  if (fileptr == NULL) {
    fprintf(stderr, "Error opening file\n");
    freeAllMem();
    exit(1);
  }
  head = buildTarget("dummy");
  line = NULL;
  size_t size = 0;

  ssize_t lineRes = getline(&line, &size, fileptr);
  while (lineRes != EOF && blankCheck(line)) {
    lineRes = getline(&line, &size, fileptr);
  }
  
  // Make sure the first line is a target
  if (isACommand(line)) {
    fprintf(stderr, "First line needs to be a target\n");
    exitWithError();
  }
  targetNode *currTarget = processTarget(line);

  // This block checks and cleans a command line to be added to a target.  
  while((lineRes = getline(&line, &size, fileptr)) != EOF) {
    if(blankCheck(line)) {
      continue;
    }
    if (isACommand(line)) {
      char *command = line;
      while (isspace(*command)) {
        command++;
      }
      if (*command == '\0') {
        continue;
      }
      char *commandEnd = line + strlen(line)-1;
      while (isspace(*commandEnd)) {
        *commandEnd = '\0';
        commandEnd--;
      }
      addCommand(currTarget, command);
  }
  else {
    currTarget = processTarget(line);
  }
}
  
  // Make sure target exists before calling traversal.
  targetNode *targetNode = findTarget(makeFileTarget);
  if (targetNode == NULL || targetNode->isTarget ==0) {
    fprintf(stderr, "Target not found\n");
    exitWithError();
  }
  postOrderTraversal(targetNode);
  free(line);

  fclose(fileptr);
  freeAllMem();

  return 0;
}
