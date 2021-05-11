/*
*  Program: reach.c
*  Author: Dillon Barr
*  Course: CSC 352
*  Purpose: This program creates a graph either from a file or
*  user input and runs a DFS to check if there exists an edge
*  between specified vertices.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct vertex {
  char *name;
  struct edge *edgeHead;
  struct vertex *next;
  int visited;
} vertex;

typedef struct edge {
  struct vertex *linked;
  struct edge *next;
} edge;

struct vertex *head;
int errorSeen = 0;

/*
* This function sets the visited field of the vertices to be false
* in order to run DFS multiple times in one execution of the program.
*/
void clearVisited() {
  struct vertex *curr = head;
  while (curr != NULL) {
    curr->visited = 0;
    curr = curr->next;
  }
}
/*
* This function builds an edge object for the linked list. It uses a pointer 
* to the source vertex as the linked field for later use.
*/
edge *buildEdge(vertex *node) {
  struct edge *newNode = malloc(sizeof(struct edge));
  if (newNode == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }
  newNode->linked = node;
  newNode->next = NULL;
  return newNode;
}

/*
* This function creates a new vertex object using the char pointer passed
* in to populate the name field.
*/
vertex *buildVertex(char *name) {
  struct vertex *newVertex = malloc(sizeof(struct vertex));
  if (newVertex == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }
  newVertex->name = strdup(name);
  newVertex->edgeHead = buildEdge(newVertex);
  newVertex->next = NULL;
  return newVertex;
}

/*
* This function iterates through all the edges attached to 
* the vertices in the linked list and frees them from
* memory.
*/
void freeEdges(vertex *vertex) {
  struct edge *edgeptr = vertex->edgeHead;
  struct edge *next = edgeptr->next;
  free(edgeptr);
  edgeptr = next;
  while (edgeptr != NULL) {
    next = edgeptr->next;
    free(edgeptr);
    edgeptr = next;
  }
}

/*
* This function adds a new vertex to the linked list
* of vertices that already exist in the graph.
*/
void addVertex(char *name) {
  struct vertex *vertexPtr = head;
  while (vertexPtr->next != NULL) {
    if (strcmp(name, vertexPtr->name)==0) {
      fprintf(stderr, "Duplicate vertex.\n");
      errorSeen = 1;
      return;
    }
    else {
      vertexPtr = vertexPtr->next;
    }
  }
  
  if (strcmp(name, vertexPtr->name) == 0) {
    fprintf(stderr, "Duplicate vertex.\n");
    errorSeen = 1;
    return;
  }
  else {
    vertexPtr->next = buildVertex(name);
  }
}

/*
* This function searches through the linked list of vertices
* to try and find the specified vertex and returns a pointer to it.
*/
vertex *findVertex(char *name) {
  struct vertex *vertexPtr = head;
  while (vertexPtr != NULL) {
    if (strcmp(vertexPtr->name, name) == 0) {
      return vertexPtr;
    }
    else {
      vertexPtr = vertexPtr->next;
    }
  }
  return vertexPtr;
}

/*
* This function adds an edge from the "from" vertex to the
* "to" vertex.
*/
void addEdge(vertex *from, vertex *to) {
  struct edge *curr = from->edgeHead;
  while (curr->next != NULL) {
    if (curr->linked == to) {
      return;
    }
    else {
      curr = curr->next;
    }
  }
  
  if (curr->linked == to) {
    return;
  }
  else {
    curr->next = buildEdge(to);
  }
}

/*
* This function runs a DFS search on two vertices in the 
* graph and returns true if an edge exists, false otherwise.
* This function was given to us in the spec.
*/
int dfs(vertex *from, vertex *to) {
  if (from == to) {
    return 1;
  }
  else {
    if (from->visited == 1) {
      return 0;
    }
    from->visited = 1;
    struct edge *curr = from->edgeHead;
    while (curr != NULL) {
      if (dfs(curr->linked, to) == 1) {
        return 1;
      }
      curr = curr->next;
    }
    return 0;
  }
}

/*
* This function handles reading the user input whether from a file or
* the keyboard. There are three valid commands and three different processes
* for dealing with said input. This function also checks for bad input whether
* that be blank lines, invalid commands, or non existant vertices.
*/
void parseLine(char *line) {
  char *lineptr = line;
  char buff[65] = "";
  int charsRead = 0;
  int result;
  
  result = sscanf(lineptr, "%64s%n", buff, &charsRead);
  lineptr += charsRead;

  if (result == 0) {
    return;
  }

  if (strcmp(buff, "@n") == 0) {
    while (sscanf(lineptr, "%64s%n", buff, &charsRead) == 1) {
      lineptr += charsRead;
      addVertex(buff);
    }
  }

  else if (strcmp(buff, "@e") == 0) {
    if (sscanf(lineptr, "%64s%n", buff, &charsRead) != 1) {
      fprintf(stderr, "Source vertex could not be read\n");
      errorSeen = 1;
    }
    else {
      lineptr += charsRead;
      struct vertex *from = findVertex(buff);
      if (from == NULL) {
        fprintf(stderr, "Source vertex does not exist\n");
        errorSeen = 1;
      }
      else {
        while (sscanf(lineptr, "%64s%n", buff, &charsRead) == 1) {
          lineptr += charsRead;
          struct vertex *to = findVertex(buff);
          if (to == NULL) {
            fprintf(stderr, "Cannot create edge with nonexistant vertex\n");
            errorSeen = 1;
          }
          else {
            addEdge(from, to);
          }
        }
      }
    }
  }

  else if (strcmp(buff, "@q") == 0) {
    char start[65];
    char end[65];
    char holder[65];
    int connected;
    if (sscanf(lineptr, "%64s %64s %64s", start, end, holder) != 2) {
      fprintf(stderr, "Too many arguments for DFS");
      errorSeen = 1;
    }
    else {
      struct vertex *from = findVertex(start);
      struct vertex *to = findVertex(end);
      if (from == NULL || to == NULL) {
        fprintf(stderr, "One of the nodes does not exist in the graph\n");
        errorSeen = 1;
      }
      else {
        clearVisited();
        connected = dfs(from, to);
        printf("%d\n", connected);
      }
    }
  }
  else {
    fprintf(stderr, "Invalid operation!\n");
    errorSeen = 1;
  }
}

int main(int argc, char **argv) {
  head = malloc(sizeof(struct vertex));
  if (head == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }
  else {
    head->next = NULL;
    head->name = strdup("temp");
    head->edgeHead = buildEdge(head);
  }
  int fromFile = 0;
  FILE *fileptr = stdin;
  if (argc > 1) {
    char *filename = argv[1];
    fromFile = 1;
    fileptr = fopen(filename, "r");
    if (fileptr == NULL) {
      fprintf(stderr, "Error opening file.\n");
      exit(1);
    }
    if (argc > 2) {
      fprintf(stderr, "Error only 1 file allowed.\n");
      errorSeen = 1;
    }
  }
  
  char *line = NULL;
  size_t size = 0;

  while (getline(&line, &size, fileptr) != EOF) {
    parseLine(line);
  }
  
  free(line);

  struct vertex *vertexPtr = head;
  struct vertex *temp;
  while (vertexPtr != NULL) {
    temp = vertexPtr->next;
    freeEdges(vertexPtr);
    free(vertexPtr->name);
    free(vertexPtr);
    vertexPtr = temp;
  }

  if (fromFile) {
    fclose(fileptr);
  }
  return errorSeen;
}
