/*
* File: myGraph.h
* Author: Dillon Barr
* Course: CSC 352
* Purpose: This header file contains the protypes and typedefs for the functions and 
* struts used in myGraph.c
*/

#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct targetNode {
  int isTarget;
  int isVisited;
  char *name;
  struct depNode *depHead;
  struct cmdNode *cmdHead;
  struct targetNode *next;
} targetNode;

typedef struct depNode {
  targetNode *targetptr;
  struct depNode *next;
} depNode;

typedef struct cmdNode {
  char *command;
  struct cmdNode *next;
} cmdNode;

targetNode *buildTarget(char *newTarget);

depNode *buildDependent(targetNode *dest);

cmdNode *buildCmdNode(char *command);

targetNode *findTarget(char *name);

void addCommand(targetNode *src, char *command);

targetNode *addTarget(char *newTarget);

void addDependent(targetNode *target, char *name);

void postOrderTraversal(targetNode *target);

void process(targetNode *target);

void freeAllMem();

void print();

extern targetNode *head;

#endif
