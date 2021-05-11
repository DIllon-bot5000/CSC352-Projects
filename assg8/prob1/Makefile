mymake : myMake.o myGraph.o
	gcc -g -Wall myMake.o myGraph.o -o mymake
myMake.o : myMake.c myGraph.h
	gcc -Wall -g -c myMake.c
myGraph.o : myGraph.c myGraph.h
	gcc -Wall -g -c myGraph.c
