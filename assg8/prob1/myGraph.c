/*
* File: myGraph.c
* Author: Dillon Barr
* Course: CSC 352
* Purpose: This program builds the graph of targets and the lists of 
* commands and dependencies associated for myMake.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myGraph.h"

targetNode *head = NULL;


// This function builds a new target node for the 
// graph.
targetNode *buildTarget(char *newTarget) {
  targetNode *target = malloc(sizeof(targetNode));
  if (target == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }
  target->name = strdup(newTarget);
  
  if (target->name == NULL) {
    fprintf(stderr, "Out of memory!\n");
    freeAllMem();
    exit(1);
  }

  target->isVisited = 0;
  target->isTarget = 0;
  target->depHead = NULL;
  target->cmdHead = NULL;
  target->next = NULL;
  return target;
}

// This function bulilds a dependent node for the 
// associated target node passed in.
depNode *buildDependent(targetNode *dest) {
  depNode *newDep = malloc(sizeof(depNode));
  if (newDep == NULL) {
    fprintf(stderr, "Out of memory!\n");
    freeAllMem();
    exit(1);
  }

  newDep->targetptr = dest;
  newDep->next = NULL;
  return newDep;
}

// This function builds a command node for a targetNode
cmdNode *buildCmdNode(char *command) {
  cmdNode *newCmd = malloc(sizeof(cmdNode));
  if (newCmd == NULL) {
    fprintf(stderr, "Out of memory!\n");
    freeAllMem();
    exit(1);
  }

  newCmd->command = strdup(command);
  if (newCmd->command == NULL) {
    fprintf(stderr, "Out of memory!\n");
    freeAllMem();
    exit(1);
  }
   newCmd->next = NULL;
   return newCmd;
}

// This function iterates over the graph of
// target nodes to find the target node
// with the matching name to the one passed in
targetNode *findTarget(char *name) {
  targetNode *ptr = head;
  while (ptr != NULL) {
    if (strcmp(ptr->name, name) == 0) {
      return ptr;
    }
    ptr = ptr->next;
  }
  return ptr;
}


// This function calls on the function to build a command
// and then inserts it into the linked list of command nodes
void addCommand(targetNode *src, char *command) {
  cmdNode *ptr = src->cmdHead;
  if (ptr == NULL) {
    src->cmdHead = buildCmdNode(command);
    return;
  }
  while (ptr != NULL) {
    ptr = ptr->next;
  }
  ptr->next = buildCmdNode(command);
}

// This function checks if a target already exists and
// if it does not, creates a new target node and inserts it
// into the linked list of targets.
targetNode *addTarget(char *newTarget) {
  targetNode *newTarg = findTarget(newTarget);
  if (newTarg != NULL) {
    return newTarg;
  }
  else {
    newTarg = buildTarget(newTarget);
    targetNode *curr = head;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = newTarg;
    return newTarg;
  }
}

// This function builds a new dependent node and inserts it into
// the linked list of dependents for a target. If the 
// dependent already exists there is an error.
void addDependent(targetNode *target, char *name) {
  targetNode *dep = addTarget(name);
  depNode *ptr = target->depHead;
  if (ptr == NULL) {
    target->depHead = buildDependent(dep);
    return;
  }
  while (ptr->next != NULL) {
    if (ptr->targetptr == dep) {
      fprintf(stderr, "A dependent already exists\n");
      freeAllMem();
      exit(1);
    }
    ptr = ptr->next;
  }

  if (ptr->targetptr == dep) {
    fprintf(stderr, "A dependent already exists\n");
    freeAllMem();
    exit(1);
  }
  ptr->next = buildDependent(dep);
}
// This function does the post order traversal for the
// graph starting at the specified target.
void postOrderTraversal(targetNode *target) {
  if (target->isVisited == 1) {
    return;
  }
  target->isVisited = 1;
  depNode *currentDep = target->depHead;
  while (currentDep != NULL) {
    postOrderTraversal(currentDep->targetptr);
    currentDep = currentDep->next;
  }

  process(target);
}

// This function assists the post order traversal function
// and prints out the target and commands.
void process(targetNode *target) {
  printf("%s\n", target->name);
  cmdNode *ptr = target->cmdHead;
  while (ptr != NULL) {
    printf("  %s\n", ptr->command);
    ptr = ptr->next;
  }
}

// This function iterates over all the dependencies
// and commands of the passed in target and frees them
void freeDepsAndCmds(targetNode *target) {
  depNode *depptr = target->depHead;
  while (depptr != NULL) {
    depNode *temp = depptr->next;
    free(depptr);
    depptr = temp;
  }

  cmdNode *cmdptr = target->cmdHead;
  while (cmdptr != NULL) {
    cmdNode *temp = cmdptr->next;
    free(cmdptr->command);
    free(cmdptr);
    cmdptr = temp;
  }
  free(target->name);
}

// This function iterates over the linked list of
// targets and calls the previous free function before
// freeing the target nodes.
void freeAllMem() {
  targetNode *targetptr = head;
  while (targetptr != NULL) {
    targetNode *temp = targetptr->next;
    freeDepsAndCmds(targetptr);
    free(targetptr);
    targetptr = temp;
  }
}

// This function prints out the entirety of the graph.
void print() {
  targetNode *targetptr = head;
  while (targetptr != NULL) {
    printf("%s: \nDependencies: ", targetptr->name);
    depNode *depptr = targetptr->depHead;
    while (depptr != NULL) {
      printf("%s ", depptr->targetptr->name);
      depptr = depptr->next;
    }
    printf("\nCommands: ");
    cmdNode *cmdptr = targetptr->cmdHead;
    while (cmdptr != NULL) {
      printf("%s ", cmdptr->command);
      cmdptr = cmdptr->next;
    }
    printf("\n");
    targetptr = targetptr->next;
  }
}
 
