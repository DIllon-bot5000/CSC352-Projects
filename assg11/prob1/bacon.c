/*
* Program: bacon.c
* Author: Dillon Barr
* Course: CSC 352
* Purpose: This program reads in a file, creates a graph and then
* can calculate the degrees of Kevin Bacon.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Connection {
    struct Actor *actor1;
    struct Actor *actor2;
    char *name_movie;
    struct Connection *futureLine;
} Connection;

typedef struct Actor {
    char *actor_name;
    struct Connection *list_edges;
    struct Connection *end_e;
    struct Actor *future_a;
    struct Actor *future_q_a;
    struct Actor *future2a;
    int score_b;
    int select_m;
} Actor;

typedef struct Queue {
    struct Actor *list_a;
    struct Actor *end_a;
} Queue;

// checking if there is any memory issue or not.
void overflow(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Error: Memory Overflow.\n");
        exit(1);
    }
}

// Creating a connection between two actors and allocating memory to the two of
// them and also checking if there is any memory issue or not.
Connection *createConnectionBetweenActors(Actor *actor1, Actor *actor2, char *name_movie) {
    Connection *currConnection = malloc(sizeof(Connection));
    //Checking the memory overflow condition if there is enough memory to allocate or not.
    overflow(currConnection);
    currConnection->actor1 = actor1;
    currConnection->actor2 = actor2;
    currConnection->name_movie = strdup(name_movie);
    //Checking the memory overflow condition if there is enough memory to allocate or not.
    overflow(currConnection->name_movie);
    currConnection->futureLine = NULL;
    return currConnection;
}

// Creating each actor and allocating each actor some memory.
Actor *createActor(char *actor_name) {
    Actor *currActor = malloc(sizeof(Actor));
    //Checking the memory overflow condition if there is enough memory to allocate or not.
    overflow(currActor);
    currActor->actor_name = strdup(actor_name);
    //Checking the memory overflow condition if there is enough memory to allocate or not.
    overflow(currActor->actor_name);
    currActor->list_edges = NULL;
    currActor->end_e = NULL;
    currActor->future_a = NULL;
    // Creating connection between other actors and the movie between
    // them checking by creating a graph between adjacent edges and actors
    currActor->future_q_a = NULL;
    currActor->future2a = NULL;
    currActor->score_b = 0;
    currActor->select_m = 0;
    return currActor;
}

//Creating a Queue to store the actors list into them.
Queue *create() {
    Queue *currQ = malloc(sizeof(Queue));
    //Checking the memory overflow condition if there is enough memory to allocate or not.
    overflow(currQ);
    //Init with a null value for the list of actors.
    currQ->list_a = NULL;
    return currQ;
}

Actor *fetchActorWithName(char *actor_name, Actor *head) {
    Actor *currActor = head;
    while (currActor != NULL) {
        if (strcmp(currActor->actor_name, actor_name) == 0) {
            return currActor;
        }
        currActor = currActor->future_a;
    }
    return NULL;
}

void push(Queue *actor_q, Actor *actor) {
    if (actor_q->list_a == NULL) {
        actor_q->list_a = actor;
        actor_q->end_a = actor;
        return;
    }
    actor_q->end_a->future_q_a = actor;
    actor_q->end_a = actor;
}

Actor *pop(Queue *actor_q) {
    if (actor_q->list_a == NULL) {
        return NULL;
    }
    Actor *head = actor_q->list_a;
    actor_q->list_a = head->future_q_a;
    head->future_q_a = NULL;
    if (actor_q->list_a == NULL) {
        actor_q->end_a = NULL;
    }
    return head;
}

void push_q(Queue *actor_q, Actor *actor) {
    if (actor_q->list_a == NULL) {
        actor_q->list_a = actor;
        actor_q->end_a = actor;
        return;
    }
    actor_q->end_a->future2a = actor;
    actor_q->end_a = actor;
}

Actor *pop_q(Queue *actor_q) {
    if (actor_q->list_a == NULL) {
        return NULL;
    }
    Actor *head = actor_q->list_a;
    actor_q->list_a = head->future2a;
    head->future2a = NULL;
    if (actor_q->list_a == NULL) {
        actor_q->end_a = NULL;
    }
    return head;
}

Actor *peek_q(Queue *actor_q, char *actor_name) {
    Actor *currActor = actor_q->list_a;
    while (currActor != NULL) {
        if (strcmp(actor_name, currActor->actor_name) == 0) {
            return currActor;
        }
        currActor = currActor->future2a;
    }
    return NULL;
}

int searchWhiteSpace(char *line) {
    if (*line == '\0') return 1;
    char *ch = line;
    while (*ch != '\0') {
        if (isspace(*ch) == 0) {
            return 0;
        }
        ch++;
    }
    return 1;
}

int search_b(char *actor_name, Actor *list_a) {
    Actor *target = fetchActorWithName(actor_name, list_a);
    if (target == NULL) {
        fprintf(stderr, "Error: No actor named %s entered.\n", actor_name);
        return 1;
    }
    Actor *kevin_bacon = fetchActorWithName("Kevin Bacon", list_a);
    if (kevin_bacon == NULL) {
        printf("Score: No Bacon!");
        return 0;
    }
    if (strcmp(actor_name, "Kevin Bacon") == 0) {
        printf("Score: 0\n");
        return 0;
    }
    Queue *actor_q = create();
    push(actor_q, kevin_bacon);
    while (actor_q->list_a != NULL) {
        Actor *currActor = pop(actor_q);
        currActor->select_m = 2;
        if (strcmp(currActor->actor_name, actor_name) == 0) {
            printf("Score: %d\n", currActor->score_b);
            free(actor_q);
            return 0;
        }
        Connection *currConnection = currActor->list_edges;
        Queue *adjacents = create();
        while (currConnection != NULL) {
            if (currConnection->actor2->select_m == 0) {
                Actor *recurr = peek_q(adjacents, currConnection->actor2->actor_name);
                if (recurr == NULL) {
                    currConnection->actor2->score_b = currActor->score_b + 1;
                    currConnection->actor2->select_m = 1;
                    push_q(adjacents, currConnection->actor2);
                    push(actor_q, currConnection->actor2);
                }
            }
            currConnection = currConnection->futureLine;
        }
        while (pop_q(adjacents) != NULL) {}
        free(adjacents);
    }
    printf("Score: No Bacon!\n");
    free(actor_q);
    return 0;
}

void buildGraphQueueMovie(Queue *actor_q, char *name_movie) {
    if (name_movie == NULL || actor_q == NULL) return;
    while (1) {
        Actor *currActor = pop(actor_q);
        if (currActor == NULL) {
            break;
        }
        Actor *otherActor = actor_q->list_a;
        while (otherActor != NULL) {
            Connection *actor1Line = createConnectionBetweenActors(currActor, otherActor, name_movie);
            Connection *actor2Line = createConnectionBetweenActors(otherActor, currActor, name_movie);
            if (currActor->end_e == NULL) {
                currActor->list_edges = actor1Line;
            }
            else {
                currActor->end_e->futureLine = actor1Line;
            }
            currActor->end_e = actor1Line;
            if (otherActor->end_e == NULL) {
                otherActor->list_edges = actor2Line;
            }
            else {
                otherActor->end_e->futureLine = actor2Line;
            }
            otherActor->end_e = actor2Line;
            otherActor = otherActor->future_q_a;
        }
    }
}
void trim(char *str) {
    char *ch = str;
    while (*ch != '\0') {
        if (*ch == '\n') {
            *ch = '\0';
            return;
        }
        ch++;
    }
}
char *argumentsCheck(int argc, char *argv[], int *L) {
    if (argc == 1) {
        fprintf(stderr, "Wrong Command Please Use Like: bacon -l inFile\n");
        exit(1);
    }
    int i;
    *L = 0;
    int flagF = 0;
    char *path;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            *L = 1;
        }
        else {
            if (flagF == 0) {
                flagF = 1;
                path = strdup(argv[i]);
            }
            else {
                fprintf(stderr, "Wrong Command Please Use Like: bacon -l inFile\n");
                free(path);
                exit(1);
            }
        }
    }
    return path;
}
Actor *buildGraph(char *namefile) {
    FILE *path = fopen(namefile, "r");
    if (path == NULL) {
        fprintf(stderr, "Error Opening File.\n");
        exit(1);
    }
    char *each_line = NULL;
    size_t capacity = 0;
    char *name_movie = NULL;
    Queue *actrs_q = create();
    Actor *head = NULL;
    while (1) {
        int inputUser = getline(&each_line, &capacity, path);
        if (inputUser == -1 || inputUser == 0) {
            break;
        }
        if (searchWhiteSpace(each_line) == 1) {
            continue;
        }
        trim(each_line);
        char segment[7];
        sscanf(each_line, "%6s", segment);
        if (strcmp(segment, "Movie:") == 0) {
            buildGraphQueueMovie(actrs_q, name_movie);
            free(name_movie);
            name_movie = strdup(each_line + 7);
            overflow(name_movie);
            continue;
        }
        Actor *actor = fetchActorWithName(each_line, head);
        if (actor == NULL) {
            actor = createActor(each_line);
            if (head == NULL) {
                head = actor;
            }
            else {
                Actor *currActor = head;
                while (currActor->future_a != NULL) {
                    currActor = currActor->future_a;
                }
                currActor->future_a = actor;
            }
        }
        push(actrs_q, actor);
    }
    if (actrs_q->list_a != NULL) {
        buildGraphQueueMovie(actrs_q, name_movie);
    }
    free(each_line);
    free(actrs_q);
    free(name_movie);
    fclose(path);
    return head;
}
int main(int argc, char *argv[]) {
    int L;
    char *path = argumentsCheck(argc, argv, &L);
    Actor *head = buildGraph(path);
    char *each_line = NULL;
    size_t capacity = 0;
    int flagT = 0;
    while (1) {
        int inputUser = getline(&each_line, &capacity, stdin);
        if (inputUser == -1 || inputUser == 0) {
            break;
        }
        if (searchWhiteSpace(each_line) == 1) {
            continue;
        }
        trim(each_line);
        int output = search_b(each_line, head);
        if (output == 1) {
            flagT = 1;
        }
        Actor *currActor = head;
        while (currActor != NULL) {
            currActor->select_m = 0;
            currActor = currActor->future_a;
        }
    }
    free(path);
    free(each_line);
    Actor *currActor = head;
    while (currActor != NULL) {
        free(currActor->actor_name);
        Connection *currConnection = currActor->list_edges;
        while (currConnection != NULL) {
            free(currConnection->name_movie);
            Connection *previousEdge = currConnection;
            currConnection = currConnection->futureLine;
            free(previousEdge);
        }
        Actor *previousActor = currActor;
        currActor = currActor->future_a;
        free(previousActor);
    }
    return flagT;
}

